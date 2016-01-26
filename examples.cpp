#include "examples.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "system.h"
#include "atom.h"
#include "vec.h"
#include "random.h"
#include "sampler.h"
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
#include "InitialConditions/fcc.h"
#include "Thermostats/thermostat.h"
#include "Thermostats/berendsenthermostat.h"

using std::cout;
using std::endl;

System* Examples::coldCollapseCluster() {
    int     n   = 250;                              // Number of particles.
    double  dt  = 0.001;                            // Time step.
    double  R0  = 20;                               // Initial sphere radius.
    double  PI  = acos(-1.0);                       // Pi.
    double  G   = 4*PI*PI*R0*R0*R0/(32*10.0*n);     // Gravitational constant.
    double  eps = 0.01;                             // Smoothing factor.
    double  sideLength = 2*R0;
    std::vector<double> boxSize{sideLength,         // Vector of box size.
                                sideLength,
                                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new EulerCromer(dt));
    system->setPotential                 (new Gravitational(G, eps, system));
    system->setInitialCondition          (new RandomSpherical(n, R0));
    system->setPeriodicBoundaryConditions(false);
    system->setSystemSize                (boxSize);
    system->integrate(2000);
    return system;
}

System* Examples::uniformBoxNoPotential() {
    int     n           = 250;              // Number of particles.
    double  dt          = 0.001;            // Time step.
    double  sideLength  = 1;                // Size of box sides.
    std::vector<double> boxSize{sideLength, // Vector of box size.
                                sideLength,
                                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new EulerCromer(dt));
    system->setPotential                 (new NoPotential(system));
    system->setInitialCondition          (new Uniform(n, boxSize, 5));
    system->setPeriodicBoundaryConditions(true);
    system->setSystemSize                (boxSize);
    system->integrate(2000);
    return system;
}

System* Examples::staticFCCLattice() {
    int     n = 8;                          // Number of unit cells in each dimension.
    double  b = 5.26;                       // Lattice constant [Å].
    double  dt          = 0.001;            // Time step.
    double  sideLength  = n*b;              // Size of box sides.
    std::vector<double> boxSize{sideLength, // Vector of box size.
                                sideLength,
                                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new EulerCromer(dt));
    system->setPotential                 (new NoPotential(system));
    system->setInitialCondition          (new FCC(n, b, 0));
    system->setPeriodicBoundaryConditions(true);
    system->setSystemSize                (boxSize);
    system->integrate(1);
    return system;
}

System* Examples::lennardJonesFCC() {
    int     nUnitCells = 4;                 // Number of unit cells in each dimension.
    double  T = 1.0;                        // Temperature, in units of 119.8 K.
    double  b = 5.26;                       // Lattice constant, in units of 1.0 Å.
    double  dt          = 0.01;             // Time step.
    double  sideLength  = nUnitCells*b;     // Size of box sides.
    std::vector<double> boxSize{sideLength, // Vector of box size.
                                sideLength,
                                sideLength};


    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setPotential                 (new LennardJones(1.0, 3.405, boxSize, system));
    system->setInitialCondition          (new FCC(nUnitCells, b, T));
    system->setPeriodicBoundaryConditions(true);
    system->setSystemSize                (boxSize);
    system->integrate(1000);
    return system;
}

System*Examples::lennardJonesBerendsen() {
    int     nUnitCells = 4;                 // Number of unit cells in each dimension.
    int     n = 4*std::pow(nUnitCells,3);   // Number of atoms.
    double  T           = 1.0;              // Temperature, in units of 119.8 K.
    double  TTarget     = 0.5;              // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    double  tau         = 10.0;             // Relaxation time used by the thermostat, in units of 119.8 K.
    double  b           = 5.26;             // Lattice constant, in units of 1.0 Å.
    double  dt          = 0.01;             // Time step.
    double  sideLength  = nUnitCells*b;     // Size of box sides.
    std::vector<double> boxSize{sideLength, // Vector of box size.
                                sideLength,
                                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setPotential                 (new LennardJones(1.0, 3.405, boxSize, system));
    system->setInitialCondition          (new FCC(nUnitCells, b, T));
    system->setPeriodicBoundaryConditions(true);
    system->setThermostat                (new BerendsenThermostat(TTarget, tau, dt));
    system->setSystemSize                (boxSize);

    system->setThermostatActive(true);
    system->integrate(2000);

    return system;
}

System*Examples::lennardJonesCellLists() {
    int     nUnitCells  = 8;                // Number of unit cells in each dimension.
    double  T           = 1.0;              // Temperature, in units of 119.8 K.
    double  b           = 5.26;             // Lattice constant, in units of 1.0 Å.
    double  dt          = 0.01;             // Time step.
    double  sideLength  = nUnitCells*b;     // Size of box sides.
    std::vector<double> boxSize{sideLength, // Vector of box size.
                                sideLength,
                                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setPotential                 (new LennardJones(1.0, 3.405, boxSize, 2*b, system));
    system->setInitialCondition          (new FCC(nUnitCells, b, T));
    system->setPeriodicBoundaryConditions(true);
    system->setSystemSize                (boxSize);
    system->integrate(100);
    return system;
}

System*Examples::lennardJonesBerendsenCellLists() {
    int     nUnitCells   = 10;               // Number of unit cells in each dimension.
    int     n = 4*std::pow(nUnitCells,3);   // Number of atoms.
    double  T            = 1.0;             // Temperature, in units of 119.8 K.
    double  TTarget      = 1.0;             // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    double  tau          = 0.1;             // Relaxation time used by the thermostat, in units of 119.8 K.
    double  b            = 5.26;            // Lattice constant, in units of 1.0 Å.
    double  dt           = 0.01;            // Time step.
    double  sideLength   = nUnitCells*b;    // Size of box sides.
    const char* fileName = "../MD/movie.xyz";
    std::vector<double> boxSize{sideLength, // Vector of box size.
                                sideLength,
                                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setPotential                 (new LennardJones(1.0, 3.405, boxSize, 2*b, system));
    system->setInitialCondition          (new FCC(nUnitCells, b, T));
    system->setPeriodicBoundaryConditions(true);
    system->setThermostat                (new BerendsenThermostat(TTarget, tau, dt));
    system->setSystemSize                (boxSize);

    system->setThermostatActive(true);
    system->integrate(20);

    //system->setThermostatActive(false);
    //system->integrate(200);


    return system;
}


















