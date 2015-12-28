#include "sampler.h"

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
    this->energies[t] = this->kineticEnergies[t] +
                        this->potentialEnergies[t];
    for (int i=0; i < this->n; i++) {
        for (int j=0; j < 3; j++) {
            this->positions[t][i][j] = this->atoms[i].getPosition()[j];
        }
    }
}

void Sampler::setPotential(Potential* potential) {
    this->potential = potential;
}

void Sampler::setNtDt(int Nt, double dt) {
    this->Nt = Nt;
    this->dt = dt;

    // Ready the storage arrays for later use.
    this->time              = new double[Nt];
    this->energies          = new double[Nt];
    this->potentialEnergies = new double[Nt];
    this->kineticEnergies   = new double[Nt];
    this->positions         = new double**[Nt];
    for (int i=0; i < this->Nt; i++) {
        this->positions[i] = new double*[this->n];
        for (int j=0; j < this->n; j++) {
            this->positions[i][j] = new double[3];
        }
    }
}

double Sampler::sampleKineticEnergy() {
    double kineticEnergy = 0;
    for (int i=0; i < this->n; i++) {
        kineticEnergy += 0.5 * atoms[i].getMass() *
                         atoms[i].getVelocity().computeLengthSquared();
    }
    return kineticEnergy;
}

double Sampler::samplePotentialEnergy() {
    return this->potential->computePotential(this->atoms, this->n);
}

