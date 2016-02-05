#include "berendsenthermostat.h"
#include <tgmath.h>
#include <vector>
#include <iostream>
#include "../atom.h"

using std::cout;
using std::endl;

BerendsenThermostat::BerendsenThermostat(real targetTemperature,
                                         real tau,
                                         real dt) :
        Thermostat(targetTemperature, dt) {
    m_tau = tau;
    m_dtOverTau = dt/tau;
}

void BerendsenThermostat::adjustVelocities(const std::vector<Atom*> & atoms,
                                           int n,
                                           real instantaneousTemperature) {
    for (int i=0; i < n; i++) {
        real gamma = std::sqrt(1+m_dtOverTau*(m_targetTemperature/instantaneousTemperature-1));
        for (int k=0; k<3; k++) {
            atoms.at(i)->multiplyVelocity(gamma, k);
        }
    }
}
