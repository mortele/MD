#include "system.h"
#include "Integrators/integrator.h"
#include "Potentials/potential.h"
#include "InitialConditions/initialcondition.h"
#include "Thermostats/thermostat.h"
#include "atom.h"
#include "sampler.h"
#include "realtime.h"


using std::cout;
using std::endl;
using std::ofstream;
using std::fstream;

System::System() :
    m_fileName("../MD/movie.xyz") {
    m_sampler           = new Sampler(this);
    m_systemSize        = std::vector<real>{-1,-1,-1}; // Used as flag for 'no system size set'
    m_thermostatActive  = false;
}

void System::setTimeStep(real dt) {
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

void System::setPeriodicBoundaryConditions(std::vector<real> systemSize) {
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

void System:: setThermostatActive(bool thermostatActive) {
    m_thermostatActive = thermostatActive;
}

void System::setTargetTemperature(real target) {
    m_thermostat->setTargetTemperature(target);
}

void System::setSystemSize(std::vector<real> systemSize) {
    m_systemSize = systemSize;
}

void System::setupSystem() {
    m_initialCondition->setupInitialCondition();
    m_n = m_initialCondition->getN();
    m_atoms = m_initialCondition->getAtoms();
    m_sampler->setupSampler(m_atoms, m_n);
    m_integrator->setPotential(m_potential);
}

void System::generateTestMatrix(double radius) {
    m_initialCondition->generateTestMatrix(radius);
}

void System::enablePressureSampling(bool enabled) {
    m_sampler->setPressureSamplingEnabled(enabled);
}



int System::integrate(int Nt) {
    m_Nt = Nt;
    if (m_integrating == false) {
        setupSystem();
        dumpInfoToTerminal();
        m_integrating = true;
        if (m_dumpToFile && m_fileOutput == nullptr) {
            m_fileOutput = new FileOutput(this, m_fileName);
        }
    }
    m_sampler->setNtDt(Nt,m_dt);

    if (m_systemSize[0] == -1 &&
        m_systemSize[1] == -1 &&
        m_systemSize[2] == -1) {
        cout << endl << "### WARNING ###: No system size set. Using default value (1,1,1)." << endl << endl;
        m_systemSize = std::vector<real>{1,1,1};
    }

    for (m_t=0; m_t < Nt; m_t++) {
        if (m_dumpToFile == true) {
            if (m_fileOutput == nullptr) {
                m_fileOutput = new FileOutput(this, m_fileName);
            }
            if (m_fileOutput->saveState(m_atoms, m_n) == false) {
                return false;
            }
        }
        m_sampler->sample(m_t);
        m_integrator->advance();

        if (m_periodicBoundaryConditions) {
            if (applyPeriodicBoundaryConditions() == false) {
                return false;
            }
        }
        if (m_thermostatActive) {
            real instantaneousTemperature = m_sampler->getInstantanousTemperature()[m_t];
            m_thermostat->adjustVelocities(instantaneousTemperature);
        }
        printProgress(m_t);
    }
    if (m_Nt != 0) {
        m_sampler->sample(Nt);
        printProgress(Nt);
    }

    return true;
}

void System::dumpInfoToTerminal() {
    vec systemSizeVec = vec(m_systemSize.at(0),
                            m_systemSize.at(1),
                            m_systemSize.at(2));
    m_totalMomentum = m_initialCondition->getTotalMomentum();
    vec totalMomentum = vec(m_totalMomentum.at(0),
                            m_totalMomentum.at(1),
                            m_totalMomentum.at(2));

    cout << " ┌──────────────────────────────────────────────────────┐ " << endl;
    cout << " │                Starting integration                  │ " << endl;
    cout << " └──┬───────────────────────────────────────────────────┘ " << endl;
    cout << "    │  Initial condition type: " << m_initialCondition->getName() << endl;
    cout << "    │  Integrator in use:      " << m_integrator->getName()       << endl;
    cout << "    │  Potential in use:       " << m_potential->getName()        << endl;
    cout << "    │  Saving state to file:   " << (m_dumpToFile ? "enabled" : "disabled") << endl;
    cout << "    │  Output file name:       " << m_fileName                    << endl;
    cout << "    ├─────────────────────────────────────────────────┐ " << endl;
    cout << "    │ Parameters                                      │ " << endl;
    cout << "    ├─────────────────────────────────────────────────┘ " << endl;
    cout << "    │  Number of atoms:        " << m_n             << endl;
    cout << "    │  Time step:              " << m_dt            << endl;
    cout << "    │  Number of time steps:   " << m_Nt            << endl;
    cout << "    │  Total time:             " << m_Nt*m_dt       << endl;
    cout << "    │  System size (cube):     " << systemSizeVec   << endl;
    cout << "    │  Total momentum removed: " << totalMomentum   << endl;
    cout << "    │  r_cut:                  " << m_potential->getRCut()   << endl;
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

        if (m_Nt < 100) {
            m_skip = 10;
        } else {
            m_skip = 100;
        }
    }
    if (t % m_skip == 0) {
        m_oldTime       = m_currentTime;
        m_currentTime   = getRealTime();
        if (t == 0) {
            m_lastTimeStepTime = m_currentTime-m_oldTime;
        }
        real progress     = ((real) t) / m_Nt;
        real elapsedTime  = m_currentTime - m_startTime;
        real lastTwoAverage = (m_currentTime-m_oldTime+m_lastTimeStepTime) / 2.0;
        if (t==m_skip) {
            lastTwoAverage = m_currentTime - m_startTime;
        }
        real estimatedTime = elapsedTime - elapsedTime+lastTwoAverage*(1-progress)*m_Nt/m_skip;

        real minutes = 0;
        if (estimatedTime > 200) {
            minutes = std::round(estimatedTime/60.0);
        }
        printf("Step %5d  ", t);
        if (estimatedTime > 200) {


            printf("(~%2.0f min) ", minutes);
        } else if (t == 0) {
            printf("(%7s) ", " ?");
        } else {
            printf("(%5.1f s) ", estimatedTime);
        }
        if (m_t!=0) {
            printf("Epot/N=%11.6f  Ekin/N=%11.6f  E/N=%11.6f  T=%11.6f  P=%11.6f  <r^2(t)>/6t=%11.6g \n",
                   m_sampler->getPotentialEnergies()[t]/m_n,
                   m_sampler->getKineticEnergies()[t]/m_n,
                   m_sampler->getEnergies()[t]/m_n,
                   m_sampler->getInstantanousTemperature()[t],
                   m_sampler->getPressures()[t],
                   m_sampler->getMeanSquareDisplacement()[t] / (6*m_dt*t));
        } else {
            printf("Epot/N=%11.6s  Ekin/N=%11.6f  E/N=%11.6s  T=%11.6f  P=%11.6f  <r^2(t)>/6t=%11.6s \n",
                   " ?",
                   m_sampler->getKineticEnergies()[t]/m_n,
                   " ?",
                   m_sampler->getInstantanousTemperature()[t],
                   m_sampler->getPressures()[t],
                   " ?");
        }
        fflush(stdout);
        m_lastTimeStepTime = m_currentTime-m_oldTime;
    }
    if (t == m_Nt) {
        real elapsedTime = m_currentTime - m_startTime;
        if (elapsedTime < 0) {
            elapsedTime = 0;
        }
        real timeStepsPerSecond       = m_Nt/elapsedTime;
        real atomTimeStepsPerSecond   = m_Nt*m_n/elapsedTime;

        cout << endl << endl << "Integration finished. Total elapsed time: "
             << elapsedTime << " s." << endl;
        if (timeStepsPerSecond > 1000) {
            cout << "Time steps/s : >1000." << endl;
            cout << "Atom-time steps/s : " << m_n << " k." << endl;
        } else {
            cout << "Time steps/s : " << timeStepsPerSecond << endl;
            cout << "Atom-time steps/s : " << atomTimeStepsPerSecond/1000 << " k." << endl;
        }
    }
}

void System::enableSavingToFile(bool dumpToFile) {
    if (dumpToFile && m_fileOutput == nullptr) {
        m_fileOutput = new FileOutput(this, m_fileName);
    }
    m_dumpToFile = dumpToFile;
    if (dumpToFile) {
        m_fileOutput->setFileOutputSkip(1);
    }

}

void System::enableSavingToFile(bool dumpToFile, int skip) {
    enableSavingToFile(dumpToFile);
    if (dumpToFile) {
        m_fileOutput->setFileOutputSkip(skip);
    }
}

bool System::saveSnapShot() {
    if (m_fileOutput == nullptr) {
        m_fileOutput = new FileOutput(this, " ");
    }
    m_fileOutput->saveSnapshot(m_atoms, m_n);
}


bool System::applyPeriodicBoundaryConditions() {
    real_posvel position[3];
    bool returnValue = true;

    for (int i=0; i < m_n; i++) {
        for (int k=0; k<3; k++) {
            position[k] = at(at(m_atoms,i)->getPosition(),k);

            if (position[k] >= at(m_systemSize,k)) {
                at(m_atoms,i)->addPosition(-at(m_systemSize,k), k);
            } else if (position[k] < 0) {
                at(m_atoms,i)->addPosition(at(m_systemSize,k), k);
            }
            /*if (at(at(m_atoms,i)->getPosition(), k) > at(m_systemSize,k) ||
                at(at(m_atoms,i)->getPosition(), k) < 0) {

                std::vector<real_posvel> atomPos = at(m_atoms,i)->getPosition();
                std::vector<real_posvel> atomVel = at(m_atoms,i)->getVelocity();
                vec pos = vec(atomPos.at(0), atomPos.at(1), atomPos.at(2));
                vec vel = vec(atomVel.at(0), atomVel.at(1), atomVel.at(2));

                cout << endl << "### ERROR ###: Atom number " << i
                     << " at position " << pos
                     << " has velocity " << vel
                     << " which is larger than the size of the box / time step. Exiting."
                     << endl << endl;

                returnValue = false;
            }*/
        }
    }
    return returnValue;
}





System::FileOutput::FileOutput(System* system, const char* fileName) {
    //m_outFile.open(fileName, std::ios::out);
    const char* fileNameTmp = "../MD/movie.xyz";
    m_outFile.open(fileNameTmp, std::ios::out);
    m_fileOutputSkip = 1;
    m_timeStep = 0;
    m_system = system;
}

System::FileOutput::~FileOutput() {
    if (m_outFile.is_open()) {
        m_outFile.close();
    }
}

bool System::FileOutput::saveState(std::vector<Atom*> atoms, int n) {
    if (m_outFile.is_open() == false) {
        cout << endl << "### ERROR ###: Could not open file. Exiting." << endl << endl;
        return false;
    } else {
        if (m_timeStep % m_fileOutputSkip == 0) {
            m_outFile << n << endl;
            m_outFile << "Time step: " << m_timeStep++ << endl;

            for (int i = 0; i < n; i++) {
                m_outFile       << atoms.at(i)->getName()           << " "
                                << std::setprecision(10)
                                << atoms.at(i)->getPosition().at(0) << " "
                                << atoms.at(i)->getPosition().at(1) << " "
                                << atoms.at(i)->getPosition().at(2) << " "
                                << endl;
            }
            return true;
        } else {
            m_timeStep++;
        }
    }
    return true;
}

bool System::FileOutput::saveSnapshot(std::vector<Atom*> atoms, int n) {
    const char* snapShotFileName ="../MD/snapShot.dat";
    m_snapShotFile.open(snapShotFileName, std::ios::out);

    if (m_snapShotFile.is_open() == false) {
        cout << endl << "### ERROR ###: Could not open snap shot file. Exiting." << endl << endl;
        return false;
    } else {
        m_snapShotFile << n << " " << m_system->getSystemSize().at(0)
                       << " " << m_system->getSystemSize().at(1)
                       << " " << m_system->getSystemSize().at(2)
                       << endl;
        for (int i = 0; i < n; i++) {
            m_snapShotFile  << atoms.at(i)->getName()           << " "
                            << std::setprecision(15)
                            << atoms.at(i)->getPosition().at(0) << " "
                            << atoms.at(i)->getPosition().at(1) << " "
                            << atoms.at(i)->getPosition().at(2) << " "
                            << atoms.at(i)->getVelocity().at(0) << " "
                            << atoms.at(i)->getVelocity().at(1) << " "
                            << atoms.at(i)->getVelocity().at(2) << " "
                            << atoms.at(i)->getMass()           << " "
                            << endl;
        }
        return true;
    }
}

void System::FileOutput::setFileOutputSkip(int fileOutputSkip) {
    m_fileOutputSkip = fileOutputSkip;
}








