#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) ,
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    int k = 600;
    setGeometry(100,100,1.5*k,k);
}

void MainWindow::plot(int n,
                      double* xPosition,
                      double* yPosition,
                      double* time,
                      double* energy) {
    customPlot = ui->customPlot;

    QVector<double> x(n);
    QVector<double> y(n);
    QVector<double> t(n);
    QVector<double> e(n);

    for (int i=0; i<n; i++) {
        t[i] = time[i];
        e[i] = energy[i];
        x[i] = xPosition[i];
        y[i] = yPosition[i];
    }

    // Position plot.
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    customPlot->xAxis->setLabel("x position");
    customPlot->yAxis->setLabel("y position");
    double k = 1.5;
    customPlot->xAxis->setRange(-1.2*k, 1.2*k);
    customPlot->yAxis->setRange(-1.2, 1.2);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);

    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->xAxis->grid()->setSubGridVisible(true);

    customPlot->replot();
}

