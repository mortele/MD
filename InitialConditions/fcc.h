#pragma once
#include "initialcondition.h"

class FCC : public InitialCondition {
public:
    FCC(int, double, double);
    void setupInitialCondition();

    std::string getName() { return "FCC (face-centered cubic)"; }

private:
    int     n;
    int     numberOfUnitCells;
    double  latticeConstant;
    double  temperature;
};

