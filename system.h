#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "vec.h"


class System {
public:
    System();
    void setTimeStep(real);
    void setIntegrator(class Integrator*);
    void setPotential(class Potential*);
    void setInitialCondition(class InitialCondition*);
    void setPeriodicBoundaryConditions(std::vector<real>);
    void setPeriodicBoundaryConditions(bool);
    void setThermostat(class Thermostat*);
    void setThermostatActive(bool);
    void setSystemSize(std::vector<real>);
    void setupSystem();
    void enablePressureSampling(bool enabled);
    int integrate(int Nt);
    bool applyPeriodicBoundaryConditions();
    void dumpInfoToTerminal();
    void printProgress(int);
    void enableSavingToFile(bool);
    void enableSavingToFile(bool, int);
    int  getN()                             { return m_n; }
    int  getT()                             { return m_t; }
    bool getPeriodicBoundaryConditions()    { return m_periodicBoundaryConditions; }
    std::vector<class Atom*>&  getAtoms()   { return m_atoms; }
    std::vector<real>& getSystemSize()    { return m_systemSize; }
    class Thermostat*   getThermostat()     { return m_thermostat; }

private:

    // Internal class for dumping positions to file.
    class FileOutput {
        public:
            FileOutput(const char*);
            ~FileOutput();
            bool saveState(std::vector<class Atom*> atoms, int n);
            void setFileOutputSkip(int fileOutputSkip);

        private:
            int m_fileOutputSkip = 1;
            int m_timeStep = 0;
            std::fstream m_outFile;
    };

    int                 m_skip                          = 0;
    int                 m_n                             = 0;
    int                 m_Nt                            = 0;
    int                 m_t                             = 0;
    real              m_dt                            = 0;
    real              m_oldTime                       = 0;
    real              m_currentTime                   = 0;
    real              m_startTime                     = 0;
    real              m_lastTimeStepTime              = 0;
    const char*         m_fileName;
    bool                m_periodicBoundaryConditions    = false;
    bool                m_thermostatActive              = false;
    bool                m_integrating                   = false;
    bool                m_dumpToFile                    = true;
    std::vector<real> m_systemSize                    = std::vector<real>(3);
    std::vector<real> m_totalMomentum                 = std::vector<real>(3);
    class Integrator*         m_integrator              = nullptr;
    class Potential*          m_potential               = nullptr;
    class InitialCondition*   m_initialCondition        = nullptr;
    std::vector<class Atom*>  m_atoms                   = std::vector<Atom*>();
    class Sampler*            m_sampler                 = nullptr;
    class Thermostat*         m_thermostat              = nullptr;
    FileOutput*               m_fileOutput              = nullptr;
};

