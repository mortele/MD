#include <iostream>
#include <fstream>
//#include <tgmath.h>
#include <cmath>
#include <vector>
//#include <omp.h>
#include <mpi.h>
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
#include "elapsedtimer.h"
using std::vector;
using std::cout;
using std::endl;

int main(int argc, char** argv) {


    //return Examples::coldCollapseCluster();
    //return Examples::uniformBoxNoPotential();
    //return Examples::lennardJonesFCC();
    //return Examples::lennardJonesFCCCellLists();
    Examples::lennardJonesFCCNeighbourLists();
    cout << "Cell list time: " << ElapsedTimer::getInstance().m_updateCellList.elapsedTime() << endl;
    cout << "Neighbor list time: " << ElapsedTimer::getInstance().m_updateNeighborList.elapsedTime() << endl;
    cout << "Forces time: " << ElapsedTimer::getInstance().m_calculateForces.elapsedTime() << endl;
    return 0;
}















