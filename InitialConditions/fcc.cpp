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

    m_numberOfUnitCells = numberOfUnitCells;
    m_latticeConstant   = latticeConstant;
    m_n                 = 4 * std::pow(numberOfUnitCells,3);
    m_temperature       = temperature;
    m_setupDone = false;
}

void FCC::setupInitialCondition() {
    int counter = 0;

    for (int i=0; i<m_numberOfUnitCells; i++) {
        for (int j=0; j<m_numberOfUnitCells; j++) {
            for (int k=0; k<m_numberOfUnitCells; k++) {

                double b = m_latticeConstant;
                double bHalf = m_latticeConstant/2.0;
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

                m_atoms.push_back(new Atom(1));
                m_atoms.push_back(new Atom(1));
                m_atoms.push_back(new Atom(1));
                m_atoms.push_back(new Atom(1));

                m_atoms.at(counter+0)->setPosition(atom0);
                m_atoms.at(counter+1)->setPosition(atom1);
                m_atoms.at(counter+2)->setPosition(atom2);
                m_atoms.at(counter+3)->setPosition(atom3);

                counter += 4;
            }
        }
    }

    for (int i=0; i<m_n; i++) {
        double m = 39.948;          // Mass of Argon in atomic units.
        m_atoms.at(i)->setMass(m);

        for (int k=0; k<3; k++) {
            m_atoms.at(i)->setVelocity(Random::nextGaussian(0, std::sqrt(m_temperature / m)), k);
        }
    }
    removeLinearMomentum();
    m_setupDone = true;
}


