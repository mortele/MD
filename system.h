#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


class System {
public:
    System();
    void setTimeStep(double);
    void setIntegrator(class Integrator*);
    void setPotential(class Potential*);
    void setInitialCondition(class InitialCondition*);
    void setPeriodicBoundaryConditions(std::vector<double>);
    void setPeriodicBoundaryConditions(bool);
    void setThermostat(class Thermostat*);
    void setThermostatActive(bool);
    void setSystemSize(std::vector<double>);
    void setupSystem();
    void enablePressureSampling(bool enabled);
    bool integrate(int Nt);
    void applyPeriodicBoundaryConditions();
    void dumpInfoToTerminal();
    void printProgress(int);
    int  getN()                             { return m_n; }
    bool getPeriodicBoundaryConditions()    { return m_periodicBoundaryConditions; }
    std::vector<class Atom*>  getAtoms()    { return m_atoms; }
    std::vector<double> getSystemSize()     { return m_systemSize; }
    class Thermostat*   getThermostat()     { return m_thermostat; }

private:

    // Internal class for dumping positions to file.
    class FileOutput {
        public:
            FileOutput(const char*);
            ~FileOutput();
            bool saveState(std::vector<class Atom*> atoms, int n);

        private:
            int m_timeStep = 0;
            std::fstream m_outFile;
    };

    int                 m_skip                          = 0;
    int                 m_n                             = 0;
    int                 m_Nt                            = 0;
    double              m_dt                            = 0;
    double              m_oldTime                       = 0;
    double              m_currentTime                   = 0;
    double              m_startTime                     = 0;
    double              m_lastTimeStepTime              = 0;
    const char*         m_fileName;
    bool                m_periodicBoundaryConditions    = false;
    bool                m_thermostatActive              = false;
    bool                m_integrating                   = false;
    std::vector<double> m_systemSize                    = std::vector<double>(3);
    std::vector<double> m_totalMomentum                 = std::vector<double>(3);
    class Integrator*         m_integrator              = nullptr;
    class Potential*          m_potential               = nullptr;
    class InitialCondition*   m_initialCondition        = nullptr;
    std::vector<class Atom*>  m_atoms                   = std::vector<Atom*>();
    class Sampler*            m_sampler                 = nullptr;
    class Thermostat*         m_thermostat              = nullptr;
    FileOutput*               m_fileOutput              = nullptr;
};

