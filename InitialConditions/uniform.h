#pragma once
#include <cmath>
#include <vector>
#include "initialcondition.h"
#include "../atom.h"
#include "../vec.h"
#include "../random.h"

class Uniform : public InitialCondition {
public:
    Uniform(int n, std::vector<double> boxSize, double temperature);
    void setupInitialCondition();
    std::string getName() { return "Uniform random"; }

private:
    int n;
    std::vector<double> boxSize;
    double temperature;
};

