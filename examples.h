#pragma once

class vec;
class Atom;
class System;

class Examples {
public:
    Examples() {}

    static System* coldCollapseCluster(int, char**);
    static System* uniformBoxNoPotential(int, char**);
    static System* staticFCCLattice(int, char**);
    static System* lennardJonesFCC(int, char**);
    static System* lennardJonesBerendsen(int, char**);
    static System* lennardJonesCellLists(int, char**);
};

