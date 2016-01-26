#include "thermostat.h"

Thermostat::Thermostat(double targetTemperature, double dt) {
    m_targetTemperature = targetTemperature;
    m_dt = dt;
}

