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
    OutputHandler(LoggerHandler *loggerRef);
    void setDetailLevel(int level);
    int getCurrentDetailLevel();
    void configureChartView(QtCharts::QChartView *chartView);

public slots:
    void updateSliders(double, double, double, double);
    void updateChart(double, double, double, double);

signals:
    void FR_topSlider_ValChanged(double);
    void FR_botSlider_ValChanged(double);
    void BL_topSlider_ValChanged(double);
    void BL_botSlider_ValChanged(double);

    void FL_topSlider_ValChanged(double);
    void FL_botSlider_ValChanged(double);
    void BR_topSlider_ValChanged(double);
    void BR_botSlider_ValChanged(double);

private:

    QtCharts::QCategoryAxis *axisX;
    QtCharts::QCategoryAxis *axisY;

    QtCharts::QLineSeries *FRSeries;
    QtCharts::QLineSeries *BLSeries;
    QtCharts::QLineSeries *FLSeries;
    QtCharts::QLineSeries *BRSeries;

    double** FRarrPtr;
    double** BLarrPtr;
    double** FLarrPtr;
    double** BRarrPtr;

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
    double** generateSinePointsKinematics(int numberOfPoints,
                                                         double cycles,
                                                         double amp,
                                                         double yOffset,
                                                         double xOffset,
                                                         double mag,
                                                         double z,
                                                         double scale);
    void plotArray(double** arr, int graphNum);
    void configurePenBrushFont();
    void configureAxis();
    void configureSeries();
    void configureChart();
};

#endif // OUTPUTHANDLER_H
