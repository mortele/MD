#include "uniformrandomcells.h"
#include <cmath>
#include <vector>
#include "../atom.h"
#include "../random.h"

UniformRandomCells::UniformRandomCells(int numberOfUnitCells,
                                       int particlesPerCell,
                                       real latticeConstant) {

    m_particlesPerCell  = particlesPerCell;
    m_numberOfUnitCells = numberOfUnitCells;
    m_latticeConstant   = latticeConstant;
    m_n                 = particlesPerCell * std::pow(numberOfUnitCells,3);
    m_temperature       = 1.0;
    m_setupDone         = false;
}

void UniformRandomCells::setupInitialCondition() {
    int counter = 0;

    for (int i=0; i<m_numberOfUnitCells; i++) {
        for (int j=0; j<m_numberOfUnitCells; j++) {
            for (int k=0; k<m_numberOfUnitCells; k++) {
                for (int l=0; l<m_particlesPerCell; l++) {
                    real x = (Random::nextReal());
                    real y = (Random::nextReal());
                    real z = (Random::nextReal());

                    m_atoms.push_back(new Atom(1.0));
                    m_atoms.at(counter)->setPosition(std::vector<real_posvel>{x,y,z});
                    m_atoms.at(counter)->setVelocity(std::vector<real_posvel>{0,0,0});
                    counter++;
                }
            }
        }
    }
    m_setupDone = true;
}
