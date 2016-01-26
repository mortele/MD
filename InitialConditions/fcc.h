#pragma once
#include "initialcondition.h"
#include <iostream>

class FCC : public InitialCondition {
public:
    FCC(int, double, double);
    void setupInitialCondition();

    std::string getName() { return "FCC (face-centered cubic)"; }

private:
    int     m_numberOfUnitCells;
    double  m_latticeConstant;
    double  m_temperature;
};

