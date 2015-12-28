#include <iostream>
#include <cmath>
#include <QApplication>
#include "../../qcustomplot/qcustomplot.h"
#include "GUI/mainwindow.h"
#include "system.h"
#include "atom.h"
#include "vec.h"
#include "sampler.h"
#include "Integrators/integrator.h"
#include "Integrators/eulercromer.h"
#include "Potentials/potential.h"
#include "Potentials/lennardjones.h"
#include "Potentials/gravitational.h"
#include "InitialConditions/initialcondition.h"
#include "InitialConditions/twobody.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    System system             (argc, argv);
    system.setupGUI           ();
    system.setIntegrator      (new EulerCromer(0.001));
    system.setPotential       (new Gravitational(4*acos(-1.0)*acos(-1.0)));
    system.setInitialCondition(new TwoBody(0.05));
    system.integrate          (2001, true);

    // If the plot is active, return the application handle.
    if (system.getPlotting()) {
        return system.app.exec();
    } else {
        return 0;
    }
}


