#include "thermostat.h"

Thermostat::Thermostat(real targetTemperature, real dt) {
    m_targetTemperature = targetTemperature;
    m_dt = dt;
}

