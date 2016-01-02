#pragma once
#include <iostream>
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

class Sampler;


class System {
public:
    System(int, char**, char*);
    void setTimeStep(double);
    void setIntegrator(Integrator*);
    void setPotential(Potential*);
    void setInitialCondition(InitialCondition*);
    void setupGUI();
    void setupSystem();
    void integrate(int Nt);
    void integrate(int Nt, bool plotting);
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
    char*             fileName;
    bool              plotting;
    Integrator*       integrator;
    Potential*        potential;
    InitialCondition* initialCondition;
    Atom*             atoms;
    MainWindow*       mainWindow;
    Sampler*          sampler;
    FileOutput*       fileOutput;
};

