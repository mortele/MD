#pragma once

class vec;
class Atom;
class System;

class Examples {
public:
    static System* coldCollapseCluster();
    static System* uniformBoxNoPotential();
    static System* staticFCCLattice();
    static System* lennardJonesFCC();
    static System* lennardJonesBerendsen();
    static System* lennardJonesCellLists();
    static System* lennardJonesBerendsenCellLists();
};

