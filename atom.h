#pragma once
#include "vec.h"
#include <vector>

class Atom {
public:
    Atom(real mass);
    Atom(std::string name, real mass);

    void setPosition        (std::vector<real>  position);
    void setPosition        (real x, int index);
    void setVelocity        (std::vector<real>  velocity);
    void setVelocity        (real v, int index);
    void setForce           (std::vector<real>  force);
    void setForce           (real f, int index);
    void addForce           (std::vector<real>  dforce);
    void setMass            (real mass);
    void setName            (std::string name);
    void setCellListIndex   (int, int, int);
    void setIndex           (int index);

    inline void addPosition(real x, int index) {
        at(m_position,index) += x;
    }
    inline void addVelocity(real v, int index) {
        at(m_velocity,index) += v;
    }
    inline void addForce(real f, int index) {
        at(m_force,index) += f;
    }
    inline void multiplyVelocity(real factor, int index) {
        at(m_velocity,index) *= factor;
    }

    int                 getIndex()          { return m_index; }
    real              getMass()           { return m_mass; }
    std::vector<real>& getPosition()      { return m_position; }
    std::vector<real>& getVelocity()      { return m_velocity; }
    std::vector<real>& getForce()         { return m_force; }
    std::string         getName()           { return m_name; }
    std::vector<int>&   getCellListIndex()  { return m_cellListIndex; }

private:
    int                 m_index           = 0;
    real              m_mass            = 1.0;
    std::string         m_name            = "Ar";
    std::vector<int>    m_cellListIndex{0,0,0};
    std::vector<real> m_position        = std::vector<real>(3);
    std::vector<real> m_velocity        = std::vector<real>(3);
    std::vector<real> m_force           = std::vector<real>(3);

};
