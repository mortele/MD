#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "QApplication"
#include "Integrators/integrator.h"
#include "Potentials/potential.h"
#include "InitialConditions/initialcondition.h"
#include "Thermostats/thermostat.h"
#include "GUI/mainwindow.h"
#include "vec.h"
#include "atom.h"
#include "sampler.h"
#include "realtime.h"


class Sampler;


class System {
public:
    System(int, char**, char*);
    void setTimeStep(double);
    void setIntegrator(Integrator*);
    void setPotential(Potential*);
    void setInitialCondition(InitialCondition*);
    void setPeriodicBoundaryConditions(std::vector<double>);
    void setPeriodicBoundaryConditions(bool);
    void setThermostat(Thermostat*);
    void setThermostatActive(bool);
    void setSystemSize(std::vector<double>);
    void setupGUI();
    void setupSystem();
    void integrate(int Nt);
    void integrate(int Nt, bool plotting);
    void applyPeriodicBoundaryConditions();
    void dumpInfoToTerminal();
    void printProgress(int);
    bool getPlotting() { return m_plotting; }
    bool getPeriodicBoundaryConditions() { return m_periodicBoundaryConditions; }
    std::vector<Atom*> getAtoms() { return m_atoms; }

    QApplication m_app;

private:

    // Internal class for dumping positions to file.
    class FileOutput {
        public:
            FileOutput(char*);
            ~FileOutput();
            void saveState(std::vector<Atom*> atoms, int n);

        private:
            std::fstream m_outFile;
    };

    void plot();

    int                 m_skip                          = 0;
    int                 m_n                             = 0;
    int                 m_Nt                            = 0;
    double              m_dt                            = 0;
    double              m_oldTime                       = 0;
    double              m_currentTime                   = 0;
    double              m_startTime                     = 0;
    double              m_lastTimeStepTime              = 0;
    char*               m_fileName                      = nullptr;
    bool                m_plotting                      = false;
    bool                m_periodicBoundaryConditions    = false;
    bool                m_thermostatActive              = false;
    bool                m_integrating                   = false;
    std::vector<double> m_systemSize                    = std::vector<double>(3);
    std::vector<double> m_totalMomentum                 = std::vector<double>(3);
    Integrator*         m_integrator                    = nullptr;
    Potential*          m_potential                     = nullptr;
    InitialCondition*   m_initialCondition              = nullptr;
    std::vector<Atom*>  m_atoms                         = std::vector<Atom*>();
    MainWindow*         m_mainWindow                    = nullptr;
    Sampler*            m_sampler                       = nullptr;
    FileOutput*         m_fileOutput                    = nullptr;
    Thermostat*         m_thermostat                    = nullptr;
};

