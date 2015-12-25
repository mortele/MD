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
    GUI/mainwindow.cpp

HEADERS += \
    atom.h \
    Integrators/integrator.h \
    Integrators/eulercromer.h \
    vec.h \
    Potentials/potential.h \
    Potentials/lennardjones.h \
    Potentials/gravitational.h \
    ../../qcustomplot/qcustomplot.h \
    GUI/mainwindow.h

FORMS += \
    mainwindow.ui

