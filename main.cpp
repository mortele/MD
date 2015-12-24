#include <iostream>
#include <cmath>

#include "atom.h"
#include "vec.h"

#include "Integrators/integrator.h"
#include "Integrators/eulercromer.h"

#include "Potentials/potential.h"
#include "Potentials/lennardjones.h"
#include "Potentials/gravitational.h"

using namespace std;

const double PI = 3.14159265358979323846;


int main() {

    int N  = 2;
    int Nt = 100;

    Atom* atoms = new Atom[N];

    for (int i = 0; i < N; i++) {
        atoms[i].setPosition(vec(i,0,0));
    }

    atoms[0].setMass(pow(10,6));
    atoms[1].setVelocity(vec(0,2*PI,0));

    Integrator* ec = new EulerCromer(0.05);
    //Potential*  lj = new LennardJones(1,1);
    Potential* grav = new Gravitational(4*PI*PI);

    for (int t=0; t < Nt; t++) {
        grav->computeForces(atoms, N);
        ec->advance(atoms, N);
        cout << atoms[1].getPosition() << endl;
    }



    return 0;
}


