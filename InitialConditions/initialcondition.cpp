#include "initialcondition.h"

InitialCondition::InitialCondition() {
    this->setupDone = false;
}

void InitialCondition::removeLinearMomentum() {
    for (int k=0; k<3; k++) {
        this->totalMomentum.at(k) = 0;
    }
    for (int i=0; i<this->n; i++) {
        for (int k=0; k<3; k++) {
            totalMomentum.at(k) += this->atoms.at(i)->getVelocity().at(k) *
                                   this->atoms.at(i)->getMass();
        }
    }
    for (int k=0; k<3; k++) {
        totalMomentum.at(k) /= (double) this->n;
    }
    for (int i=0; i<this->n; i++) {
        for (int k=0; k<3; k++) {
            this->atoms.at(i)->addVelocity(-totalMomentum.at(k) /
                                       this->atoms.at(i)->getMass(), k);
        }
    }
}



