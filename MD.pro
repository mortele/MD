TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11


SOURCES += main.cpp \
    atom.cpp \
    Integrators/integrator.cpp \
    Integrators/eulercromer.cpp \
    vec.cpp \
    Potentials/potential.cpp \
    Potentials/lennardjones.cpp

HEADERS += \
    atom.h \
    Integrators/integrator.h \
    Integrators/eulercromer.h \
    vec.h \
    Potentials/potential.h \
    Potentials/lennardjones.h

