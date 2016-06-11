#pragma once
#include "initialcondition.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>



class LoadFromFile : public InitialCondition {
public:
    LoadFromFile(char* file, class System* system);
    void setupInitialCondition();

    std::string getName();

private:
    char* m_fileName = nullptr;
    std::fstream m_inFile;
    class System* m_system = nullptr;
};
