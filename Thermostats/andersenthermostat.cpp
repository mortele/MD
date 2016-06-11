#include "andersenthermostat.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "../atom.h"
#include "../system.h"

AndersenThermostat::AndersenThermostat(System*      system,
                                       real         targetTemperature,
                                       real         tau,
                                       real         dt) :
        Thermostat(system, targetTemperature, dt) {
    m_tau = tau;
    m_dtOverTau = dt/tau;
}

void AndersenThermostat::adjustVelocities(real instantaneousTemperature) {
    for (int i=0; i < m_system->getN(); i++) {
        real randomCollisionProbability = Random::nextReal();
        if (randomCollisionProbability < m_dtOverTau) {
            Atom* atom = at(m_system->getAtoms(), i);
            double m = atom->getMass();
            for (int k=0; k<3; k++) {
                real newVelocity = Random::nextGaussian(0, std::sqrt(m_targetTemperature / m));
                atom->setVelocity(newVelocity, k);
            }
        }
    }
}

