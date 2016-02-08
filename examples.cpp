#include "examples.h"
#include <iostream>
#include <fstream>
#include <tgmath.h>
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
#include "Potentials/lennardjonescelllists.h"
#include "Potentials/lennardjonesneighbourlists.h"
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

int Examples::coldCollapseCluster() {
    int     n   = 250;                              // Number of particles.
    real  dt  = 0.001;                            // Time step.
    real  R0  = 20;                               // Initial sphere radius.
    real  PI  = acos(-1.0);                       // Pi.
    real  G   = 4*PI*PI*R0*R0*R0/(32*10.0*n);     // Gravitational constant.
    real  eps = 0.01;                             // Smoothing factor.
    real  sideLength = 2*R0;
    std::vector<real> boxSize{sideLength,         // Vector of box size.
                                sideLength,
                                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new EulerCromer(dt));
    system->setPotential                 (new Gravitational(G, eps, system));
    system->setInitialCondition          (new RandomSpherical(n, R0));
    system->setPeriodicBoundaryConditions(false);
    system->setSystemSize                (boxSize);
    return system->integrate(2000);
}

int Examples::uniformBoxNoPotential() {
    int     n           = 250;              // Number of particles.
    real  dt          = 0.001;            // Time step.
    real  sideLength  = 1;                // Size of box sides.
    std::vector<real> boxSize{sideLength, // Vector of box size.
                                sideLength,
                                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new EulerCromer(dt));
    system->setPotential                 (new NoPotential(system));
    system->setInitialCondition          (new Uniform(n, boxSize, 5));
    system->setPeriodicBoundaryConditions(true);
    system->setSystemSize                (boxSize);
    return system->integrate(2000);
}

int Examples::lennardJonesFCC() {
    int   nUnitCells          = 6;    // Number of unit cells in each dimension.
    real  T                   = 1.0;   // Temperature, in units of 119.8 K.
    real  targetTemperature   = 1.0;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    real  b                   = 5.26;  // Lattice constant, in units of 1.0 Å.
    real  dt                  = 0.0997765; // Time step.
    real  tau                 = dt;    // Relaxation time used by the thermostat, in units of 119.8 K.
    real  sideLength          = nUnitCells*b; // Size of box sides.
    real  epsilon             = 1;
    real  sigma               = 3.405;
    real  rCut                = 2.5*sigma;
    std::vector<real> boxSize{sideLength,     // Vector of box size.
                                sideLength,
                                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setPotential                 (new LennardJones(epsilon, sigma, boxSize, rCut, system));
    system->setInitialCondition          (new FCC(nUnitCells, b, T));
    system->setPeriodicBoundaryConditions(true);
    system->setThermostat                (new BerendsenThermostat(system, targetTemperature, tau, dt));
    system->setSystemSize                (boxSize);
    system->setThermostatActive          (false);
    system->enablePressureSampling       (true);
    system->enableSavingToFile           (true, 25);
    return system->integrate(1000);
}

int Examples::lennardJonesFCCCellLists() {
    int   nUnitCells          = 8;    // Number of unit cells in each dimension.
    real  T                   = 1.0;   // Temperature, in units of 119.8 K.
    real  targetTemperature   = 1.0;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    real  b                   = 5.26;  // Lattice constant, in units of 1.0 Å.
    real  dt                  = 0.0997765; // Time step.
    real  tau                 = dt;    // Relaxation time used by the thermostat, in units of 119.8 K.
    real  sideLength          = nUnitCells*b; // Size of box sides.
    real  epsilon             = 1;
    real  sigma               = 3.405;
    real  rCut                = 2.5 * sigma;
    real  rNeighbourCut       = 3.0 * sigma;
    std::vector<real> boxSize{sideLength,     // Vector of box size.
                                sideLength,
                                sideLength};

    if (sideLength < 3*rCut) {
        cout << endl << "### WARNING ###: System size smaller than 3 sigma, may cause segfault." << endl << endl;
    }

    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setPotential                 (new LennardJonesCellLists(epsilon, sigma, boxSize, rCut, system));
    system->setInitialCondition          (new FCC(nUnitCells, b, T));
    system->setPeriodicBoundaryConditions(true);
    system->setThermostat                (new BerendsenThermostat(system, targetTemperature, tau, dt));
    system->setSystemSize                (boxSize);
    system->setThermostatActive          (false);
    system->enablePressureSampling       (true);
    system->enableSavingToFile           (true, 25);
    return system->integrate(1000);
}

int Examples::lennardJonesFCCNeighbourLists() {
    int   nUnitCells          = 20;    // Number of unit cells in each dimension.
    real  T                   = 1.0;   // Temperature, in units of 119.8 K.
    real  targetTemperature   = 1.0;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    real  b                   = 5.26;  // Lattice constant, in units of 1.0 Å.
    real  dt                  = 0.0997765; // Time step.
    real  tau                 = dt;    // Relaxation time used by the thermostat, in units of 119.8 K.
    real  sideLength          = nUnitCells*b; // Size of box sides.
    real  epsilon             = 1;
    real  sigma               = 3.405;
    real  rCut                = 2.5 * sigma;
    real  rNeighbourCut       = 3.0 * sigma;
    std::vector<real> boxSize{sideLength,     // Vector of box size.
                                sideLength,
                                sideLength};

    if (sideLength < 3*rCut) {
        cout << endl << "### WARNING ###: System size smaller than 3 sigma, may cause segfault." << endl << endl;
    }

    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setPotential                 (new LennardJonesNeighbourLists(epsilon, sigma, boxSize, rCut, rNeighbourCut, system));
    system->setInitialCondition          (new FCC(nUnitCells, b, T));
    system->setPeriodicBoundaryConditions(true);
    system->setThermostat                (new BerendsenThermostat(system, targetTemperature, tau, dt));
    system->setSystemSize                (boxSize);
    system->setThermostatActive          (false);
    system->enablePressureSampling       (true);
    system->enableSavingToFile           (false);
    return system->integrate(1000);
}


















