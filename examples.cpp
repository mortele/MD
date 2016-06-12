#include "examples.h"
#include <iostream>
#include <iomanip>
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
#include "Potentials/lennardjonescelllists.h"
#include "Potentials/lennardjonesneighbourlists.h"
#include "Potentials/gravitational.h"
#include "Potentials/nopotential.h"
#include "InitialConditions/initialcondition.h"
#include "InitialConditions/twobody.h"
#include "InitialConditions/randomspherical.h"
#include "InitialConditions/uniform.h"
#include "InitialConditions/fcc.h"
#include "InitialConditions/loadfromfile.h"
#include "Thermostats/thermostat.h"
#include "Thermostats/berendsenthermostat.h"
#include "Thermostats/andersenthermostat.h"

using std::cout;
using std::endl;

int Examples::coldCollapseCluster() {
    int   n   = 2000;                              // Number of particles.
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
    system->setIntegrator                (new EulerCromer(dt, system));
    system->setPotential                 (new Gravitational(G, eps, system));
    system->setInitialCondition          (new RandomSpherical(n, R0));
    system->setPeriodicBoundaryConditions(false);
    system->setSystemSize                (boxSize);
    system->enableSavingToFile           (true, 25);
    return system->integrate(5000);
}

int Examples::uniformBoxNoPotential() {
    int     n         = 10000;              // Number of particles.
    real  dt          = 0.001;            // Time step.
    real  sideLength  = 1;                // Size of box sides.
    std::vector<real> boxSize{sideLength, // Vector of box size.
                sideLength,
                sideLength};

    System* system = new System          ();
    system->setIntegrator                (new EulerCromer(dt, system));
    system->setPotential                 (new NoPotential(system));
    system->setInitialCondition          (new Uniform(n, boxSize, 5));
    system->setPeriodicBoundaryConditions(true);
    system->setSystemSize                (boxSize);
    system->enableSavingToFile           (false);
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
    system->enableSavingToFile           (false);
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
    system->enableSavingToFile           (false);
    return system->integrate(1000);
}

int Examples::lennardJonesFCCNeighbourLists() {
    int   nUnitCells          = 10;    // Number of unit cells in each dimension.
    real  T                   = 3.0;   // Temperature, in units of 119.8 K.
    real  targetTemperature   = 3.0;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    real  b                   = 5.26;  // Lattice constant, in units of 1.0 Å.
    real  dt                  = 0.01;  // Time step.
    real  tau                 = dt*100;    // Relaxation time used by the thermostat, in units of 119.8 K.
    real  sideLength          = nUnitCells*b; // Size of box sides.
    real  epsilon             = 1.0;
    real  sigma               = 1.0; // 3.405;
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
    system->setThermostat                (new AndersenThermostat(system, targetTemperature, tau, dt));
    system->setSystemSize                (boxSize);
    system->setThermostatActive          (true);
    system->enablePressureSampling       (true);
    system->enableSavingToFile           (true);

    system->integrate                    (1000);
    system->setThermostatActive(false);
    return system->integrate(1000);

}

int Examples::lennardJonesLiquid() {
    int   nUnitCells          = 10;    // Number of unit cells in each dimension.
    real  T                   = 0.851;   // Temperature, in units of 119.8 K.
    real  targetTemperature   = 0.851;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    real  b                   = 5.72;  // Lattice constant, in units of 1.0 Å.
    real  dt                  = 0.01;  // Time step.
    real  tau                 = dt*10;    // Relaxation time used by the thermostat, in units of 119.8 K.
    real  sideLength          = nUnitCells*b; // Size of box sides.
    real  epsilon             = 1.0;
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
    system->setThermostatActive          (true);
    system->enablePressureSampling       (true);
    system->enableSavingToFile           (false);

    system->integrate                    (1000);
    system->setThermostatActive          (false);
    system->integrate                    (1000);
    return system->saveSnapShot();
}

int Examples::loadFromFile() {
    real  targetTemperature   = 0.851;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    real  dt                  = 0.01;  // Time step.
    real  tau                 = dt*10;    // Relaxation time used by the thermostat, in units of 119.8 K.
    real  epsilon             = 1.0;
    real  sigma               = 3.405;
    real  rCut                = 2.5 * sigma;
    real  rNeighbourCut       = 3.0 * sigma;

    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setInitialCondition          (new LoadFromFile("snapShot.dat", system));
    system->setPotential                 (new LennardJonesNeighbourLists(epsilon, sigma, rCut, rNeighbourCut, system));
    system->setPeriodicBoundaryConditions(true);
    system->setThermostat                (new BerendsenThermostat(system, targetTemperature, tau, dt));
    system->setSystemSize                (system->getInitialCondition()->getSystemSize());
    system->setThermostatActive          (true);
    system->enablePressureSampling       (true);
    system->enableSavingToFile           (false);
    system->integrate                    (1000);
}

int Examples::lennardJonesFCCNanoPorousTest() {
    real  targetTemperature   = 0.851;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    real  dt                  = 0.01;  // Time step.
    real  tau                 = dt*10;    // Relaxation time used by the thermostat, in units of 119.8 K.
    real  epsilon             = 1.0;
    real  sigma               = 3.405;
    real  rCut                = 2.5 * sigma;
    real  rNeighbourCut       = 3.0 * sigma;

    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setInitialCondition          (new LoadFromFile("../MD/snapShot.dat", system));
    system->setPotential                 (new LennardJonesNeighbourLists(epsilon, sigma, rCut, rNeighbourCut, system));
    system->setPeriodicBoundaryConditions(true);
    system->setThermostat                (new BerendsenThermostat(system, targetTemperature, tau, dt));
    system->setSystemSize                (system->getInitialCondition()->getSystemSize());
    system->setThermostatActive          (true);
    system->enablePressureSampling       (true);
    system->enableSavingToFile           (true);
    system->integrate                    (0);
    system->generateTestMatrix           (20.0);
    system->integrate                    (1000);
}

int Examples::lennardJonesFCCNanoPorous() {
    real  targetTemperature   = 0.851;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    real  dt                  = 0.01;  // Time step.
    real  tau                 = dt*10;    // Relaxation time used by the thermostat, in units of 119.8 K.
    real  epsilon             = 1.0;
    real  sigma               = 3.405;
    real  rCut                = 2.5 * sigma;
    real  rNeighbourCut       = 3.0 * sigma;

    System* system = new System          ();
    system->setIntegrator                (new VelocityVerlet(dt, system));
    system->setInitialCondition          (new LoadFromFile("../MD/snapShot20x20x20.dat", system));
    system->setPotential                 (new LennardJonesNeighbourLists(epsilon, sigma, rCut, rNeighbourCut, system));
    system->setPeriodicBoundaryConditions(true);
    system->setThermostat                (new BerendsenThermostat(system, targetTemperature, tau, dt));
    system->setSystemSize                (system->getInitialCondition()->getSystemSize());
    system->setThermostatActive          (true);
    system->enablePressureSampling       (true);
    system->enableSavingToFile           (true);
    system->integrate                    (0);
    system->generateMatrix               (20.0, 30.0, 20);
    system->integrate                    (10000);
}

int Examples::computeTemperatureFluctuations() {
    //std::vector<real> temp = {0.3, 0.4, 0.5, 0.6, 0.7, 0.7, 0.8, 0.9, 1.0};
    //std::vector<int>  num  = {3,4,5,6,7,8,9,10};
    std::vector<real> temp = {0.3, 0.8};
    std::vector<int>  num  = {11,12,13,14,15};
    std::vector<std::vector<real>> stdd;
    stdd.resize(temp.size(), std::vector<real>());
    for (int i=0; i<temp.size(); i++) {
        stdd.at(i).resize(num.size());
    }

    int NN = 10;

    for (int itemp=0; itemp<temp.size(); itemp++) {
        for (int inum=0; inum<num.size(); inum++) {

            for (int kk=0; kk<NN; kk++) {
                int   nUnitCells          = num.at(inum);    // Number of unit cells in each dimension.
                real  T                   = temp.at(itemp);   // Temperature, in units of 119.8 K.
                real  targetTemperature   = T;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
                real  b                   = 5.26;  // Lattice constant, in units of 1.0 Å.
                real  dt                  = 0.01;  // Time step.
                real  tau                 = dt*10;    // Relaxation time used by the thermostat, in units of 119.8 K.
                real  sideLength          = nUnitCells*b; // Size of box sides.
                real  epsilon             = 1.0;
                real  sigma               = 3.405;
                real  rCut                = 2.5 * sigma;
                real  rNeighbourCut       = 3.0 * sigma;
                std::vector<real> boxSize{  sideLength,     // Vector of box size.
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
                system->setThermostatActive          (true);
                system->enablePressureSampling       (true);
                system->enableSavingToFile           (false);
                system->integrate                    (1000);
                system->setThermostatActive          (false);
                system->enableTemperatureFluctuationsMeasurement(true);
                system->integrate                    (1000);
                double stddev = std::sqrt(system->getTemperatureVariance());
                cout << "Temperature std. dev.: " << stddev << endl;
                (stdd.at(itemp)).at(inum) += stddev;

                cout << endl;
                for (int jtemp=0; jtemp<temp.size(); jtemp++) {
                    for (int jnum=0; jnum<num.size(); jnum++) {
                        printf("%15.10f  ", at(at(stdd, jtemp), jnum));
                    }
                    cout << endl;
                }
                cout << endl;
            }
            (stdd.at(itemp)).at(inum) /= NN;
        }
    }
}

int Examples::computeRadialDistributionFunction() {
    int   nUnitCells          = 6;    // Number of unit cells in each dimension.
    real  T                   = 0.3;   // Temperature, in units of 119.8 K.
    real  targetTemperature   = 0.3;   // Temperature of the heat bath used by the thermostat, in units of 119.8 K.
    real  b                   = 5.26;  // Lattice constant, in units of 1.0 Å.
    real  dt                  = 0.01;  // Time step.
    real  tau                 = dt*10;    // Relaxation time used by the thermostat, in units of 119.8 K.
    real  sideLength          = nUnitCells*b; // Size of box sides.
    real  epsilon             = 1.0;
    real  sigma               = 1.0; // 3.405;
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
    system->setThermostatActive          (true);
    system->enablePressureSampling       (true);
    system->enableSavingToFile           (false);
    system->integrate                    (1000);
    system->setThermostatActive(false);
    system->enablePairCorrelationMeasurement(true);
    return system->integrate(1000);
}

















