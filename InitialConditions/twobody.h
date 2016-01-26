#pragma once
#include "initialcondition.h"
#include <string>
#include "../atom.h"

class TwoBody : public InitialCondition {
public:
    TwoBody();
    TwoBody(double);
    void  setupInitialCondition();
    std::string getName() { return "Two-body"; }

private:
    double m_e = 0.0;
};

