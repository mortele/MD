#include "loadfromfile.h"
#include "../system.h"
#include "../atom.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

using std::string;
using std::fstream;
using std::cout;
using std::endl;
using std::stringstream;

LoadFromFile::LoadFromFile(char* fileName, System* system) {
    m_fileName = fileName;
    m_inFile.open(fileName, std::ios::in);
    if (m_inFile.is_open() == false) {
        cout << endl << "### ERROR ###: Could not open file for snapshot. Exiting." << endl << endl;
    }
    string line;
    getline(m_inFile, line);
    stringstream stream(line);
    string tmpString;
    getline(stream, tmpString, ' ');
    m_n = atoi(tmpString.c_str());
    std::vector<real> systemSize{0,0,0};

    for (int k=0; k<3; k++) {
        getline(stream, tmpString, ' ');
        systemSize.at(k) = atof(tmpString.c_str());
    }
    m_system = system;
    m_systemSize = systemSize;
    m_system->setSystemSize(systemSize);
}

void LoadFromFile::setupInitialCondition() {
    string line;
    string tmpString;

    for (int i=0; i<m_n; i++) {
        getline(m_inFile, line);
        stringstream stream(line);
        getline(stream, tmpString, ' ');
        string name = tmpString;
        std::vector<real_posvel> position{0,0,0};
        std::vector<real_posvel> velocity{0,0,0};
        for (int k=0; k<3; k++) {
            getline(stream, tmpString, ' ');
            position.at(k) = atof(tmpString.c_str());
        }
        for (int k=0; k<3; k++) {
            getline(stream, tmpString, ' ');
            velocity.at(k) = atof(tmpString.c_str());
        }
        getline(stream, tmpString, ' ');
        real_posvel mass = atof(tmpString.c_str());

        m_atoms.push_back(new Atom(name, mass));
        m_atoms.at(i)->setPosition(position);
        m_atoms.at(i)->setVelocity(velocity);
    }
    removeLinearMomentum();
    m_setupDone = true;
}


std::string LoadFromFile::getName() {
    char str[100];
    string returnString;
    strcpy(str, "State loaded from: ");
    strcpy(str, m_fileName);
    std::stringstream stringStream;
    stringStream >> str;
    stringStream << returnString;
    return returnString;
}
