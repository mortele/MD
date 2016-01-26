#include "berendsenthermostat.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "../atom.h"
#include "../vec.h"

using std::cout;
using std::endl;

BerendsenThermostat::BerendsenThermostat(double targetTemperature,
                                         double tau,
                                         double dt) :
        Thermostat(targetTemperature, dt) {
    m_tau = tau;
    m_dtOverTau = dt/tau;
}

void BerendsenThermostat::adjustVelocities(const std::vector<Atom*> & atoms,
                                           int n,
                                           double instantaneousTemperature) {
    for (int i=0; i < n; i++) {
        double gamma = std::sqrt(1+m_dtOverTau*(m_targetTemperature/instantaneousTemperature-1));
        for (int k=0; k<3; k++) {
            atoms.at(i)->multiplyVelocity(gamma, k);
        }
    }
}
