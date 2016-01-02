#include <iostream>
#include <fstream>
#include <cmath>
#include <QApplication>
#include "../../qcustomplot/qcustomplot.h"
#include "system.h"
#include "atom.h"
#include "vec.h"
#include "random.h"
#include "sampler.h"
#include "GUI/mainwindow.h"
#include "Integrators/integrator.h"
#include "Integrators/eulercromer.h"
#include "Potentials/potential.h"
#include "Potentials/lennardjones.h"
#include "Potentials/gravitational.h"
#include "InitialConditions/initialcondition.h"
#include "InitialConditions/twobody.h"
#include "InitialConditions/randomspherical.h"

using std::cout;
using std::endl;

/* FIXME: Make real time plotting work--need to be able to compute stuff in
 *        System, but update the plot in MainWindow in real time.
 * FIXME: Clean up MainWindow class and the integrate method in System.
 *
 * TODO: Velocity Verlet integrator.
 * TODO: Add FCC lattice initial condition.
 * TODO: Add option to dump positions to .xyz file for visualization in VMD.
 * TODO: Add periodic boundary conditions.
 * TODO: Add Lennard-Jones potential.
 * TODO: Add boundary condition class--periodic, hard box, none, etc.
 */

int main(int argc, char* argv[]) {
    int     n   = 250;                              // Number of particles.
    int     Nt  = 2000;                             // Number of time steps.
    double  dt  = 0.001;                            // Time step.
    double  R0  = 20;                               // Initial sphere radius.
    double  PI  = acos(-1.0);                       // Pi.
    double  G   = 4*PI*PI*R0*R0*R0/(32*10.0*n);     // Gravitational constant.
    double  eps = 0.01;                             // Smoothing factor.

    System system             (argc, argv, "../MD/movie.xyz");
    system.setupGUI           ();
    system.setIntegrator      (new EulerCromer(dt));
    system.setPotential       (new Gravitational(G, eps));
    system.setInitialCondition(new RandomSpherical(n, R0));
    system.integrate          (Nt);

    // If the plot is active, return the application handle.
    if (system.getPlotting()) {
        return system.app.exec();
    } else {
        return 0;
    }
}


