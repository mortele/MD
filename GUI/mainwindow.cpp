#include "mainwindow.h"
#include "ui_mainwindow.h"

using std::cout;
using std::endl;
using std::cos;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
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

    QVector<double> x(n);
    QVector<double> y(n);
    QVector<double> t(n);
    QVector<double> e(n);

    double eMin = 0;
    double eMax = 0;

    for (int i=0; i<n; i++) {
        t[i] = time[i];
        e[i] = energy[i];
        x[i] = xPosition[i];
        y[i] = yPosition[i];

        if (e[i] > eMax) {
            eMax = e[i];
        }
        if (e[i] < eMin) {
            eMin = e[i];
        }
    }

    cout << eMin << ", " << eMax << endl;
    // Position plot.
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(t, e);
    ui->customPlot->xAxis->setLabel("time");
    ui->customPlot->yAxis->setLabel("total energy");
    double k = 1.5;
    ui->customPlot->xAxis->setRange(0, t[n-1]);
    ui->customPlot->yAxis->setRange(eMin, eMax);
    //ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    //ui->customPlot->graph(0)->setLineStyle();

    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->xAxis->grid()->setSubGridVisible(true);

    ui->customPlot->replot();
}

void MainWindow::setupRealtimePlot(int Nt) {
    this->setupRealtimeDataDemo(ui->customPlot);
    /*this->oldIndex     = 0;
    this->currentIndex = 0;
    this->Nt           = Nt;
    this->xData = QVector<double>(Nt);
    this->yData = QVector<double>(Nt);

    ui->customPlot = ui->customPlot;
    ui->customPlot->addGraph(0);
    ui->customPlot->graph(0)->setPen(QPen(Qt::red));
    ui->customPlot->graph(0)->setData(this->xData, this->yData);
    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->yAxis->setLabel("Total energy");
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->xAxis->grid()->setSubGridVisible(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0);

    statusBar()->clearMessage();
    ui->customPlot->replot();*/
}

void MainWindow::updateData(double* xData, double* yData, int currentIndex) {
    this->currentIndex = currentIndex;

    if (this->currentIndex > this->oldIndex) {
        cout << "current=" << this->currentIndex
             << ", old="   << this->oldIndex << endl;
        for (int i=this->oldIndex; i < this->currentIndex; i++) {
            this->xData[i] = xData[i];
            this->yData[i] = yData[i];

            this->xData[i] = i/100.0;
            this->yData[i] = (i/100.0)/2.0;
        }
        this->oldIndex = this->currentIndex;

        ui->customPlot->graph(0)->setData(this->xData, this->yData);
        ui->customPlot->replot();

        //this->realtimeDataSlot();
        /*ui->customPlot->graph(0)->clearData();
        ui->customPlot->graph(0)->setData(this->xData, this->yData);
        ui->customPlot->replot();*/
    }
}

void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot) {
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
    //demoName = "Real Time Data Demo";

    // include this section to fully disable antialiasing for higher performance:
    /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    customPlot->graph(0)->setAntialiasedFill(false);
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(Qt::red));
    customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

    customPlot->addGraph(); // blue dot
    customPlot->graph(2)->setPen(QPen(Qt::blue));
    customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    customPlot->addGraph(); // red dot
    customPlot->graph(3)->setPen(QPen(Qt::red));
    customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setTickStep(2);
    customPlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtime()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::realtimeDataSlot() {
    //ui->customPlot->graph(0)->clearData();
    ui->customPlot->graph(0)->setData(this->xData, this->yData);
    ui->customPlot->replot();
}

void MainWindow::realtime() {
    // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    double key = 0;
#else
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
        double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
        // add data to lines:
        ui->customPlot->graph(0)->addData(key, value0);
        ui->customPlot->graph(1)->addData(key, value1);
        // set data of dots:
        ui->customPlot->graph(2)->clearData();
        ui->customPlot->graph(2)->addData(key, value0);
        ui->customPlot->graph(3)->clearData();
        ui->customPlot->graph(3)->addData(key, value1);
        // remove data of lines that's outside visible range:
        ui->customPlot->graph(0)->removeDataBefore(key-8);
        ui->customPlot->graph(1)->removeDataBefore(key-8);
        // rescale value (vertical) axis to fit the current data:
        ui->customPlot->graph(0)->rescaleValueAxis();
        ui->customPlot->graph(1)->rescaleValueAxis(true);
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->customPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->statusbar->showMessage(
                    QString("%1 FPS, Total Data points: %2")
                    .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                    .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
                    , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
}





