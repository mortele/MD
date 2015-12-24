#include <iostream>
#include "atom.h"
#include "vec.h"

#include "Integrators/integrator.h"
#include "Integrators/eulercromer.h"

#include "Potentials/potential.h"
#include "Potentials/lennardjones.h"

using namespace std;


int main() {

    int N  = 10;
    int Nt = 100;

    Atom* atoms = new Atom[N];

    for (int i = 0; i < N; i++) {
        atoms[i].setPosition(vec(1.0,i+10,i+20));
    }

    atoms[0].setVelocity(vec(0.1,0,0));

    Integrator* ec = new EulerCromer(0.05);
    Potential*  lj = new LennardJones(1,1);

    for (int t=0; t < Nt; t++) {
        lj->computeForces(atoms, N);
        ec->advance(atoms, N);
        cout << atoms[0].getPosition() << endl;
    }



    return 0;
}


