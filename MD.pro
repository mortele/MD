TEMPLATE = app
CONFIG += console c++11
CONFIG += c++11
QT += widgets printsupport

SOURCES += main.cpp \
    atom.cpp \
    Integrators/integrator.cpp \
    Integrators/eulercromer.cpp \
    vec.cpp \
    Potentials/potential.cpp \
    Potentials/lennardjones.cpp \
    Potentials/gravitational.cpp \
    ../../qcustomplot/qcustomplot.cpp \
    GUI/mainwindow.cpp \
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
    InitialConditions/staticfcc.cpp \
    InitialConditions/fcc.cpp \
    Thermostats/thermostat.cpp \
    Thermostats/berendsenthermostat.cpp

HEADERS += \
    atom.h \
    Integrators/integrator.h \
    Integrators/eulercromer.h \
    vec.h \
    Potentials/potential.h \
    Potentials/lennardjones.h \
    Potentials/gravitational.h \
    ../../qcustomplot/qcustomplot.h \
    GUI/mainwindow.h \
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
    InitialConditions/staticfcc.h \
    InitialConditions/fcc.h \
    Thermostats/thermostat.h \
    Thermostats/berendsenthermostat.h

FORMS += \
    mainwindow.ui

