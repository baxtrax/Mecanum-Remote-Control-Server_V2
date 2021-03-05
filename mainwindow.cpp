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
    QtCharts::QSplineSeries *series2 = new QtCharts::QSplineSeries();

    QtCharts::QCategoryAxis *axisX = new QtCharts::QCategoryAxis();
    QtCharts::QCategoryAxis *axisY = new QtCharts::QCategoryAxis();

    //Axis colors
    QPen axisYPen(QBrush(QRgb(0x5E5E6F)), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen axisXPen(QBrush(QRgb(0x303046)), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    //Axis Labels
    QFont axisLabelFont("Open Sans ExtraBold", 14);
    QBrush axisLabelPen(QRgb(0xA3A3AD));

    axisY->setLabelsFont(axisLabelFont);
    axisY->setLabelsBrush(axisLabelPen);
    axisY->setLinePen(axisYPen);
    axisY->setGridLinePen(axisXPen);

    //axisX->setLinePen(axisXPen);
    axisX->setGridLineVisible(false);

    //Axis data
    axisY->append("-1.00 ", -1.00);
    axisY->append("0 ", 0);
    axisY->append("1.00 ", 1.00);
    axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    axisY->setRange(-1.1, 1.1);

    axisX->setRange(0.7, 14.3);



    //Line colors
    QLinearGradient lightPinkBruise_Gradient;
    lightPinkBruise_Gradient.setStart(QPointF(0, 0));
    lightPinkBruise_Gradient.setFinalStop(QPointF(1, 0));
    lightPinkBruise_Gradient.setColorAt(0.0, QRgb(0xDD3CFD));
    lightPinkBruise_Gradient.setColorAt(1.0, QRgb(0xFF6F7A));
    lightPinkBruise_Gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    QPen pen1(lightPinkBruise_Gradient, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QLinearGradient darkUltramarine_Gradient;
    lightPinkBruise_Gradient.setStart(QPointF(0, 0));
    lightPinkBruise_Gradient.setFinalStop(QPointF(1, 0));
    lightPinkBruise_Gradient.setColorAt(0.0, QRgb(0x7517F8));
    lightPinkBruise_Gradient.setColorAt(1.0, QRgb(0x02A4FF));
    lightPinkBruise_Gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    QPen pen2(lightPinkBruise_Gradient, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    series1->setPen(pen1);
    series1->setName("spline");

    series2->setPen(pen2);
    series2->setName("spline");

    //TODO generate and append data dynamically

    //Series 2
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
    //Series 1
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
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY);
    chart->setBackgroundVisible(false);
    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->setBackgroundRoundness(0);

    ui->kinematicsGraphView->setChart(chart);
    ui->kinematicsGraphView->setRenderHint(QPainter::Antialiasing);

}

//MainWindow deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}

