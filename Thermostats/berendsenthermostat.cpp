#include "berendsenthermostat.h"
#include <cmath>
#include <iostream>
#include "../atom.h"
#include "../vec.h"

using std::cout;
using std::endl;

BerendsenThermostat::BerendsenThermostat(double targetTemperature,
                                         double tau,
                                         double dt) {
    this->targetTemperature = targetTemperature;
    this->tau = tau;
    this->dt = dt;
    this->dtOverTau = dt/tau;
}

void BerendsenThermostat::adjustVelocities(Atom* atoms,
                                           int n,
                                           double instantaneousTemperature) {
    for (int i=0; i < n; i++) {

        double gamma = std::sqrt(1+this->dtOverTau*(this->targetTemperature/instantaneousTemperature-1));
        atoms[i].setVelocity(gamma*atoms[i].getVelocity());
    }
}
