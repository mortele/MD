#pragma once
#include "vec.h"
#include <vector>

class Atom {
public:
    Atom();
    Atom(double mass);
    Atom(std::string name, double mass);

    void setPosition(std::vector<double>  position);
    void setPosition(double x, int index);
    void addPosition(double x, int index);
    void setVelocity(std::vector<double>  velocity);
    void setVelocity(double v, int index);
    void addVelocity(double v, int index);
    void setForce           (std::vector<double>  force);
    void setForce           (double f, int index);
    void addForce           (std::vector<double>  dforce);
    void addForce           (double f, int index);
    void setMass            (double mass);
    void setName            (std::string name);
    void setCellListIndex   (int cellListIndex, int index);

    double              getMass()           { return this->mass; }
    std::vector<double> getPosition()       { return this->position; }
    std::vector<double> getVelocity()       { return this->velocity; }
    std::vector<double> getForce()          { return this->force; }
    std::string         getName()           { return this->name; }
    std::vector<int>    getCellListIndex()  { return this->cellListIndex; }
    int getCellListIndex(int index)         { return this->cellListIndex.at(index); }

private:
    double  mass = 1.0;
    std::vector<int>    cellListIndex{-1,-1,-1};
    std::vector<double> position        = std::vector<double>(3);
    std::vector<double> velocity        = std::vector<double>(3);
    std::vector<double> force           = std::vector<double>(3);
    std::string name = "Ar";
};
