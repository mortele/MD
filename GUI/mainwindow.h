#pragma once
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "../../qcustomplot/qcustomplot.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    Ui::MainWindow *ui;

    void plot(QCustomPlot *customPlot);

};

