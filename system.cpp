#include "system.h"


using std::cout;
using std::endl;
using std::ofstream;
using std::fstream;

System::System(int argc, char* argv[], char* fileName) :
    app(argc, argv) {

    this->fileName = fileName;
    this->sampler  = new Sampler;
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

    // Set up the real time plot if plotting is enabled.
    this->plotting = plotting;
    if (this->plotting) {
        //this->mainWindow->setup(Nt);
        this->mainWindow->show();
    }
    this->Nt       = Nt;
    this->sampler->setNtDt(Nt,this->dt);

    for (int t=0; t < Nt; t++) {
        this->integrator->advance(this->atoms, this->n);
        this->fileOutput->saveState(this->atoms, this->n);
        this->sampler->sample(t);
        this->printProgress(t);
    }
    this->printProgress(Nt);
    this->plot();
}

void System::dumpInfoToTerminal() {
    cout << " ┌────────────────────────────────────────────────────┐ " << endl;
    cout << " │               Starting integration                 │ " << endl;
    cout << " └──┬─────────────────────────────────────────────────┘ " << endl;
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
    cout << "    ├─────────────────────────────────────────────────┐ " << endl;
    cout << "    │ Progress                                        │ " << endl;
    cout << "    └─────────────────────────────────────────────────┘ " << endl;
}

void System::printProgress(int t) {
    int nBoxes   = 40;
    if (t==0) {
        this->dumpInfoToTerminal();
    }
    if (t % (Nt/100) == 0) {
        double progress = ((double) t) / Nt;
        cout << "     [";
        for (int i=0; i < std::floor(nBoxes*progress); i++) {
            cout << "█";
        }
        for (int i=nBoxes*progress; i < nBoxes; i++) {
            cout << " ";
        }
        cout << "]  " << 100*progress << " % \r";
        fflush(stdout);
    }
    if (t == this->Nt) {
        cout << "     [";
        for (int i = 0; i < nBoxes; i++) {
            cout << "█";
        }
        cout << "]  100 %" << endl;
    }
}

void System::plot() {
    double*** positions = this->sampler->getPositions();
    double*   xPosition = new double[this->Nt];
    double*   yPosition = new double[this->Nt];

    for (int i=0; i < this->Nt; i++) {
        xPosition[i] = positions[i][1][0];
        yPosition[i] = positions[i][1][1];
    }

    this->mainWindow->plot(this->Nt,
                           xPosition,
                           yPosition,
                           this->sampler->getTime(),
                           this->sampler->getEnergies());
    this->mainWindow->show();
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
            this->outFile << "Ar " << atoms[i].getPosition()[0] << " "
                                   << atoms[i].getPosition()[1] << " "
                                   << atoms[i].getPosition()[2] << " "
                                   << endl;
        }
    }
}








