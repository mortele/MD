#include "system.h"


using std::cout;
using std::endl;
using std::ofstream;
using std::fstream;

System::System(int argc, char** argv, char* fileName) :
    m_app(argc, argv) {

    m_fileName          = fileName;
    m_sampler           = new Sampler;
    m_systemSize        = std::vector<double>{-1,-1,-1}; // Used as flag for 'no system size set'
    m_thermostatActive  = false;
}

void System::setTimeStep(double dt) {
    m_dt = dt;
}

void System::setIntegrator(Integrator* integrator) {
    m_integrator = integrator;
    m_dt = integrator->getTimeStep();
}

void System::setPotential(Potential* potential) {
    m_potential = potential;
    m_sampler->setPotential(potential);
}

void System::setInitialCondition(InitialCondition* initialCondition) {
    m_initialCondition = initialCondition;
}

void System::setPeriodicBoundaryConditions(std::vector<double> systemSize) {
    m_periodicBoundaryConditions = true;
    m_systemSize                 = systemSize;
}

void System::setPeriodicBoundaryConditions(bool periodicBoundaryConditions) {
    m_periodicBoundaryConditions = periodicBoundaryConditions;
}

void System::setThermostat(Thermostat* thermostat) {
    m_thermostat = thermostat;
    m_thermostatActive = true;
}

void System::setThermostatActive(bool thermostatActive) {
    m_thermostatActive = thermostatActive;
}

void System::setSystemSize(std::vector<double> systemSize) {
    m_systemSize = systemSize;
}

void System::setupGUI() {
    m_skip = 25;
    m_mainWindow = new MainWindow;
}

void System::setupSystem() {
    m_initialCondition->setupInitialCondition();
    m_atoms = m_initialCondition->getAtoms();
    m_n     = m_initialCondition->getN();
    m_sampler->setupSampler(m_atoms, m_n);
    m_integrator->setPotential(m_potential);
    m_fileOutput = new FileOutput(m_fileName);
}

void System::integrate(int Nt) {
    integrate(Nt, true);
}


void System::integrate(int Nt, bool plotting) {    
    if (m_integrating == false) {
        setupSystem();
        m_integrating = true;
    }

    if (m_systemSize[0] == -1 &&
        m_systemSize[1] == -1 &&
        m_systemSize[2] == -1) {
        cout << endl << "### WARNING ###: No system size set. Using default value (1,1,1)." << endl << endl;
        m_systemSize = std::vector<double>{1,1,1};
    }
    m_plotting = plotting;
    if (m_plotting) {
        setupGUI();
        m_mainWindow->show();
    }
    m_Nt       = Nt;
    m_sampler->setNtDt(Nt,m_dt);

    for (int t=0; t < Nt; t++) {
        m_fileOutput->saveState(m_atoms, m_n);
        m_sampler->sample(t);

        m_integrator->advance(m_atoms, m_n);

        if (m_periodicBoundaryConditions) {
            applyPeriodicBoundaryConditions();
        }
        if (m_thermostatActive) {
            double instantaneousTemperature = m_sampler->getInstantanousTemperature()[t];
            m_thermostat->adjustVelocities(m_atoms, m_n, instantaneousTemperature);
        }
        printProgress(t);
    }
    printProgress(Nt);

    if (m_plotting) {
        plot();
    }
}

void System::dumpInfoToTerminal() {
    vec systemSizeVec = vec(m_systemSize.at(0),
                            m_systemSize.at(1),
                            m_systemSize.at(2));
    cout << " ┌──────────────────────────────────────────────────────┐ " << endl;
    cout << " │                Starting integration                  │ " << endl;
    cout << " └──┬───────────────────────────────────────────────────┘ " << endl;
    cout << "    │  Initial condition type: " << m_initialCondition->getName() << endl;
    cout << "    │  Integrator in use:      " << m_integrator->getName()       << endl;
    cout << "    │  Potential in use:       " << m_potential->getName()        << endl;
    cout << "    │  Output file name:       " << m_fileName                    << endl;
    cout << "    ├─────────────────────────────────────────────────┐ " << endl;
    cout << "    │ Parameters                                      │ " << endl;
    cout << "    ├─────────────────────────────────────────────────┘ " << endl;
    cout << "    │  Number of atoms:        " << m_n             << endl;
    cout << "    │  Time step:              " << m_dt            << endl;
    cout << "    │  Number of time steps:   " << m_Nt            << endl;
    cout << "    │  Total time:             " << m_Nt*m_dt       << endl;
    cout << "    │  System size (cube):     " << systemSizeVec   << endl;
    cout << "    ├─────────────────────────────────────────────────┐ " << endl;
    cout << "    │ Progress                                        │ " << endl;
    cout << "    └─────────────────────────────────────────────────┘ " << endl;
}

void System::printProgress(int t) {
    if (t==0) {
        m_startTime = getRealTime();
        m_currentTime = m_startTime;
        m_oldTime   = m_startTime;
        m_lastTimeStepTime = 0;
        dumpInfoToTerminal();
        if (m_Nt < 100) {
            m_skip = 1;
        } else {
            m_skip = 5;
        }
    }
    if (t % m_skip == 0) {
        m_oldTime       = m_currentTime;
        m_currentTime   = getRealTime();
        double progress     = ((double) t) / m_Nt;
        double elapsedTime  = m_currentTime - m_startTime;
        double estimatedTime = elapsedTime+
                               (m_currentTime-m_oldTime+m_lastTimeStepTime)*
                               (1-progress)*m_skip/2.0;
        double minutes = 0;
        if (estimatedTime > 200) {
            minutes = std::round(estimatedTime/60.0);
        }
        cout << "                                                                             \r";
        printf("\r %5.1f %s : %5.1f s ",
               progress*100, "%",
               elapsedTime);

        if (estimatedTime > 200) {
            printf("(~%.0f min) ", minutes);
        } else {
            printf("(%5.1f s) ", estimatedTime);
        }
        printf("E = %5.1f  T = %5.1f \r",
               m_sampler->getEnergies()[t],
               m_sampler->getInstantanousTemperature()[t]);
        fflush(stdout);
        m_lastTimeStepTime = m_currentTime-m_oldTime;
    }
    if (t == m_Nt) {
        double elapsedTime = m_currentTime - m_startTime;
        if (elapsedTime < 0) {
            elapsedTime = 0;
        }
        cout << "                                                                             ";
        cout << endl << "Integration finished. Total elapsed time: " << elapsedTime << endl;
    }
}

void System::plot() {
    m_mainWindow->plot(m_n, m_Nt, m_sampler);
    m_mainWindow->show();
}



void System::applyPeriodicBoundaryConditions() {
    std::vector<double> position{0,0,0};

    for (int i=0; i < m_n; i++) {
        bool changed = false;

        for (int k=0; k<3; k++) {
            position.at(k) = m_atoms[i].getPosition().at(k);

            if (position.at(k) > m_systemSize.at(k)) {
                changed = true;
                m_atoms[i].setPosition(position.at(k) - m_systemSize.at(k), k);
            } else if (position.at(k) < 0) {
                changed = true;
                m_atoms[i].setPosition(position.at(k) + m_systemSize.at(k), k);
            }
        }
    }
}





System::FileOutput::FileOutput(char* fileName) {
    m_outFile.open(fileName, std::ios::out);
}

System::FileOutput::~FileOutput() {
    if (m_outFile.is_open()) {
        m_outFile.close();
    }
}

void System::FileOutput::saveState(Atom* atoms, int n) {
    if (true) {//(m_outFile.is_open()) {
        m_outFile << n << endl;
        m_outFile << "Comment line" << endl;

        for (int i = 0; i < n; i++) {
            m_outFile       << atoms[i].getName()        << " "
                            << atoms[i].getPosition()[0] << " "
                            << atoms[i].getPosition()[1] << " "
                            << atoms[i].getPosition()[2] << " "
                            << endl;
        }
    }
}








