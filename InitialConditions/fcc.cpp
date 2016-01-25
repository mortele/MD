#include "fcc.h"
#include <cmath>
#include "../atom.h"
#include "../random.h"

using std::cout;
using std::endl;

FCC::FCC(int    numberOfUnitCells,
         double latticeConstant,
         double temperature         ) {

    this->numberOfUnitCells = numberOfUnitCells;
    this->latticeConstant   = latticeConstant;
    this->n                 = 4 * std::pow(numberOfUnitCells,3);
    this->temperature       = temperature;

    InitialCondition::n = this->n;
    InitialCondition::setupDone = false;
}

void FCC::setupInitialCondition() {
    this->atoms = new Atom[this->n];
    int counter = 0;

    for (int i=0; i<this->numberOfUnitCells; i++) {
        for (int j=0; j<this->numberOfUnitCells; j++) {
            for (int k=0; k<this->numberOfUnitCells; k++) {

                double b = this->latticeConstant;
                vec cellOrigin = vec(i*b, j*b, k*b);

                vec atom0 = vec(0,      0,      0       );
                vec atom1 = vec(b/2.0,  b/2.0,  0       );
                vec atom2 = vec(0,      b/2.0,  b/2.0   );
                vec atom3 = vec(b/2.0,  0,      b/2.0   );

                this->atoms[counter+0].setPosition(cellOrigin + atom0);
                this->atoms[counter+1].setPosition(cellOrigin + atom1);
                this->atoms[counter+2].setPosition(cellOrigin + atom2);
                this->atoms[counter+3].setPosition(cellOrigin + atom3);
                counter += 4;
            }
        }
    }

    for (int i=0; i<this->n; i++) {
        double m = 39.948;          // Mass of Argon in atomic units.
        atoms[i].setMass(m);
        atoms[i].setVelocity(vec(Random::nextGaussian(0, std::sqrt(this->temperature / m)),
                                 Random::nextGaussian(0, std::sqrt(this->temperature / m)),
                                 Random::nextGaussian(0, std::sqrt(this->temperature / m))));
    }
    InitialCondition::setupDone = true;
}
