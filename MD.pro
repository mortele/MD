TEMPLATE                 = app
CONFIG                  += console c++11
CONFIG                  += c++11
QMAKE_CXXFLAGS_RELEASE  -= -O2
QMAKE_CXXFLAGS_RELEASE  += -O3
#QMAKE_CXXFLAGS_RELEASE  += -fopenmp
#LIBS                    += -fopenmp


debug {
    DEFINES += VECTOR_LOOKUP_DEBUG
}
release {
    DEFINES -= VECTOR_LOOKUP_DEBUG
}

SOURCES += main.cpp \
    atom.cpp \
    Integrators/integrator.cpp \
    Integrators/eulercromer.cpp \
    vec.cpp \
    Potentials/potential.cpp \
    Potentials/lennardjones.cpp \
    Potentials/gravitational.cpp \
    system.cpp \
    InitialConditions/initialcondition.cpp \
    InitialConditions/twobody.cpp \
    sampler.cpp \
    Integrators/velocityverlet.cpp \
    InitialConditions/randomspherical.cpp \
    random.cpp \
    realtime.cpp \
    Potentials/nopotential.cpp \
    InitialConditions/uniform.cpp \
    examples.cpp \
    InitialConditions/fcc.cpp \
    Thermostats/thermostat.cpp \
    Thermostats/berendsenthermostat.cpp \
    celllist.cpp

HEADERS += \
    atom.h \
    Integrators/integrator.h \
    Integrators/eulercromer.h \
    vec.h \
    Potentials/potential.h \
    Potentials/lennardjones.h \
    Potentials/gravitational.h \
    system.h \
    InitialConditions/initialcondition.h \
    InitialConditions/twobody.h \
    sampler.h \
    Integrators/velocityverlet.h \
    InitialConditions/randomspherical.h \
    random.h \
    realtime.h \
    Potentials/nopotential.h \
    InitialConditions/uniform.h \
    examples.h \
    InitialConditions/fcc.h \
    Thermostats/thermostat.h \
    Thermostats/berendsenthermostat.h \
    celllist.h

