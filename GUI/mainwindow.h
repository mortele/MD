#pragma once
#include <cmath>
#include <iostream>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "../../qcustomplot/qcustomplot.h"
#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget *parent = 0);
    void plot(int, double*, double*, double*, double*);

private:
    Ui::MainWindow *ui;
    QCustomPlot *customPlot;

};

