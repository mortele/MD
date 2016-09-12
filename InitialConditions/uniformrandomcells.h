#pragma once
#include "initialcondition.h"
#include <iostream>


class UniformRandomCells : public InitialCondition {
public:
    UniformRandomCells(int numberOfUnitCells, int particlesPerCell, real latticeConstant);
    void setupInitialCondition();

    std::string getName() { return "Random cells"; }

private:
    int   m_numberOfUnitCells;
    int   m_particlesPerCell;
    real  m_latticeConstant;
    real  m_temperature;

};

