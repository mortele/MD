#pragma once
#include "initialcondition.h"
#include <iostream>

class FCC : public InitialCondition {
public:
    FCC(int, real, real);
    void setupInitialCondition();

    std::string getName() { return "FCC (face-centered cubic)"; }

private:
    int     m_numberOfUnitCells;
    real  m_latticeConstant;
    real  m_temperature;
};

