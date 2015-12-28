#pragma once
#include <iostream>
#include "QApplication"


class Sampler;
class Atom;
class InitialCondition;
class MainWindow;
class Potential;
class Integrator;
class vec;


class System {
public:
    System(int argc, char* argv[]);
    void setTimeStep(double);
    void setIntegrator(Integrator*);
    void setPotential(Potential*);
    void setInitialCondition(InitialCondition*);
    void setupGUI();
    void setupSystem();
    void integrate(int Nt, bool plotting);
    bool getPlotting() { return this->plotting; }

    QApplication app;

private:
    void plot();

    int               n;
    int               Nt;
    double            dt;
    bool              plotting;
    Integrator*       integrator;
    Potential*        potential;
    InitialCondition* initialCondition;
    Atom*             atoms;
    MainWindow*       mainWindow;
    Sampler*          sampler;
};

