#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
//#include <omp.h>
#include "examples.h"
#include "system.h"
#include "atom.h"
#include "vec.h"
#include "random.h"
#include "sampler.h"
#include "celllist.h"
#include "Integrators/integrator.h"
#include "Integrators/eulercromer.h"
#include "Potentials/potential.h"
#include "Potentials/lennardjones.h"
#include "Potentials/gravitational.h"
#include "Potentials/nopotential.h"
#include "InitialConditions/initialcondition.h"
#include "InitialConditions/twobody.h"
#include "InitialConditions/randomspherical.h"
#include "InitialConditions/fcc.h"
#include "Thermostats/thermostat.h"
#include "Thermostats/berendsenthermostat.h"


using std::vector;
using std::cout;
using std::endl;


class A {
public:
    A(int index)                { m_index = index; }
    void    setIndex(int index) { m_index = index; }
    int     getIndex()          { return m_index; }

private:
    int m_index = 0;
};

class B {
public:
    B() { m_n = 4; m_a = vector<vector<vector<A*>>>(m_n); }
    void setupB();
    vector<vector<vector<A*>>> getA() { return m_a; }

private:
    int m_n = 0;
    vector<vector<vector<A*>>> m_a;// = vector<vector<A*>>();
};

void B::setupB() {
    m_a.reserve(m_n);
    for (int i=0; i<m_n; i++) {
        at(m_a,i) = vector<vector<A*>>(m_n);
        at(m_a,i).reserve(m_n);
        for (int j=0; j<m_n; j++) {
            at(at(m_a,i),j) = vector<A*>(m_n);
            at(at(m_a,i),j).clear();
            for (int k=0; k<m_n; k++) {
                at(at(m_a,i),j).push_back(new A(i*m_n*m_n+j*m_n+k));
            }
        }
    }
}

int main() {
    System* system;
    //system = Examples::coldCollapseCluster();
    //system = Examples::uniformBoxNoPotential();
    //system = Examples::lennardJonesFFC();

    B balle = B();
    balle.setupB();
    cout << "size=" << balle.getA().at(1).at(2).size() << endl;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            for (int k=0; k<4; k++) {
                cout << at(at(at(balle.getA(),i),j),k)->getIndex() << endl;
            }
        }
    }
    cout << "DOne" << endl;
    return 0;
}















