#include "randomspherical.h"


RandomSpherical::RandomSpherical(int n, double R0) {
    this->n  = n;
    this->R0 = R0;
}


void RandomSpherical::setupInitialCondition() {
    InitialCondition::n = this->n;
    this->atoms = new Atom[this->n];

    using std::cos;
    using std::sin;
    using std::pow;
    using std::acos;
    using std::cout;
    using std::endl;

    for (int i=0; i<this->n; i++) {
        double mass = Random::nextGaussian(10.0, 1.0);

        double u,v,w,x,y,z,r,theta,phi;
        u = (Random::nextDouble());
        v = (Random::nextDouble());
        w = (Random::nextDouble());

        r     = R0*pow(u, 1.0/3.0);
        theta = acos(1-2*v);
        phi   = 2*acos(-1.0)*w;

        x = r*sin(theta)*cos(phi);
        y = r*sin(theta)*sin(phi);
        z = r*cos(theta);

        this->atoms[i].setMass(mass);
        this->atoms[i].setPosition(vec(x,y,z));
        this->atoms[i].setVelocity(vec());
    }

    InitialCondition::setupDone = true;
}


