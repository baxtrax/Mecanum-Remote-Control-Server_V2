#include "outputhandler.h"

OutputHandler::OutputHandler(QSlider *FRBL_topSliderRef,
                             QSlider *FRBL_botSliderRef,
                             QSlider *FLBR_topSliderRef,
                             QSlider *FLBR_botSliderRef,
                             QtCharts::QChartView *chartViewRef,
                             LoggerHandler *loggerRef)
{
    chartView = chartViewRef;
    logger = loggerRef;
    FRBL_topSlider = FRBL_topSliderRef;
    FRBL_botSlider = FRBL_botSliderRef;
    FLBR_topSlider = FLBR_topSliderRef;
    FLBR_botSlider = FLBR_botSliderRef;
    detailLevel = SettingsConstants::DETAILED_INFO;
    axisX = new QtCharts::QCategoryAxis();
    axisY = new QtCharts::QCategoryAxis();
    FRBLSeries = new QtCharts::QLineSeries();
    FLBRSeries = new QtCharts::QLineSeries();
    dirSeries = new QtCharts::QLineSeries();
    chart = new QtCharts::QChart();
    configurePenBrushFont();
    configureAxis();
    configureSeries();
    configureChart();
    updateChart(0,0,0,0);
}


/**
 * @brief Configures all brushes used to style the chart.
 */
void OutputHandler::configurePenBrushFont()
{
    axisYPen = new QPen(QBrush(QRgb(0x5E5E6F)), 1,
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    axisXPen = new QPen(QBrush(QRgb(0x303046)), 1,
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    axisLabelFont = new QFont("Open Sans", 12);
    axisLabelPenBrush = new QBrush(QRgb(0xA3A3AD));

    QLinearGradient lightPinkBruise_Gradient;
    lightPinkBruise_Gradient.setStart(QPointF(0, 0));
    lightPinkBruise_Gradient.setFinalStop(QPointF(1, 0));
    lightPinkBruise_Gradient.setColorAt(0.0, QRgb(0xDD3CFD));
    lightPinkBruise_Gradient.setColorAt(1.0, QRgb(0xFF6F7A));
    lightPinkBruise_Gradient.setCoordinateMode(QGradient::StretchToDeviceMode);

    QLinearGradient darkUltramarine_Gradient;
    darkUltramarine_Gradient.setStart(QPointF(0, 0));
    darkUltramarine_Gradient.setFinalStop(QPointF(1, 0));
    darkUltramarine_Gradient.setColorAt(0.0, QRgb(0x7517F8));
    darkUltramarine_Gradient.setColorAt(1.0, QRgb(0x02A4FF));
    darkUltramarine_Gradient.setCoordinateMode(QGradient::StretchToDeviceMode);

    FRBLPen = new QPen(lightPinkBruise_Gradient, 5,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    FLBRPen = new QPen(darkUltramarine_Gradient, 5,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QBrush dirPenBrush = QBrush(QRgb(0xFFFFFF));
    dirPen = new QPen(dirPenBrush, 3,
                      Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

}


/**
 * @brief Configures all needed axis with all the needed styling
 * and settings.
 */
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


/**
 * @brief Configures all needed series with all the needed styling
 * and settings.
 */
void OutputHandler::configureSeries()
{
    FRBLSeries->setPen(*FRBLPen);
    FLBRSeries->setPen(*FLBRPen);
    dirSeries->setPen(*dirPen);
}


/**
 * @brief Configures the specified chart with all the needed styling
 * and settings.
 */
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


/**
 * @brief Maps one output range to another range and returns the number if it
 * where on that scale.
 * @param double input value
 * @param double min range of source
 * @param double max range of source
 * @param double min range of desired
 * @param double max range of desired
 * @return double number maped to new range.
 */
double OutputHandler::linearMap(double input, double srcMin, double srcMax, double dstMin, double dstMax)
{
    return (((input-srcMin) / (srcMax-srcMin)) * (dstMax-dstMin) + dstMin);
}


/**
 * @brief Generates a set number of data points of a modified sine function. The
 * modified sine function is the basis of the kinematics for a mechanum drive
 * system.
 * @param int number of data points in array generated.
 * @param double cycles from start to finsh.
 * @param double amplitude of sine.
 * @param double up and down offset.
 * @param double left and right offset.
 * @param double magnitude of force (how fast).
 * @param double z coordinate of input.
 * @param double value that is used for normalization.
 * @return double array of pointers pointing to data points.
 */
double** generateSinePointsKinematics(int numberOfPoints, double cycles, double amp, double yOffset, double xOffset, double mag, double z, double scale) {
    double y = 0.0;
    double f = cycles/double(numberOfPoints-1);
    double** arr = new double*[numberOfPoints];
    for (int i = 0; i < numberOfPoints; i++) {
        arr[i] = new double[2];
    }

    for (int t=0; t<(numberOfPoints); t++) {
        //y = (roundf(((((amp * sin (2 * 3.14159 * f * t + xOffset) + yOffset) * mag) + z)/scale) * 100000) / 100000.0);
        y = std::clamp((roundf(((((amp * sin (2 * 3.14159 * f * t + xOffset) + yOffset) * mag) + z)/scale) * 100000) / 100000.0), IOConstants::MIN, IOConstants::MAX);
        arr[(t)][0] = t+1;
        arr[(t)][1] = y;
    }
    return arr;
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


//TODO this function needs heavy performance fixes
//TODO add option in settings to adjust detail level and ammount of data points
/**
 * @brief Main update function that calls all he needs functions for updating
 * the graph to new data that has been sent. Performance is directly connected
 * connected to how many points per update need to be generated.
 * @param double direction of force.
 * @param double magnitude of force (how fast).
 * @param double z coordinate of input.
 * @param double value that is used for normalization.
 */
void OutputHandler::updateChart(double dir,
                                double mag,
                                double z,
                                double scaleFactor)
{
    logger->write(LoggerConstants::DEBUG, "Updating kinematics chart ...");
    // Generate series showing vertical line where speeds are currently getting
    // fetched from.
    if (dir < 0.0) { dir = dir + (2 * MathConstants::PI); }
    dir = linearMap(dir,
                    0,
                    (2 * MathConstants::PI),
                    IOConstants::MIN_XCHART,
                    IOConstants::MAX_XCHART);
    dirSeries->clear();
    dirSeries->append(dir, IOConstants::MAX+.02);
    dirSeries->append(dir, IOConstants::MIN-.02);

    if (scaleFactor == 0) { scaleFactor = 1.0; }

    double x, y = -9.9;
    // TODO Potentially switch over to using vectors? Statically allocated
    // arrays seems fine in this case as the array size does not change after
    // compile timer.
    double** FRBLarrPtr;
    double** FLBRarrPtr;

    // Show line at dir
    switch (getCurrentDetailLevel()) {
        case SettingsConstants::BASIC_INFO:
            // Generate data of wave with mag, and scale for FRBL
            FRBLarrPtr = generateSinePointsKinematics(IOConstants::MAX_XCHART,
                                                      1.0,
                                                      1.0,
                                                      0.0,
                                                      (-(MathConstants::PI/4)),
                                                      mag,
                                                      0.0,
                                                      scaleFactor);
            FRBLSeries->clear();
            for (int i=0; i<IOConstants::MAX_XCHART; i++) {
                for (int j=0; j<2; j++) {
                    if (j == 0) {
                        x = FRBLarrPtr[i][j];
                    } else {
                        y = FRBLarrPtr[i][j];
                    }
                }
                //qDebug() << "FRBL" << x << y;
                // Add new generated data
                FRBLSeries->append(x, y);
            }
            // Clean up memory used by array
            for(int i=0; i<IOConstants::MAX_XCHART; i++) {
                delete[] FRBLarrPtr[i];
            }
            delete[] FRBLarrPtr;

            // Generate data of wave with mag, and scale for FLBR
            FLBRarrPtr = generateSinePointsKinematics(IOConstants::MAX_XCHART,
                                                      1.0,
                                                      1.0,
                                                      0.0,
                                                      ((MathConstants::PI/4)),
                                                      mag,
                                                      0.0,
                                                      scaleFactor);
            FLBRSeries->clear();
            for (int i=0; i<IOConstants::MAX_XCHART; i++) {
                for (int j=0; j<2; j++) {
                    if (j == 0) {
                        x = FLBRarrPtr[i][j];
                    } else {
                        y = FLBRarrPtr[i][j];
                    }
                }
                //qDebug() << "FRBL" << x << y;
                FLBRSeries->append(x, y);
            }
            // Clean up memory used by array
            for(int i=0; i<IOConstants::MAX_XCHART; i++) {
                delete[] FLBRarrPtr[i];
            }
            delete[] FLBRarrPtr;
            break;
        case SettingsConstants::DETAILED_INFO:
            // Generate data of wave with mag, z, and scale for FRBL
            FRBLarrPtr = generateSinePointsKinematics(IOConstants::MAX_XCHART,
                                                      1.0,
                                                      1.0,
                                                      0.0,
                                                      (-(MathConstants::PI/4)),
                                                      mag,
                                                      z,
                                                      scaleFactor);
            FRBLSeries->clear();
            for (int i=0; i<IOConstants::MAX_XCHART; i++) {
                for (int j=0; j<2; j++) {
                    if (j == 0) {
                        x = FRBLarrPtr[i][j];
                    } else {
                        y = FRBLarrPtr[i][j];
                    }
                }
                //qDebug() << "FRBL" << x << y;
                FRBLSeries->append(x, y);
            }
            // Clean up memory used by array
            for(int i=0; i<IOConstants::MAX_XCHART; i++) {
                delete[] FRBLarrPtr[i];
            }
            delete[] FRBLarrPtr;
            // Generate data of wave with mag, z, and scale for FLBR
            FLBRarrPtr = generateSinePointsKinematics(IOConstants::MAX_XCHART,
                                                      1.0,
                                                      1.0,
                                                      0.0,
                                                      ((MathConstants::PI/4)),
                                                      mag,
                                                      z,
                                                      scaleFactor);
            FLBRSeries->clear();
            for (int i=0; i<IOConstants::MAX_XCHART; i++) {
                for (int j=0; j<2; j++) {
                    if (j == 0) {
                        x = FLBRarrPtr[i][j];
                    } else {
                        y = FLBRarrPtr[i][j];
                    }
                }
                //qDebug() << "FRBL" << x << y;
                FLBRSeries->append(x, y);
            }
            // Clean up memory used by array
            for(int i=0; i<IOConstants::MAX_XCHART; i++) {
                delete[] FLBRarrPtr[i];
            }
            delete[] FLBRarrPtr;
            break;
    }
}


// Getters

/**
 * @brief Gets current detail level that the graphing is set at.
 * @return int value of enum that detail is set at.
 */
int OutputHandler::getCurrentDetailLevel()
{
    return detailLevel;
}


// Setters

// TODO Add wrong input checking
/**
 * @brief Sets level of detail for graphing points of the kinematics.
 * @param int level as a constant from SettingsConstants choices.
 */
void OutputHandler::setDetailLevel(int level)
{
    detailLevel = level;
}


/**
 * @brief Sets value of FRBL slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX.
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
 * @param double value between IOConstants::MIN and IOConstants::MAX.
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
