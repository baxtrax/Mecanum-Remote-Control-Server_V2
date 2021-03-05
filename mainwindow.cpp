#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QtCharts::QSplineSeries *series1 = new QtCharts::QSplineSeries();
    series1->setName("spline");
    series1->append(1, -0.71);
    series1->append(2, -0.3);
    series1->append(3, 0.18);
    series1->append(4, 0.62);
    series1->append(5, 0.91);
    series1->append(6, 1);
    series1->append(7, 0.86);
    series1->append(8, 0.52);
    series1->append(9, 0.06);
    series1->append(10, -0.41);
    series1->append(11, -0.79);
    series1->append(12, -0.98);
    series1->append(13, -0.95);
    series1->append(14, -0.71);

    ui->setupUi(this);
    QtCharts::QSplineSeries *series2 = new QtCharts::QSplineSeries();
    series2->setName("spline");
    series2->append(1, 0.71);
    series2->append(2, 0.95);
    series2->append(3, 0.98);
    series2->append(4, 0.79);
    series2->append(5, 0.41);
    series2->append(6, -0.06);
    series2->append(7, -0.52);
    series2->append(8, -0.86);
    series2->append(9, -1);
    series2->append(10, -0.91);
    series2->append(11, -0.62);
    series2->append(12, -0.18);
    series2->append(13, 0.3);
    series2->append(14, 0.71);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->createDefaultAxes();

    ui->kinematicsGraphView->setChart(chart);
    ui->kinematicsGraphView->setRenderHint(QPainter::Antialiasing);

}

//MainWindow deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}

