#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
//#include <omp.h>
//#include <mpi.h>
#include "examples.h"
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
#include "Potentials/lennardjonescelllists.h"
#include "Potentials/lennardjonesneighbourlists.h"
#include "Potentials/gravitational.h"
#include "Potentials/nopotential.h"
#include "InitialConditions/initialcondition.h"
#include "InitialConditions/twobody.h"
#include "InitialConditions/randomspherical.h"
#include "InitialConditions/fcc.h"
#include "Thermostats/thermostat.h"
#include "Thermostats/berendsenthermostat.h"

using std::vector;
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    //return Examples::coldCollapseCluster();
    //return Examples::uniformBoxNoPotential();
    //return Examples::lennardJonesFCC();
    //return Examples::lennardJonesFCCCellLists();
    return Examples::lennardJonesFCCNeighbourLists();
}















