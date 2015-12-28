#include "system.h"
#include "Integrators/integrator.h"
#include "Potentials/potential.h"
#include "InitialConditions/initialcondition.h"
#include "GUI/mainwindow.h"
#include "vec.h"
#include "atom.h"
#include "sampler.h"

using std::cout;
using std::endl;

System::System(int argc, char* argv[]) :
    app(argc, argv) {

    this->sampler = new Sampler;
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
    this->mainWindow = new MainWindow;

}

void System::setupSystem() {
    this->initialCondition->setupInitialCondition();
    this->atoms = this->initialCondition->getAtoms();
    this->n = initialCondition->getN();
    this->sampler->setupSampler(this->atoms, this->n);
    this->integrator->setPotential(this->potential);
}

void System::integrate(int Nt, bool plotting) {
    this->setupSystem();

    this->plotting = plotting;
    this->Nt       = Nt;
    this->sampler->setNtDt(Nt,this->dt);

    for (int t=0; t < Nt; t++) {
        //this->potential->computeForces(this->atoms, this->n);
        this->integrator->advance     (this->atoms, this->n);
        this->sampler->sample(t);
    }

    if (this->plotting) {
        this->plot();
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






