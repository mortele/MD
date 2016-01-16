#pragma once
#include <cmath>
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include "../../qcustomplot/qcustomplot.h"
#include "ui_mainwindow.h"


class Sampler;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    void plot(int, int, Sampler*);
    void setupRealtimePlot(int);
    void updateData(double*, double*, int);

    void setupRealtimeDataDemo(QCustomPlot *customPlot);

private slots:
  void realtimeDataSlot();
  void realtime();

private:
    int             n;
    int             Nt;
    int             currentIndex;
    int             oldIndex;
    QVector<double> xData;
    QVector<double> yData;
    Ui::MainWindow* ui;
    QTimer          dataTimer;
    QString         plotName;
    Sampler*        sampler;
};

