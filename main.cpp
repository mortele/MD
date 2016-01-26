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
#include "celllist.h"
#include "GUI/mainwindow.h"
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

/* FIXME: Make real time plotting work--need to be able to compute stuff in
 *        System, but update the plot in MainWindow in real time.
 * FIXME: Clean up MainWindow class and the integrate method in System.
 *
 * TODO: Velocity Verlet integrator.
 * TODO: Make the plots close when the run terminal closes.
 */

int main(int argc, char* argv[]) {

    System* system;
    //system = Examples::coldCollapseCluster(argc, argv);
    //system = Examples::uniformBoxNoPotential(argc, argv);
    //system = Examples::staticFCCLattice(argc, argv);
    //system = Examples::lennardJonesFCC(argc, argv);
    //system = Examples::lennardJonesBerendsen(argc, argv);
    system = Examples::lennardJonesCellLists(argc, argv);

    // If the plot is active, return the application handle.
    if (system->getPlotting()) {
        return system->m_app.exec();
    } else {
        return 0;
    }
}






