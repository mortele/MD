#pragma once
#include "initialcondition.h"
#include "../atom.h"

class StaticFCC : public InitialCondition {
public:
    StaticFCC(int, double);
    void setupInitialCondition();
    std::string getName() { return "Static FCC (Face-centered-cubic)"; }

private:
    int     n;
    int     numberOfUnitCells;
    double  latticeConstant;
};

