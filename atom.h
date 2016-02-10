#pragma once
#include "vec.h"
#include <vector>

class Atom {
public:
    static int nextIndex;
    static real_posvel *positions;
    static real_posvel *velocities;
    static real_posvel *forces;
    template <int type>
    static real_posvel *getNext();
    Atom(real_posvel mass);
    Atom(std::string name, real_posvel mass);

    void setPosition        (real_posvel x, int index);
    void setPosition        (std::vector<real_posvel> x);
    void setVelocity        (real_posvel v, int index);
    void setVelocity(std::vector<real_posvel> v);
    void setForce           (real_posvel f, int index);
    void setMass            (real_posvel mass);
    void setName            (std::string name);
    void setCellListIndex   (int, int, int);
    void setIndex           (int index);

    inline void addPosition(real_posvel x, int index) {
        at(m_position,index) += x;
        at(m_positionUnwrapped,index) += x;
    }
    inline void addVelocity(real_posvel v, int index) {
        at(m_velocity,index) += v;
    }
    inline void addForce(real_posvel f, int index) {
        at(m_force,index) += f;
    }
    inline void multiplyVelocity(real_posvel factor, int index) {
        at(m_velocity,index) *= factor;
    }

    int                       getIndex()            { return m_index; }
    real                      getMass()             { return m_mass; }
    real_posvel* getPosition()         { return m_position; }
    real_posvel* getVelocity()         { return m_velocity; }
    real_posvel* getForce()            { return m_force; }
//    std::vector<real_posvel>& getPosition()         { return m_position; }
//    std::vector<real_posvel>& getVelocity()         { return m_velocity; }
//    std::vector<real_posvel>& getForce()            { return m_force; }
    std::string               getName()             { return m_name; }
    std::vector<int>&         getCellListIndex()    { return m_cellListIndex; }
    bool needToUpdateNeighborList(real neighborListShellThickness);
    void didUpdateNeighborlist();

private:
    int                 m_index           = 0;
    real                m_mass            = 1.0;
    std::string         m_name            = "Ar";
    std::vector<int>    m_cellListIndex{0,0,0};
    // real_posvel m_position[3];
//    real_posvel m_velocity[3];
//    real_posvel m_force[3];
    real_posvel m_positionLastNeighborListUpdate[3];
    real_posvel m_positionUnwrapped[3];
    real_posvel *m_position = nullptr;
    real_posvel *m_velocity = nullptr;
    real_posvel *m_force = nullptr;

//    real_posvel *m_position;
//    real_posvel *m_velocity;
//    real_posvel *m_force;

//    std::vector<real_posvel> m_position        = std::vector<real_posvel>(3);
//    std::vector<real_posvel> m_velocity        = std::vector<real_posvel>(3);
//    std::vector<real_posvel> m_force           = std::vector<real_posvel>(3);

};
