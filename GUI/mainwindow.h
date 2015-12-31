#pragma once
#include <cmath>
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include "../../qcustomplot/qcustomplot.h"
#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    void plot(int, double*, double*, double*, double*);
    void setupRealtimePlot(int);
    void updateData(double*, double*, int);

    void setupRealtimeDataDemo(QCustomPlot *customPlot);

private slots:
  void realtimeDataSlot();
  void realtime();

private:
    int             Nt;
    int             currentIndex;
    int             oldIndex;
    QVector<double> xData;
    QVector<double> yData;
    Ui::MainWindow* ui;
    //QCustomPlot*    customPlot;
    QTimer          dataTimer;
    QString         plotName;
};

