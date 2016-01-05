#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "QApplication"
#include "Integrators/integrator.h"
#include "Potentials/potential.h"
#include "InitialConditions/initialcondition.h"
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
    void setPeriodicBoundaryConditions(vec);
    void setPeriodicBoundaryConditions(bool);
    void setSystemSize(vec);
    void setupGUI();
    void setupSystem();
    void integrate(int Nt);
    void integrate(int Nt, bool plotting);
    void applyPeriodicBoundaryConditions();
    void dumpInfoToTerminal();
    void printProgress(int);
    bool getPlotting() { return this->plotting; }

    QApplication app;

private:

    // Internal class for dumping positions to file.
    class FileOutput {
        public:
            FileOutput(char*);
            ~FileOutput();
            void saveState(Atom* atoms, int n);

        private:
            std::fstream outFile;
    }; // end FileOutput

    void plot();

    int               skip;
    int               n;
    int               Nt;
    double            dt;
    double            oldTime;
    double            currentTime;
    double            startTime;
    char*             fileName;
    bool              plotting;
    bool              periodicBoundaryConditions;
    vec               systemSize;
    Integrator*       integrator;
    Potential*        potential;
    InitialCondition* initialCondition;
    Atom*             atoms;
    MainWindow*       mainWindow;
    Sampler*          sampler;
    FileOutput*       fileOutput;
};

