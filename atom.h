#pragma once
#include "vec.h"
#include <vector>

class Atom {
public:
    Atom(real_posvel mass);
    Atom(std::string name, real_posvel mass);

    void setPosition        (std::vector<real_posvel>  position);
    void setPosition        (real_posvel x, int index);
    void setVelocity        (std::vector<real_posvel>  velocity);
    void setVelocity        (real_posvel v, int index);
    void setForce           (std::vector<real_posvel>  force);
    void setForce           (real_posvel f, int index);
    void addForce           (std::vector<real_posvel>  dforce);
    void setMass            (real_posvel mass);
    void setName            (std::string name);
    void setCellListIndex   (int, int, int);
    void setIndex           (int index);

    inline void addPosition(real_posvel x, int index) {
        at(m_position,index) += x;
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
    std::vector<real_posvel>& getPosition()         { return m_position; }
    std::vector<real_posvel>& getVelocity()         { return m_velocity; }
    std::vector<real_posvel>& getForce()            { return m_force; }
    std::string               getName()             { return m_name; }
    std::vector<int>&         getCellListIndex()    { return m_cellListIndex; }

private:
    int                 m_index           = 0;
    real                m_mass            = 1.0;
    std::string         m_name            = "Ar";
    std::vector<int>    m_cellListIndex{0,0,0};
    std::vector<real_posvel> m_position        = std::vector<real_posvel>(3);
    std::vector<real_posvel> m_velocity        = std::vector<real_posvel>(3);
    std::vector<real_posvel> m_force           = std::vector<real_posvel>(3);

};
