#include "randomspherical.h"


RandomSpherical::RandomSpherical(int n, real R0) {
    m_setupDone = false;
    m_n  = n;
    m_R0 = R0;
}


void RandomSpherical::setupInitialCondition() {
    using std::cos;
    using std::sin;
    using std::pow;
    using std::acos;
    using std::cout;
    using std::endl;

    for (int i=0; i<m_n; i++) {
        real mass = Random::nextGaussian(10.0, 1.0);

        real u,v,w,x,y,z,r,theta,phi;
        u = (Random::nextreal());
        v = (Random::nextreal());
        w = (Random::nextreal());

        r     = m_R0*pow(u, 1.0/3.0);
        theta = acos(1-2*v);
        phi   = 2*acos(-1.0)*w;

        x = r*sin(theta)*cos(phi)+m_R0;
        y = r*sin(theta)*sin(phi)+m_R0;
        z = r*cos(theta)         +m_R0;

        m_atoms.push_back(new Atom(1));
        m_atoms.at(i)->setMass(mass);
        m_atoms.at(i)->setPosition(std::vector<real_posvel>{x,y,z});
        m_atoms.at(i)->setVelocity(std::vector<real_posvel>{0,0,0});
    }

    m_setupDone = true;
}



