#pragma once
#include "vec.h"
#include <vector>

class Atom {
public:
    Atom(double mass);
    Atom(std::string name, double mass);

    void setPosition        (std::vector<double>  position);
    void setPosition        (double x, int index);
    void setVelocity        (std::vector<double>  velocity);
    void setVelocity        (double v, int index);
    void setForce           (std::vector<double>  force);
    void setForce           (double f, int index);
    void addForce           (std::vector<double>  dforce);
    void setMass            (double mass);
    void setName            (std::string name);
    void setCellListIndex   (int, int, int);
    void setIndex           (int index);

    inline void addPosition(double x, int index) {
        at(m_position,index) += x;
    }
    inline void addVelocity(double v, int index) {
        at(m_velocity,index) += v;
    }
    inline void addForce(double f, int index) {
        at(m_force,index) += f;
    }
    inline void multiplyVelocity(double factor, int index) {
        at(m_velocity,index) *= factor;
    }

    int                 getIndex()          { return m_index; }
    double              getMass()           { return m_mass; }
    std::vector<double>& getPosition()      { return m_position; }
    std::vector<double>& getVelocity()      { return m_velocity; }
    std::vector<double>& getForce()         { return m_force; }
    std::string         getName()           { return m_name; }
    std::vector<int>&   getCellListIndex()  { return m_cellListIndex; }

private:
    int                 m_index           = 0;
    double              m_mass            = 1.0;
    std::string         m_name            = "Ar";
    std::vector<int>    m_cellListIndex{0,0,0};
    std::vector<double> m_position        = std::vector<double>(3);
    std::vector<double> m_velocity        = std::vector<double>(3);
    std::vector<double> m_force           = std::vector<double>(3);

};
