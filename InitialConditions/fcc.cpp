#include "fcc.h"
#include <cmath>
#include <vector>
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
                double bHalf = this->latticeConstant/2.0;
                std::vector<double> cellOrigin{i*b, j*b, k*b};
                std::vector<double> atom0{cellOrigin.at(0), cellOrigin.at(1), cellOrigin.at(2)};
                std::vector<double> atom1{cellOrigin.at(0), cellOrigin.at(1), cellOrigin.at(2)};
                std::vector<double> atom2{cellOrigin.at(0), cellOrigin.at(1), cellOrigin.at(2)};
                std::vector<double> atom3{cellOrigin.at(0), cellOrigin.at(1), cellOrigin.at(2)};

                atom1.at(0) += bHalf;
                atom1.at(1) += bHalf;
                atom2.at(1) += bHalf;
                atom2.at(2) += bHalf;
                atom3.at(0) += bHalf;
                atom3.at(2) += bHalf;

                this->atoms[counter+0].setPosition(atom0);
                this->atoms[counter+1].setPosition(atom1);
                this->atoms[counter+2].setPosition(atom2);
                this->atoms[counter+3].setPosition(atom3);
                counter += 4;
            }
        }
    }

    for (int i=0; i<this->n; i++) {
        double m = 39.948;          // Mass of Argon in atomic units.
        atoms[i].setMass(m);

        for (int k=0; k<3; k++) {
            atoms[i].setVelocity(Random::nextGaussian(0, std::sqrt(this->temperature / m)), k);
        }
    }
    InitialCondition::setupDone = true;
}
