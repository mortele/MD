#include "thermostat.h"
#include "../system.h"

Thermostat::Thermostat(System* system, real targetTemperature, real dt) {
    m_system = system;
    m_targetTemperature = targetTemperature;
    m_dt = dt;
}

