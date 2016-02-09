TEMPLATE                 = app
CONFIG                  += console c++11
CONFIG                  += c++11
QMAKE_CXXFLAGS_RELEASE  -= -O2
QMAKE_CXXFLAGS_RELEASE  += -O3
#QMAKE_CXXFLAGS_RELEASE  += -fopenmp
#LIBS                    += -fopenmp

# MPI Settings
QMAKE_CXX = mpicxx
QMAKE_CXX_RELEASE = $$QMAKE_CXX
QMAKE_CXX_DEBUG = $$QMAKE_CXX
QMAKE_LINK = $$QMAKE_CXX
QMAKE_CC = mpicc

QMAKE_CFLAGS += $$system(mpicc --showme:compile)
QMAKE_LFLAGS += $$system(mpicxx --showme:link)
QMAKE_CXXFLAGS += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK
QMAKE_CXXFLAGS_RELEASE += $$system(mpicxx --showme:compile) -DMPICH_IGNORE_CXX_SEEK
INCLUDEPATH += /usr/local/include

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
    celllist.cpp \
    neighbourlist.cpp \
    Potentials/lennardjonescelllists.cpp \
    Potentials/lennardjonesneighbourlists.cpp

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
    celllist.h \
    neighbourlist.h \
    Potentials/lennardjonescelllists.h \
    Potentials/lennardjonesneighbourlists.h

