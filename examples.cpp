#include "examples.h"
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
#include "Integrators/velocityverlet.h"
#include "Potentials/potential.h"
#include "Potentials/lennardjones.h"
#include "Potentials/gravitational.h"
#include "Potentials/nopotential.h"
#include "InitialConditions/initialcondition.h"
#include "InitialConditions/twobody.h"
#include "InitialConditions/randomspherical.h"
#include "InitialConditions/uniform.h"
#include "InitialConditions/staticfcc.h"
#include "InitialConditions/fcc.h"
#include "Thermostats/thermostat.h"
#include "Thermostats/berendsenthermostat.h"


System* Examples::coldCollapseCluster(int argc, char** argv) {
    int     n   = 250;                              // Number of particles.
    double  dt  = 0.001;                            // Time step.
    double  R0  = 20;                               // Initial sphere radius.
    double  PI  = acos(-1.0);                       // Pi.
    double  G   = 4*PI*PI*R0*R0*R0/(32*10.0*n);     // Gravitational constant.
    double  eps = 0.01;                             // Smoothing factor.

    System* system = new System          (argc, argv, "../MD/movie.xyz");
    system->setIntegrator                (new EulerCromer(dt));
    system->setPotential                 (new Gravitational(G, eps));
    system->setInitialCondition          (new RandomSpherical(n, R0));
    system->setPeriodicBoundaryConditions(false);
    system->setSystemSize                (vec(2*R0));
    system->integrate(2000,false);
    return system;
}

System* Examples::uniformBoxNoPotential(int argc, char** argv) {
    int     n           = 250;              // Number of particles.
    double  dt          = 0.001;            // Time step.
    double  sideLength  = 1;                // Size of box sides.
    vec     boxSize     = vec(sideLength);  // Vector of box size.

    System* system = new System          (argc, argv, "../MD/movie.xyz");
    system->setIntegrator                (new EulerCromer(dt));
    system->setPotential                 (new NoPotential);
    system->setInitialCondition          (new Uniform(n, boxSize, 5));
    system->setPeriodicBoundaryConditions(true);
    system->setSystemSize                (boxSize);
    system->integrate(2000,false);
    return system;
}

System* Examples::staticFCCLattice(int argc, char** argv) {
    int     n = 5;                          // Number of unit cells in each dimension.
    double  b = 5.26;                       // Lattice constant [Å].
    double  dt          = 0.001;            // Time step.
    double  sideLength  = n*b;              // Size of box sides.
    vec     boxSize     = vec(sideLength);  // Vector of box size.

    System* system = new System          (argc, argv, "../MD/movie.xyz");
    system->setIntegrator                (new EulerCromer(dt));
    system->setPotential                 (new NoPotential);
    system->setInitialCondition          (new FCC(n, b, 0));
    system->setPeriodicBoundaryConditions(true);
    system->setSystemSize                (boxSize);
    system->integrate(1,false);
    return system;
}

System* Examples::lennardJonesFCC(int argc, char** argv) {
    int     n = 4;                          // Number of unit cells in each dimension.
    double  T = 0.2;                        // Temperature, in units of 119.8 K.
    double  b = 5.26;                       // Lattice constant, in units of 1.0 Å.
    double  dt          = 0.01;             // Time step.
    double  sideLength  = n*b;              // Size of box sides.
    vec     boxSize     = vec(sideLength);  // Vector of box size.

    System* system = new System          (argc, argv, "../MD/movie.xyz");
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setPotential                 (new LennardJones(1.0, 3.405, boxSize));
    system->setInitialCondition          (new FCC(n, b, T));
    system->setPeriodicBoundaryConditions(true);
    system->setSystemSize                (boxSize);
    system->integrate(1000, true);
    return system;
}

System*Examples::lennardJonesBerendsen(int argc, char** argv) {
    int     nUnitCells = 5;                 // Number of unit cells in each dimension.
    int     n = 4*std::pow(nUnitCells,3);   // Number of atoms.
    double  T           = 9.0;              // Temperature, in units of 119.8 K.
    double  TTarget     = 0.5;              // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    double  tau         = 10.0;             // Relaxation time used by the thermostat, in units of 119.8 K.
    double  b           = 5.26;             // Lattice constant, in units of 1.0 Å.
    double  dt          = 0.01;             // Time step.
    double  sideLength  = nUnitCells*b;     // Size of box sides.
    vec     boxSize     = vec(sideLength);  // Vector of box size.

    System* system = new System          (argc, argv, "../MD/movie.xyz");
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setPotential                 (new LennardJones(1.0, 3.405, boxSize));
    system->setInitialCondition          (new FCC(nUnitCells, b, T));
    system->setPeriodicBoundaryConditions(true);
    system->setThermostat                (new BerendsenThermostat(TTarget, tau, dt));
    system->setSystemSize                (boxSize);

    // Thermalize.
    system->setThermostatActive(false);
    system->integrate(1000, false);

    // Apply thermostat and integrate further.
    system->setThermostatActive(true);
    system->integrate(10000, false);

    // Allow thermalization in the new state.
    system->setThermostatActive(false);
    system->integrate(2000, false);

    return system;
}
