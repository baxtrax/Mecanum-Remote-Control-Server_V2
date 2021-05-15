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
#include "loggerhandler.h"
#include "helper.h"

class OutputHandler : public QObject
{
    Q_OBJECT
public:
    OutputHandler(QSlider *FR_topSliderRef,
                  QSlider *FR_botSliderRef,
                  QSlider *BL_topSliderRef,
                  QSlider *BL_botSliderRef,
                  QSlider *FL_topSliderRef,
                  QSlider *FL_botSliderRef,
                  QSlider *BR_topSliderRef,
                  QSlider *BR_botSliderRef,
                  QtCharts::QChartView *chartViewRef,
                  LoggerHandler *loggerRef);
    void setDetailLevel(int level);
    int getCurrentDetailLevel();
public slots:
    void updateSliders(double, double, double, double);
    void updateChart(double, double, double, double);
private:
    QtCharts::QChartView *chartView;
    QSlider *FR_topSlider;
    QSlider *FR_botSlider;
    QSlider *BL_topSlider;
    QSlider *BL_botSlider;

    QSlider *FL_topSlider;
    QSlider *FL_botSlider;
    QSlider *BR_topSlider;
    QSlider *BR_botSlider;
    QtCharts::QCategoryAxis *axisX;
    QtCharts::QCategoryAxis *axisY;
    QtCharts::QLineSeries *FRBLSeries;
    QtCharts::QLineSeries *FLBRSeries;
    QtCharts::QLineSeries *dirSeries;
    QtCharts::QChart *chart;
    LoggerHandler *logger;

    QPen *axisYPen;
    QPen *axisXPen;
    QPen *FRBLPen;
    QPen *FLBRPen;
    QPen *dirPen;

    QFont *axisLabelFont;
    QBrush *axisLabelPenBrush;

    int detailLevel;

    void setFRSlider(double value);
    void setBLSlider(double value);
    void setFLSlider(double value);
    void setBRSlider(double value);

    void configurePenBrushFont();
    void configureAxis();
    void configureSeries();
    void configureChart();

    //double linearMap(double input, double srcMin, double srcMax, double dstMin, double dstMax);
};

#endif // OUTPUTHANDLER_H
