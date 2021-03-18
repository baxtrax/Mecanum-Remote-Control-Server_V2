#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <QObject>
#include <QDebug>
#include <QSlider>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QCategoryAxis>

#include <math.h>
#include "constants.h"

class OutputHandler : public QObject
{
    Q_OBJECT
public:
    OutputHandler(QSlider *FRBL_topSliderRef,
                  QSlider *FRBL_botSliderRef,
                  QSlider *FLBR_topSliderRef,
                  QSlider *FLBR_botSliderRef,
                  QtCharts::QChartView *chartViewRef);
    void setIsDetailedChart(bool value);
    bool isDetailedChart();
public slots:
    void updateSliders(double, double);
    void updateChart(double, double, double, double, double);
private:
    QtCharts::QChartView *chartView;
    QSlider *FRBL_topSlider;
    QSlider *FRBL_botSlider;
    QSlider *FLBR_topSlider;
    QSlider *FLBR_botSlider;
    QtCharts::QCategoryAxis *axisX;
    QtCharts::QCategoryAxis *axisY;
    QtCharts::QSplineSeries *FRBLSeries;
    QtCharts::QSplineSeries *FLBRSeries;
    QtCharts::QLineSeries *dirSeries;
    QtCharts::QChart *chart;

    QPen *axisYPen;
    QPen *axisXPen;
    QPen *FRBLPen;
    QPen *FLBRPen;
    QPen *dirPen;

    QFont *axisLabelFont;
    QBrush *axisLabelPenBrush;

    bool isDetailed;

    void setFRBLSlider(double value);
    void setFLBRSlider(double value);

    void configurePenBrushFont();
    void configureAxis();
    void configureSeries();
    void configureChart();

    double linearMap(double input, double srcMin, double srcMax, double dstMin, double dstMax);
};

#endif // OUTPUTHANDLER_H
