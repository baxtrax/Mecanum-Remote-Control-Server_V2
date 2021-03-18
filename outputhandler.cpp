#include "outputhandler.h"

OutputHandler::OutputHandler(QSlider *FRBL_topSliderRef,
                             QSlider *FRBL_botSliderRef,
                             QSlider *FLBR_topSliderRef,
                             QSlider *FLBR_botSliderRef,
                             QtCharts::QChartView *chartViewRef)
{
    chartView = chartViewRef;
    FRBL_topSlider = FRBL_topSliderRef;
    FRBL_botSlider = FRBL_botSliderRef;
    FLBR_topSlider = FLBR_topSliderRef;
    FLBR_botSlider = FLBR_botSliderRef;
    isDetailed = false;
    axisX = new QtCharts::QCategoryAxis();
    axisY = new QtCharts::QCategoryAxis();
    FRBLSeries = new QtCharts::QSplineSeries();
    FLBRSeries = new QtCharts::QSplineSeries();
    dirSeries = new QtCharts::QLineSeries();
    chart = new QtCharts::QChart();
    configurePenBrushFont();
    configureAxis();
    configureSeries();
    configureChart();
}


void OutputHandler::configurePenBrushFont()
{
    axisYPen = new QPen(QBrush(QRgb(0x5E5E6F)), 2,
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    axisXPen = new QPen(QBrush(QRgb(0x303046)), 2,
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    axisLabelFont = new QFont("Open Sans", 12);
    axisLabelPenBrush = new QBrush(QRgb(0xA3A3AD));

    QLinearGradient lightPinkBruise_Gradient;
    lightPinkBruise_Gradient.setStart(QPointF(0, 0));
    lightPinkBruise_Gradient.setFinalStop(QPointF(1, 0));
    lightPinkBruise_Gradient.setColorAt(0.0, QRgb(0xDD3CFD));
    lightPinkBruise_Gradient.setColorAt(1.0, QRgb(0xFF6F7A));
    lightPinkBruise_Gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    QLinearGradient darkUltramarine_Gradient;
    darkUltramarine_Gradient.setStart(QPointF(0, 0));
    darkUltramarine_Gradient.setFinalStop(QPointF(1, 0));
    darkUltramarine_Gradient.setColorAt(0.0, QRgb(0x7517F8));
    darkUltramarine_Gradient.setColorAt(1.0, QRgb(0x02A4FF));
    darkUltramarine_Gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    FRBLPen = new QPen(lightPinkBruise_Gradient, 10,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    FLBRPen = new QPen(darkUltramarine_Gradient, 10,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QBrush dirPenBrush = QBrush(QRgb(0xFFFFFF/*0x6EFE74*/));
    dirPen = new QPen(dirPenBrush, 5,
                      Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

}

void OutputHandler::configureAxis()
{
    axisY->setLabelsFont(*axisLabelFont);
    axisY->setLabelsBrush(*axisLabelPenBrush);
    axisY->setLinePen(*axisYPen);
    axisY->setGridLinePen(*axisXPen);
    axisX->setGridLineVisible(false);

    //Axis data
    axisY->append("-1.00 ", IOConstants::MIN);
    axisY->append("0 ", 0);
    axisY->append("1.00 ", IOConstants::MAX);
    axisY->setLabelsPosition(QtCharts::
                                 QCategoryAxis::AxisLabelsPositionOnValue);
    // + and - are padding around max numbers shown
    axisY->setRange(IOConstants::MIN-0.1, IOConstants::MAX+0.1);
    axisX->setRange(IOConstants::MIN_XCHART-0.3, IOConstants::MAX_XCHART+0.3);
}



void OutputHandler::configureSeries()
{
    FRBLSeries->setPen(*FRBLPen);
    FLBRSeries->setPen(*FLBRPen);
    dirSeries->setPen(*dirPen);
}

void OutputHandler::configureChart()
{
    configureAxis();
    // Adding details
    chart->legend()->hide();
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->setBackgroundVisible(false);
    // Removing unneeded space around chart
    chart->setMargins(QMargins(0, 0, 0, -20)); //-20 removes unnessary x-axis
    chart->setBackgroundRoundness(0);
    chartView->setChart(chart);
    chartView->setStyleSheet(NULL);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->addSeries(FRBLSeries);
    chartView->chart()->addSeries(FLBRSeries);
    chartView->chart()->addSeries(dirSeries);
    FRBLSeries->attachAxis(axisX);
    FRBLSeries->attachAxis(axisY);
    FLBRSeries->attachAxis(axisX);
    FLBRSeries->attachAxis(axisY);
    dirSeries->attachAxis(axisX);
    dirSeries->attachAxis(axisY);
}

double OutputHandler::linearMap(double input, double srcMin, double srcMax, double dstMin, double dstMax)
{
    return (((input-srcMin) / (srcMax-srcMin)) * (dstMax-dstMin) + dstMin);
}



double** generateSinePointsKinematics(int numberOfPoints, double cycles, double amp, double yOffset, double xOffset, double mag, double z, double scale) {
    double y = 0.0;
    double f = cycles/double(numberOfPoints-1);
    double** arr = new double*[numberOfPoints];
    for (int i = 0; i < numberOfPoints; i++) {
        arr[i] = new double[2];
    }

    for (int t=0; t<(numberOfPoints); t++) {
        y = roundf(((((amp * sin (2 * 3.14159 * f * t + xOffset) + yOffset) * mag) + z)/scale) * 100000) / 100000.0;
        arr[(t)][0] = t+1;
        arr[(t)][1] = y;
    }
    return arr;
}


double** generateSinePointsKinematics(int numberOfPoints, double cycles, double amp, double yOffset, double xOffset, double mag) {
    return generateSinePointsKinematics(numberOfPoints, cycles, amp, yOffset, xOffset, mag, 0.0, 1.0);
}


/**
 * @brief Updates sliders on GUI to repersent FR/BL and FL/BR values. Function
 * is called any time a kinematics value is updated or changed.
 */
void OutputHandler::updateSliders(double FRBLSpeed, double FLBRSpeed)
{
    setFRBLSlider(FRBLSpeed);
    setFLBRSlider(FLBRSpeed);
}


void OutputHandler::updateChart(double dir,
                                double mag,
                                double z,
                                double FRBLscaleFactor,
                                double FLBRscaleFactor)
{
    if (dir < 0.0) { dir = dir + (2 * MathConstants::PI); }
    dir = linearMap(dir,
                    0,
                    (2 * MathConstants::PI),
                    IOConstants::MIN_XCHART,
                    IOConstants::MAX_XCHART);
    dirSeries->clear();
    dirSeries->append(dir, IOConstants::MAX+.02);
    dirSeries->append(dir, IOConstants::MIN-.02);

    if (isDetailedChart()) {
        //Setup x and y.
        double x, y = -99.99;
        double scale = 0.0;
        if (FRBLscaleFactor > FLBRscaleFactor) {
            scale = FRBLscaleFactor;
        } else if (FRBLscaleFactor < FLBRscaleFactor) {
            scale = FLBRscaleFactor;
        } else {
            scale = FRBLscaleFactor;
        }
        double** FRBLarrPtr = generateSinePointsKinematics(IOConstants::MAX_XCHART, 1.0, 1.0, 0.0, (-(MathConstants::PI/4)), mag, z, scale);
        FRBLSeries->clear();
        for (int i=0; i<IOConstants::MAX_XCHART; i++) {
            for (int j=0; j<2; j++) {
                if (j == 0) {
                    x = FRBLarrPtr[i][j];
                } else {
                    y = FRBLarrPtr[i][j];
                }
                //qDebug() << arrPtr[i][j] << " ";
            }
            qDebug() << "FRBL" << x << y;
            FRBLSeries->append(x, y);
        }
        //Clean up memory used by array
        for(int i=0; i<IOConstants::MAX_XCHART; i++) {
            delete[] FRBLarrPtr[i];
        }
        delete[] FRBLarrPtr;
        //TODO Potentially switch over to using vectors? Statically allocated,
        //seems fine in this case as the array size does not change.

        //Reset x and y
        x = -99.99;
        y = -99.99;

        double** FLBRarrPtr = generateSinePointsKinematics(IOConstants::MAX_XCHART, 1.0, 1.0, 0.0, ((MathConstants::PI/4)), mag, z, scale);
        FLBRSeries->clear();
        for (int i=0; i<IOConstants::MAX_XCHART; i++) {
            for (int j=0; j<2; j++) {
                if (j == 0) {x = FLBRarrPtr[i][j];} else {y = FLBRarrPtr[i][j];}
                //qDebug() << arrPtr[i][j] << " ";
            }
            qDebug() << "FRBL" << x << y;
            FLBRSeries->append(x, y);
        }
        //Clean up memory used by array
        for(int i=0; i<IOConstants::MAX_XCHART; i++) {
            delete[] FLBRarrPtr[i];
        }
        delete[] FLBRarrPtr;
        //TODO Potentially switch over to using vectors? Statically allocated,
        //seems fine in this case as the array size does not change.
        // Draw chart with mag, z, and scale

        // Generate data of wave with mag, z, and scale
        // Erase current series
        // Add new generated data

        // Generate series showing vertical line at dir
        // Show line at dir
    } else {
        //Setup x and y.
        double x, y = -99.99;

        double** FRBLarrPtr = generateSinePointsKinematics(IOConstants::MAX_XCHART, 1.0, 1.0, 0.0, (-(MathConstants::PI/4)), mag);
        FRBLSeries->clear();
        for (int i=0; i<IOConstants::MAX_XCHART; i++) {
            for (int j=0; j<2; j++) {
                if (j == 0) {
                    x = FRBLarrPtr[i][j];
                } else {
                    y = FRBLarrPtr[i][j];
                }
                //qDebug() << arrPtr[i][j] << " ";
            }
            qDebug() << "FRBL" << x << y;
            FRBLSeries->append(x, y);
        }
        //Clean up memory used by array
        for(int i=0; i<IOConstants::MAX_XCHART; i++) {
            delete[] FRBLarrPtr[i];
        }
        delete[] FRBLarrPtr;
        //TODO Potentially switch over to using vectors? Statically allocated,
        //seems fine in this case as the array size does not change.

        //Reset x and y
        x = -99.99;
        y = -99.99;

        double** FLBRarrPtr = generateSinePointsKinematics(IOConstants::MAX_XCHART, 1.0, 1.0, 0.0, ((MathConstants::PI/4)), mag);
        FLBRSeries->clear();
        for (int i=0; i<IOConstants::MAX_XCHART; i++) {
            for (int j=0; j<2; j++) {
                if (j == 0) {x = FLBRarrPtr[i][j];} else {y = FLBRarrPtr[i][j];}
                //qDebug() << arrPtr[i][j] << " ";
            }
            qDebug() << "FRBL" << x << y;
            FLBRSeries->append(x, y);
        }
        //Clean up memory used by array
        for(int i=0; i<IOConstants::MAX_XCHART; i++) {
            delete[] FLBRarrPtr[i];
        }
        delete[] FLBRarrPtr;
        //TODO Potentially switch over to using vectors? Statically allocated,
        //seems fine in this case as the array size does not change.
    }
}


bool OutputHandler::isDetailedChart()
{
    return (isDetailed);
}


void OutputHandler::setIsDetailedChart(bool value)
{
    isDetailed = value;
}


//Setters
/**
 * @brief Sets value of FRBL slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX
 */
void OutputHandler::setFRBLSlider(double value)
{
    double amplifiedFRBL = value * 100.0;
    if (amplifiedFRBL > 0.0) { // positive
        FRBL_botSlider->setValue(0.0);
        if (amplifiedFRBL <= IOConstants::MIN_SLIDER) {
            FRBL_topSlider->setValue(IOConstants::MIN_SLIDER);
        }  else {
            FRBL_topSlider->setValue(amplifiedFRBL);
        }
    } else if (amplifiedFRBL < 0.0) { // negative
        FRBL_topSlider->setValue(0.0);
        if (amplifiedFRBL >= -IOConstants::MIN_SLIDER) {
            FRBL_botSlider->setValue(-IOConstants::MIN_SLIDER);
        }  else {
            FRBL_botSlider->setValue(amplifiedFRBL);
        }
    } else { // zero
        FRBL_botSlider->setValue(0.0);
        FRBL_topSlider->setValue(0.0);
    }
}


/**
 * @brief Sets value of FLBR slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX
 */
void OutputHandler::setFLBRSlider(double value)
{
    double amplifiedFLBR = value * 100.0;
    if (amplifiedFLBR > 0.0) { // positive
        FLBR_botSlider->setValue(0.0);
        if (amplifiedFLBR <= IOConstants::MIN_SLIDER) {
            FLBR_topSlider->setValue(IOConstants::MIN_SLIDER);
        }  else {
            FLBR_topSlider->setValue(amplifiedFLBR);
        }
    } else if (amplifiedFLBR < 0.0) { // negative
        FLBR_topSlider->setValue(0.0);
        if (amplifiedFLBR >= -IOConstants::MIN_SLIDER) {
            FLBR_botSlider->setValue(-IOConstants::MIN_SLIDER);
        }  else {
            FLBR_botSlider->setValue(amplifiedFLBR);
        }
    } else { // zero
        FLBR_botSlider->setValue(0.0);
        FLBR_topSlider->setValue(0.0);
    }
}
