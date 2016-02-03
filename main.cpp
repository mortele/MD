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
    B() { m_n = 4; }
    void setupB();
    vector<vector<vector<vector<A*>>>>& getA() { return m_a; }

private:
    int m_n = 0;
    vector<vector<vector<vector<A*>>>> m_a;// = vector<vector<A*>>();
};

void B::setupB() {
    // A[1:N][1:N][1:N][1:k]
    m_a.resize(m_n, vector<vector<vector<A*>>>(m_n, vector<vector<A*>>(m_n, vector<A*>())));
    for (int i=0; i<m_n; i++) {
        for (int j=0; j<m_n; j++) {
            for (int k=0; k<m_n; k++) {
                at(at(at(m_a,i),j),k).reserve(100);
                auto &vec = at(at(at(m_a,i),j),k);
                for (int l=0; l<100; l++) {
                    vec.push_back(new A(i*m_n*m_n+j*m_n+k+1000*l));
                }

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
                //cout << at(at(at(balle.getA(),i),j),k).getIndex() << endl;
                for (int l=0; l<100; l++) {
                    cout << balle.getA().at(i).at(j).at(k).at(l)->getIndex() << endl;
                }
            }
        }
    }

    cout << "DOne" << endl;
    return 0;
}















