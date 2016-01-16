#include "system.h"


using std::cout;
using std::endl;
using std::ofstream;
using std::fstream;

System::System(int argc, char** argv, char* fileName) :
    app(argc, argv) {

    this->fileName          = fileName;
    this->sampler           = new Sampler;
    this->systemSize        = vec(-1,-1,-1); // Used as flag for 'no system size set'
    this->thermostatActive  = false;
}

void System::setTimeStep(double dt) {
    this->dt = dt;
}

void System::setIntegrator(Integrator* integrator) {
    this->integrator = integrator;
    this->dt = integrator->getTimeStep();
}

void System::setPotential(Potential* potential) {
    this->potential = potential;
    this->sampler->setPotential(potential);
}

void System::setInitialCondition(InitialCondition* initialCondition) {
    this->initialCondition = initialCondition;
}

void System::setPeriodicBoundaryConditions(vec systemSize) {
    this->periodicBoundaryConditions = true;
    this->systemSize                 = systemSize;
}

void System::setPeriodicBoundaryConditions(bool periodicBoundaryConditions) {
    this->periodicBoundaryConditions = periodicBoundaryConditions;
}

void System::setThermostat(Thermostat* thermostat) {
    this->thermostat = thermostat;
    this->thermostatActive = true;
}

void System::setThermostatActive(bool thermostatActive) {
    this->thermostatActive = thermostatActive;
}

void System::setSystemSize(vec systemSize) {
    this->systemSize = systemSize;
}

void System::setupGUI() {
    this->skip = 25;
    this->mainWindow = new MainWindow;

}

void System::setupSystem() {
    this->initialCondition->setupInitialCondition();
    this->atoms = this->initialCondition->getAtoms();
    this->n = initialCondition->getN();
    this->sampler->setupSampler(this->atoms, this->n);
    this->integrator->setPotential(this->potential);
    this->fileOutput = new FileOutput(this->fileName);
}

void System::integrate(int Nt) {
    this->integrate(Nt, true);
}


void System::integrate(int Nt, bool plotting) {    
    this->setupSystem();

    if (this->systemSize[0] == -1 &&
        this->systemSize[1] == -1 &&
        this->systemSize[2] == -1) {
        cout << endl << "### WARNING ###: No system size set. Using default value (1,1,1)." << endl << endl;
        this->systemSize = vec(1);
    }
    // Set up the real time plot if plotting is enabled.
    this->plotting = plotting;
    if (this->plotting) {
        this->setupGUI();
        //this->mainWindow->setup(Nt);
        this->mainWindow->show();
    }
    this->Nt       = Nt;
    this->sampler->setNtDt(Nt,this->dt);

    for (int t=0; t < Nt; t++) {
        this->integrator->advance(this->atoms, this->n);

        if (this->periodicBoundaryConditions) {
            this->applyPeriodicBoundaryConditions();
        }
        if (this->thermostatActive) {
            double instantaneousTemperature = this->sampler->getInstantanousTemperature()[t];
            this->thermostat->adjustVelocities(this->atoms, this->n, instantaneousTemperature);
        }

        this->fileOutput->saveState(this->atoms, this->n);
        this->sampler->sample(t);
        this->printProgress(t);
    }
    this->printProgress(Nt);

    if (this->plotting) {
        this->plot();
    }
}

void System::dumpInfoToTerminal() {
    cout << " ┌──────────────────────────────────────────────────────┐ " << endl;
    cout << " │                Starting integration                  │ " << endl;
    cout << " └──┬───────────────────────────────────────────────────┘ " << endl;
    cout << "    │  Initial condition type: " << this->initialCondition->getName() << endl;
    cout << "    │  Integrator in use:      " << this->integrator->getName()       << endl;
    cout << "    │  Potential in use:       " << this->potential->getName()        << endl;
    cout << "    │  Output file name:       " << this->fileName                    << endl;
    cout << "    ├─────────────────────────────────────────────────┐ " << endl;
    cout << "    │ Parameters                                      │ " << endl;
    cout << "    ├─────────────────────────────────────────────────┘ " << endl;
    cout << "    │  Number of atoms:        " << this->n             << endl;
    cout << "    │  Time step:              " << this->dt            << endl;
    cout << "    │  Number of time steps:   " << this->Nt            << endl;
    cout << "    │  Total time:             " << this->Nt*this->dt   << endl;
    cout << "    │  System size (cube):     " << this->systemSize    << endl;
    cout << "    ├─────────────────────────────────────────────────┐ " << endl;
    cout << "    │ Progress                                        │ " << endl;
    cout << "    └─────────────────────────────────────────────────┘ " << endl;
}

void System::printProgress(int t) {
    if (t==0) {
        this->startTime = getRealTime();
        this->oldTime   = this->startTime;
        this->lastTimeStepTime = 0;
        this->dumpInfoToTerminal();
    }
    int k = 200;
    if (t % (Nt/k) == 0) {
        this->oldTime       = this->currentTime;
        this->currentTime   = getRealTime();
        double progress     = ((double) t) / this->Nt;
        double elapsedTime  = this->currentTime - this->startTime;
        cout << "                                                                             \r";
        printf("\r      %5.1f %s  Elapsed time: %5.1f s  Estimated tot. time: %5.1f s \r",
               progress*100, "%",
               elapsedTime,
               elapsedTime+(this->currentTime-this->oldTime+this->lastTimeStepTime)*(1-progress)*k/2.0);
        fflush(stdout);
        this->lastTimeStepTime = this->currentTime-this->oldTime;
    }
    if (t == this->Nt) {
        double elapsedTime = this->currentTime - this->startTime;
        if (elapsedTime < 0) {
            elapsedTime = 0;
        }
        cout << "                                                                             ";
        cout << endl << "Integration finished. Total elapsed time: " << elapsedTime << endl;
    }
}

void System::plot() {
    this->mainWindow->plot(this->n, this->Nt, this->sampler);
    this->mainWindow->show();
}



void System::applyPeriodicBoundaryConditions() {
    for (int i=0; i < this->n; i++) {
        vec pos = vec();
        vec posBefore = vec();
        posBefore.set(this->atoms[i].getPosition());
        pos.set(this->atoms[i].getPosition());

        bool changed = false;

        for (int j=0; j < 3; j++) {
            if (pos[j] > this->systemSize[j]) {
                changed = true;
                pos.set(pos[j] - this->systemSize[j], j);
            } else if (pos[j] < 0) {
                changed = true;
                pos.set(this->systemSize[j]+pos[j], j);
            }
        }
        if (changed) {
            this->atoms[i].setPosition(pos);
        }
    }
}





System::FileOutput::FileOutput(char* fileName) {
    this->outFile.open(fileName, std::ios::out);
}

System::FileOutput::~FileOutput() {
    if (this->outFile.is_open()) {
        this->outFile.close();
    }
}

void System::FileOutput::saveState(Atom* atoms, int n) {
    if (true) {//(this->outFile.is_open()) {
        this->outFile << n << endl;
        this->outFile << "Comment line" << endl;

        for (int i = 0; i < n; i++) {
            this->outFile   << atoms[i].getName()        << " "
                            << atoms[i].getPosition()[0] << " "
                            << atoms[i].getPosition()[1] << " "
                            << atoms[i].getPosition()[2] << " "
                            << endl;
        }
    }
}








