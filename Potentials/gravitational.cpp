#include "gravitational.h"
#include <vector>
#include "../system.h"

using std::endl;
using std::cout;

Gravitational::Gravitational(double G, System* system) :
        Gravitational(G, 0, system) {
}

Gravitational::Gravitational(double G, double eps, System* system) :
        Potential(system) {
    m_G     = G;
    m_eps   = eps;
}


void Gravitational::computeForces(const std::vector<Atom*> & atoms, int n) {

    setForcesToZero(atoms, n);

    std::vector<double> dr{0,0,0};
    double r  = 0;
    double r2 = 0;
    double f  = 0;
    m_potentialEnergy = 0;

    for (int i=0; i < n; i++) {
        for (int j=0; j < n; j++) {
            if (i!=j) {
                r2 = 0;
                for (int k=0; k < 3; k++) {
                    dr.at(k) = atoms.at(i)->getPosition().at(k) -
                               atoms.at(j)->getPosition().at(k);
                    r2      += dr.at(k)*dr.at(k);
                }
                r = std::sqrt(r2);

                f = -m_G * atoms.at(i)->getMass() * atoms.at(j)->getMass() /
                    (r2 + m_eps);

                for (int k=0; k<3; k++) {

                    atoms.at(i)->addForce(f * dr.at(k) / r, k);
                    //atoms[j].setForce(atoms[j].getForce().at(k) - atoms[i].getForce().at(k), k);
                }

                m_potentialEnergy += r * f;
            }
        }
    }
}

double Gravitational::computePotential(const std::vector<Atom*> & atoms, int n) {
    return m_potentialEnergy / 2.0;
}







