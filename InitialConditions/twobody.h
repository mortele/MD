#pragma once
#include "initialcondition.h"
#include <string>
#include "../atom.h"

class TwoBody : public InitialCondition {
public:
    TwoBody();
    TwoBody(real);
    void  setupInitialCondition();
    std::string getName() { return "Two-body"; }

private:
    real m_e = 0.0;
};

