#include "sampler.h"

using std::cout;
using std::endl;

Sampler::Sampler() {

}

void Sampler::setupSampler(Atom* atoms, int n) {
    this->atoms = atoms;
    this->n     = n;
}

void Sampler::sample(int t) {
    this->time[t]              = t*this->dt;
    this->kineticEnergies[t]   = this->sampleKineticEnergy();
    this->potentialEnergies[t] = this->samplePotentialEnergy();
    this->energies[t] = this->kineticEnergies[t] + this->potentialEnergies[t];
    this->instantanousTemperature[t] = (2.0/3.0)*this->kineticEnergies[t] / this->n;
}

void Sampler::setPotential(Potential* potential) {
    this->potential = potential;
}

void Sampler::setNtDt(int Nt, double dt) {
    this->Nt = Nt;
    this->dt = dt;

    // Ready the storage arrays for later use.
    this->time                      = new double[Nt];
    this->energies                  = new double[Nt];
    this->potentialEnergies         = new double[Nt];
    this->kineticEnergies           = new double[Nt];
    this->instantanousTemperature   = new double[Nt];
}

double Sampler::sampleKineticEnergy() {
    double kineticEnergy = 0;
    for (int i=0; i < this->n; i++) {
        std::vector<double> v = atoms[i].getVelocity();
        double v2 = v.at(0)*v.at(0) + v.at(1)*v.at(1) + v.at(2)*v.at(2);
        kineticEnergy += 0.5 * atoms[i].getMass() * v2;
    }
    return kineticEnergy;
}

double Sampler::samplePotentialEnergy() {
    return this->potential->computePotential(this->atoms, this->n);
}

