#include "sampler.h"
#include "Potentials/lennardjones.h"

using std::cout;
using std::endl;

Sampler::Sampler(System* system) {
    m_system = system;
}

void Sampler::setupSampler(std::vector<Atom*> atoms, int n) {
    m_atoms = atoms;
    m_n     = n;
    m_volume = m_system->getSystemSize().at(0) *
               m_system->getSystemSize().at(1) *
               m_system->getSystemSize().at(2);
    m_density = m_system->getN() * m_system->getAtoms().at(0)->getMass() / m_volume;
}

void Sampler::sample(int t) {
    m_time[t]              = t*m_dt;
    m_kineticEnergies[t]   = sampleKineticEnergy();
    m_potentialEnergies[t] = samplePotentialEnergy();
    m_energies[t] = m_kineticEnergies[t] + m_potentialEnergies[t];
    m_instantanousTemperature[t] = (2.0/3.0)*m_kineticEnergies[t] / m_n;
    m_meanSquareDisplacement[t] = sampleMeanSquareDisplacement();

    if (m_pressureSamplingEnabled) {
        m_pressures[t] = samplePressure(m_instantanousTemperature[t]);
    }
}

void Sampler::setPotential(Potential* potential) {
    m_potential = potential;
}

void Sampler::setNtDt(int Nt, real dt) {
    m_Nt = Nt;
    m_dt = dt;

    // Ready the storage arrays for later use.
    m_time                      = new real[Nt+1];
    m_energies                  = new real[Nt+1];
    m_potentialEnergies         = new real[Nt+1];
    m_kineticEnergies           = new real[Nt+1];
    m_instantanousTemperature   = new real[Nt+1];
    m_pressures                 = new real[Nt+1];
    m_meanSquareDisplacement    = new real[Nt+1];
}

real Sampler::sampleKineticEnergy() {
    real kineticEnergy = 0;
    for (int i=0; i < m_n; i++) {
        real v2 = m_atoms.at(i)->getVelocity().at(0)*m_atoms.at(i)->getVelocity().at(0) +
                  m_atoms.at(i)->getVelocity().at(1)*m_atoms.at(i)->getVelocity().at(1) +
                  m_atoms.at(i)->getVelocity().at(2)*m_atoms.at(i)->getVelocity().at(2);
        kineticEnergy += 0.5 * m_atoms.at(i)->getMass() * v2;
    }
    return kineticEnergy;
}

real Sampler::samplePotentialEnergy() {
    return m_potential->computePotential();
}

real Sampler::samplePressure(real instantaneousTemperature) {
    real pressureFromLennardJones = m_potential->getPressure();
    return instantaneousTemperature * m_density +
            pressureFromLennardJones / (3 * m_volume);
}

real Sampler::sampleMeanSquareDisplacement() {
    real meanSquareDisplacement = 0;
    std::vector<real> dr{0,0,0};
    std::vector<real> systemSize = m_system->getSystemSize();
    for (int i=0; i<m_n; i++) {
        Atom* atom = at(m_atoms, i);
        for (int k=0; k<3; k++) {
            at(dr,k) = at(atom->getPosition(),k) - at(atom->getInitialPosition(),k);
            if (at(dr,k) > at(systemSize,k)*0.5) {
                at(dr,k) = at(dr,k) - at(systemSize,k);
            } else if (at(dr,k) < -at(systemSize,k)*0.5) {
                at(dr,k) = at(dr,k) + at(systemSize,k);
            }
            meanSquareDisplacement += at(dr,k)*at(dr,k);
        }
    }
    return meanSquareDisplacement / m_n;
}

void Sampler::setPressureSamplingEnabled(bool enabled) {
    m_pressureSamplingEnabled = enabled;
}

