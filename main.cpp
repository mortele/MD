//#include <omp.h>
#include "examples.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "system.h"
#include "atom.h"
#include "vec.h"
#include "random.h"
#include "sampler.h"
#include "celllist.h"
#include "Integrators/integrator.h"
#include "Integrators/eulercromer.h"
#include "Potentials/potential.h"
#include "Potentials/lennardjones.h"
#include "Potentials/gravitational.h"
#include "Potentials/nopotential.h"
#include "InitialConditions/initialcondition.h"
#include "InitialConditions/twobody.h"
#include "InitialConditions/randomspherical.h"
#include "InitialConditions/fcc.h"
#include "Thermostats/thermostat.h"
#include "Thermostats/berendsenthermostat.h"

using std::cout;
using std::endl;

template <typename T>
T &at(std::vector<T> &vec, int index) {
    #ifdef VECTOR_LOOKUP_DEBUG
        return vec.at(index);
    #else
        return vec[index];
    #endif
}

int main() {

    System* system;
    //system = Examples::coldCollapseCluster();
    //system = Examples::uniformBoxNoPotential();
    system = Examples::lennardJonesFFC();

    return 0;
}



