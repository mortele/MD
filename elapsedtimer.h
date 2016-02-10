#ifndef CPELAPSEDTIMER_H
#define CPELAPSEDTIMER_H
#include <time.h>

class TimingObject {
private:
    double m_timeElapsed;
    clock_t m_startedAt;
public:
    TimingObject() : m_timeElapsed(0), m_startedAt(0) { }

    void start() {
         m_startedAt = clock();
    }

    double stop() {
        double t = double(clock() - m_startedAt)/CLOCKS_PER_SEC;
        m_timeElapsed += t;
        return t;
    }

    double elapsedTime() { return m_timeElapsed; }
};

class ElapsedTimer
{
public:
    ElapsedTimer();

    static ElapsedTimer& getInstance()
    {
        static ElapsedTimer instance; // Guaranteed to be destroyed.
                                 // Instantiated on first use.
        return instance;
    }

    clock_t        m_startedAt;
    TimingObject m_calculateForces;
    TimingObject m_updateCellList;
    TimingObject m_updateNeighborList;
    TimingObject m_move;
    TimingObject m_halfKick;
    TimingObject m_periodicBoundaryConditions;
    TimingObject m_sampling;
    TimingObject m_disk;
    TimingObject m_timeEvolution;
    TimingObject m_thermostat;

    static TimingObject &calculateForces() { return ElapsedTimer::getInstance().m_calculateForces; }
    static TimingObject &updateCellList() { return ElapsedTimer::getInstance().m_updateCellList; }
    static TimingObject &updateNeighborList() { return ElapsedTimer::getInstance().m_updateNeighborList; }
    static TimingObject &move() { return ElapsedTimer::getInstance().m_move; }
    static TimingObject &halfKick() { return ElapsedTimer::getInstance().m_halfKick; }
    static TimingObject &periodicBoundaryConditions() { return ElapsedTimer::getInstance().m_periodicBoundaryConditions; }
    static TimingObject &sampling() { return ElapsedTimer::getInstance().m_sampling; }
    static TimingObject &disk() { return ElapsedTimer::getInstance().m_disk; }
    static TimingObject &timeEvolution() { return ElapsedTimer::getInstance().m_timeEvolution; }
    static TimingObject &thermostat() { return ElapsedTimer::getInstance().m_thermostat; }

    static double totalTime() { return double(clock() - ElapsedTimer::getInstance().m_startedAt)/ CLOCKS_PER_SEC; }
};

#endif // CPELAPSEDTIMER_H
