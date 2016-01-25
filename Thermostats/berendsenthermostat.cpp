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
                                         double dt) {
    this->targetTemperature = targetTemperature;
    this->tau = tau;
    this->dt = dt;
    this->dtOverTau = dt/tau;
}

void BerendsenThermostat::adjustVelocities(Atom* atoms,
                                           int n,
                                           double instantaneousTemperature) {
    std::vector<double> velocity;

    for (int i=0; i < n; i++) {

        double gamma = std::sqrt(1+this->dtOverTau*(this->targetTemperature/instantaneousTemperature-1));
        velocity = atoms[i].getVelocity();
        for (int k=0; k<3; k++) {
            velocity.at(k) *= gamma;
        }
        atoms[i].setVelocity(velocity);
    }
}
