#include "outputhandler.h"


// Constructor
OutputHandler::OutputHandler(LoggerHandler *loggerRef, QSettings *settingsRef)
{
    logger = loggerRef;
    settings = settingsRef;

    detailLevel = SettingsConstants::ADVANCED_INFO;

    axisX = new QtCharts::QCategoryAxis();
    axisY = new QtCharts::QCategoryAxis();

    FRSeries = new QtCharts::QLineSeries();
    BLSeries = new QtCharts::QLineSeries();
    FLSeries = new QtCharts::QLineSeries();
    BRSeries = new QtCharts::QLineSeries();
    dirSeries = new QtCharts::QLineSeries();

    chart = new QtCharts::QChart;

    if (chart)
    {
        configurePenBrushFont();
        configureAxis();
        setMaxDataPoints(15);
        configureSeries();
        configureChart();

        updateChart(0,0,0,0);
    }
}


/**
 * @brief Configures all brushes used to style the chart.
 */
void OutputHandler::configurePenBrushFont()
{
    axisYPen = new QPen(QBrush(QColor(94,94,111)), 1,
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    axisXPen = new QPen(QBrush(QColor(48,48,70)), 1,
                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    axisLabelFont = new QFont("Open Sans", 12);
    axisLabelPenBrush = new QBrush(QColor(163,163,173));

    QBrush lightPinkBruise_GradientPenBrush = QBrush(QColor(232,77,209));

    QBrush darkUltramarine_GradientPenBrush = QBrush(QColor(79,70,250));

    FRBLPen = new QPen(lightPinkBruise_GradientPenBrush, 5,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    FLBRPen = new QPen(darkUltramarine_GradientPenBrush, 5,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QBrush dirPenBrush = QBrush(QColor(255,255,255));
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

    // TODO get rid of magic numbers
    // + and - are padding around max numbers shown
    axisY->setRange(IOConstants::MIN-0.1, IOConstants::MAX+0.1);
}


/**
 * @brief Configures all needed series with all the needed styling
 * and settings.
 */
void OutputHandler::configureSeries()
{
    FRSeries->setPen(*FRBLPen);
    BLSeries->setPen(*FRBLPen);
    FLSeries->setPen(*FLBRPen);
    BRSeries->setPen(*FLBRPen);
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

    chart->addSeries(FRSeries);
    chart->addSeries(BLSeries);
    chart->addSeries(FLSeries);
    chart->addSeries(BRSeries);
    chart->addSeries(dirSeries);

    FRSeries->attachAxis(axisX);
    FRSeries->attachAxis(axisY);
    BLSeries->attachAxis(axisX);
    BLSeries->attachAxis(axisY);
    FLSeries->attachAxis(axisX);
    FLSeries->attachAxis(axisY);
    BRSeries->attachAxis(axisX);
    BRSeries->attachAxis(axisY);
    dirSeries->attachAxis(axisX);
    dirSeries->attachAxis(axisY);

    useHardwareAcceleration(true);
}

void OutputHandler::configureChartView(QtCharts::QChartView *chartView)
{
    chartView->setStyleSheet("background-color: rgb(25, 25, 50);");
    chartView->hide();
    if (chart)
    {
        chartView->show();
        chartView->setChart(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    }
}


// TODO revamp algorithm to grab critical points instead of set points. Will
// give a better looking graph with less points
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
double** OutputHandler::generateSinePointsKinematics(int numberOfPoints,
                                                     double cycles,
                                                     double amp,
                                                     double yOffset,
                                                     double xOffset,
                                                     double mag,
                                                     double z,
                                                     double scale) {
    double y = 0.0;
    double f = cycles/double(numberOfPoints-1);
    double** arr = new double*[numberOfPoints];
    for (int i = 0; i < numberOfPoints; i++) {
        arr[i] = new double[2];
    }

    for (int t = 0; t < (numberOfPoints); t++) {
        y = std::clamp((roundf(((((amp * sin (2 * 3.14159 * f * t + xOffset)
                                   + yOffset) * mag) + z)/scale) * 100000)
                                   / 100000.0),
                       IOConstants::MIN,
                       IOConstants::MAX);
        arr[t][0] = t + 1;
        arr[t][1] = y;
    }
    return arr;
}


/**
 * @brief Updates sliders on GUI to repersent FR/BL and FL/BR values. Function
 * is called any time a kinematics value is updated or changed.
 */
void OutputHandler::updateSliders(double FRSpeed,
                                  double BLSpeed,
                                  double FLSpeed,
                                  double BRSpeed)
{
    setFRSlider(FRSpeed);
    setBLSlider(BLSpeed);
    setFLSlider(FLSpeed);
    setBRSlider(BRSpeed);
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
    if (chart && !(getCurrentDetailLevel() == SettingsConstants::DISABLED_INFO))
    {
        logger->write(LoggerConstants::DEBUG, "Updating kinematics chart ...");
        // Generate series showing vertical line where speeds are currently getting
        // fetched from.
        if(!(getCurrentDetailLevel() == SettingsConstants::DISABLED_INFO)) {
            if (dir < 0.0) { dir = dir + (2 * MathConstants::PI); }
            dir = linearMap(dir,
                            0,
                            (2 * MathConstants::PI),
                            IOConstants::MIN_XCHART,
                            getMaxDataPoints());
            dirSeries->clear();
            dirSeries->append(dir, IOConstants::MAX+.02);
            dirSeries->append(dir, IOConstants::MIN-.02);

            if (scaleFactor == 0) { scaleFactor = 1.0; }
        }

        // TODO Potentially switch over to using vectors? Statically allocated
        // arrays seems fine in this case as the array size does not change after
        // compile timer.
        // Show line at dir
        switch (getCurrentDetailLevel()) {
            case SettingsConstants::BASIC_INFO:
                // Generate mag and scale - 2 speed lines
                FRSeries->setVisible(true);
                BLSeries->setVisible(false);
                FLSeries->setVisible(true);
                BRSeries->setVisible(false);

                FRarrPtr = generateSinePointsKinematics(getMaxDataPoints(),
                                                        1.0,
                                                        1.0,
                                                        0.0,
                                                        (-(MathConstants::PI/4)),
                                                        mag,
                                                        0.0,
                                                        scaleFactor);

                FLarrPtr = generateSinePointsKinematics(getMaxDataPoints(),
                                                        1.0,
                                                        1.0,
                                                        0.0,
                                                        ((MathConstants::PI/4)),
                                                        mag,
                                                        0.0,
                                                        scaleFactor);

                FRSeries->clear();
                FLSeries->clear();

                plotArray(FRarrPtr, IOConstants::FR_GRAPH);
                plotArray(FLarrPtr, IOConstants::FL_GRAPH);

                // Clean up memory used by array
                for(int i=0; i<getMaxDataPoints(); i++) {
                    delete[] FRarrPtr[i];
                    delete[] FLarrPtr[i];
                }
                delete[] FRarrPtr;
                delete[] FLarrPtr;

                break;

            case SettingsConstants::DETAILED_INFO:
                //Generate Mag scale and z - 2 speed lines
                FRSeries->setVisible(true);
                BLSeries->setVisible(false);
                FLSeries->setVisible(true);
                BRSeries->setVisible(false);

                FRarrPtr = generateSinePointsKinematics(getMaxDataPoints(),
                                                        1.0,
                                                        1.0,
                                                        0.0,
                                                        (-(MathConstants::PI/4)),
                                                        mag,
                                                        z,
                                                        scaleFactor);

                FLarrPtr = generateSinePointsKinematics(getMaxDataPoints(),
                                                        1.0,
                                                        1.0,
                                                        0.0,
                                                        ((MathConstants::PI/4)),
                                                        mag,
                                                        z,
                                                        scaleFactor);
                FRSeries->clear();
                FLSeries->clear();

                plotArray(FRarrPtr, IOConstants::FR_GRAPH);
                plotArray(FLarrPtr, IOConstants::FL_GRAPH);

                // Clean up memory used by array
                for(int i=0; i<getMaxDataPoints(); i++) {
                    delete[] FRarrPtr[i];
                    delete[] FLarrPtr[i];
                }
                delete[] FRarrPtr;
                delete[] FLarrPtr;

                break;

            case SettingsConstants::ADVANCED_INFO:
                // Generate Mag scale and z - 4 speed lines
                FRSeries->setVisible(true);
                BLSeries->setVisible(true);
                FLSeries->setVisible(true);
                BRSeries->setVisible(true);

                FRarrPtr = generateSinePointsKinematics(getMaxDataPoints(),
                                                        1.0,
                                                        1.0,
                                                        0.0,
                                                        (-(MathConstants::PI/4)),
                                                        mag,
                                                        z,
                                                        scaleFactor);

                BLarrPtr = generateSinePointsKinematics(getMaxDataPoints(),
                                                        1.0,
                                                        -1.0,
                                                        0.0,
                                                        (-(MathConstants::PI/4)),
                                                        mag,
                                                        z,
                                                        scaleFactor);

                FLarrPtr = generateSinePointsKinematics(getMaxDataPoints(),
                                                        1.0,
                                                        -1.0,
                                                        0.0,
                                                        (MathConstants::PI/4),
                                                        mag,
                                                        z,
                                                        scaleFactor);

                BRarrPtr = generateSinePointsKinematics(getMaxDataPoints(),
                                                        1.0,
                                                        1.0,
                                                        0.0,
                                                        (MathConstants::PI/4),
                                                        mag,
                                                        z,
                                                        scaleFactor);
                FRSeries->clear();
                BLSeries->clear();
                FLSeries->clear();
                BRSeries->clear();

                for (int i=0; i<getMaxDataPoints(); i++) {
                    BLarrPtr[i][1] = -BLarrPtr[i][1];
                    FLarrPtr[i][1] = -FLarrPtr[i][1];
                }

                plotArray(FRarrPtr, IOConstants::FR_GRAPH);
                plotArray(BLarrPtr, IOConstants::BL_GRAPH);
                plotArray(FLarrPtr, IOConstants::FL_GRAPH);
                plotArray(BRarrPtr, IOConstants::BR_GRAPH);

                // Clean up memory used by array
                for(int i=0; i<getMaxDataPoints(); i++) {
                    delete[] FRarrPtr[i];
                    delete[] BLarrPtr[i];
                    delete[] FLarrPtr[i];
                    delete[] BRarrPtr[i];
                }
                delete[] FRarrPtr;
                delete[] BLarrPtr;
                delete[] FLarrPtr;
                delete[] BRarrPtr;

                break;
        }
    }
}


/**
 * @brief Adds speed points to their respective series
 * @param double array of speeds
 * @param int ammount of data points
 */
void OutputHandler::plotArray(double** arr, int graphNum) {
    double x, y;
    for (int i=0; i<getMaxDataPoints(); i++) {
        for (int j=0; j<2; j++) {
            if (j == 0) {
                x = arr[i][j];
            } else {
                y = arr[i][j];
            }
        }
        switch(graphNum) {
            case 0: FRSeries->append(x, y); break;
            case 1: BLSeries->append(x, y); break;
            case 2: FLSeries->append(x, y); break;
            case 3: BRSeries->append(x, y); break;
        }
    }
}

//TODO add to settings for chart
void OutputHandler::useHardwareAcceleration(bool value)
{
    FRSeries->setUseOpenGL(value);
    BLSeries->setUseOpenGL(value);
    FLSeries->setUseOpenGL(value);
    BRSeries->setUseOpenGL(value);
    dirSeries->setUseOpenGL(value);
}

void OutputHandler::updateWithSettings()
{
    qDebug() << "output handler update";
    bool enStatus = settings->value(SettingsConstants::GRAPH_PERF_EN, SettingsConstants::D_GRAPH_PERF_EN).toBool();
    if (chart)
    {
        emit setChartVisibility(enStatus);
        if (!enStatus)
        {
            setDetailLevel(SettingsConstants::DISABLED_INFO);
        } else {
            switch(settings->value(SettingsConstants::GRAPH_PERF_QUAL, SettingsConstants::D_GRAPH_PERF_QUAL).toInt())
            {
            case 0:
                setDetailLevel(SettingsConstants::BASIC_INFO);
                break;
            case 1:
                setDetailLevel(SettingsConstants::DETAILED_INFO);
                break;
            case 2:
                setDetailLevel(SettingsConstants::ADVANCED_INFO);
                break;
            }
        }
        setMaxDataPoints(settings->value(SettingsConstants::GRAPH_PERF_POINTS, SettingsConstants::D_GRAPH_PERF_POINTS).toInt());
        useHardwareAcceleration(settings->value(SettingsConstants::GRAPH_PERF_ACCEL, SettingsConstants::D_GRAPH_PERF_ACCEL).toBool());
        updateChart(0,0,0,0);
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

int OutputHandler::getMaxDataPoints()
{
    return maxDataPoints;
}


// Setters
/**
 * @brief Sets level of detail for graphing points of the kinematics.
 * @param int level as a constant from SettingsConstants choices.
 */
void OutputHandler::setDetailLevel(int level)
{
    detailLevel = level;
}

void OutputHandler::setMaxDataPoints(int value)
{
    maxDataPoints = value;
    //update datapoint ranges
    axisX->setRange(IOConstants::MIN_XCHART-0.3, value+0.3);
}


/**
 * @brief Sets value of FR slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX.
 */
void OutputHandler::setFRSlider(double value)
{
    double amplifiedFR = value * 100.0;
    if (amplifiedFR > 0.0) { // positive
        emit FR_botSlider_ValChanged(0.0);
        if (amplifiedFR <= IOConstants::MIN_SLIDER+13.0) {
            emit FR_topSlider_ValChanged(IOConstants::MIN_SLIDER+13.0);
        }  else {
            emit FR_topSlider_ValChanged(amplifiedFR);
        }
    } else if (amplifiedFR < 0.0) { // negative
        emit FR_topSlider_ValChanged(0.0);
        if (amplifiedFR >= -IOConstants::MIN_SLIDER-11.0) {
            emit FR_botSlider_ValChanged(-IOConstants::MIN_SLIDER-11.0);
        } else {
            emit FR_botSlider_ValChanged(amplifiedFR);
        }
    } else { // zero
        emit FR_botSlider_ValChanged(0.0);
        emit FR_topSlider_ValChanged(0.0);
    }
}


/**
 * @brief Sets value of BL slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX.
 */
void OutputHandler::setBLSlider(double value)
{
    double amplifiedBL = value * 100.0;
    if (amplifiedBL > 0.0) { // positive
        emit BL_botSlider_ValChanged(0.0);
        if (amplifiedBL <= IOConstants::MIN_SLIDER+13.0) {
            emit BL_topSlider_ValChanged(IOConstants::MIN_SLIDER+13.0);
        }  else {
            emit BL_topSlider_ValChanged(amplifiedBL);
        }
    } else if (amplifiedBL < 0.0) { // negative
        emit BL_topSlider_ValChanged(0.0);
        if (amplifiedBL >= -IOConstants::MIN_SLIDER-11.0) {
            emit BL_botSlider_ValChanged(-IOConstants::MIN_SLIDER-11.0);
        }  else {
            emit BL_botSlider_ValChanged(amplifiedBL);
        }
    } else { // zero
        emit BL_botSlider_ValChanged(0.0);
        emit BL_topSlider_ValChanged(0.0);
    }
}


/**
 * @brief Sets value of FLBR slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX.
 */
void OutputHandler::setFLSlider(double value)
{
    double amplifiedFL = value * 100.0;
    if (amplifiedFL > 0.0) { // positive
        emit FL_botSlider_ValChanged(0.0);
        if (amplifiedFL <= IOConstants::MIN_SLIDER+13.0) {
            emit FL_topSlider_ValChanged(IOConstants::MIN_SLIDER+13.0);
        }  else {
            emit FL_topSlider_ValChanged(amplifiedFL);
        }
    } else if (amplifiedFL < 0.0) { // negative
        emit FL_topSlider_ValChanged(0.0);
        if (amplifiedFL >= -IOConstants::MIN_SLIDER-11.0) {
            emit FL_botSlider_ValChanged(-IOConstants::MIN_SLIDER-11.0);
        }  else {
            emit FL_botSlider_ValChanged(amplifiedFL);
        }
    } else { // zero
        emit FL_botSlider_ValChanged(0.0);
        emit FL_topSlider_ValChanged(0.0);
    }
}


/**
 * @brief Sets value of FLBR slider scaled to fit.
 * @param double value between IOConstants::MIN and IOConstants::MAX.
 */
void OutputHandler::setBRSlider(double value)
{
    double amplifiedBR = value * 100.0;
    if (amplifiedBR > 0.0) { // positive
        emit BR_botSlider_ValChanged(0.0);
        if (amplifiedBR <= IOConstants::MIN_SLIDER+13.0) {
            emit BR_topSlider_ValChanged(IOConstants::MIN_SLIDER+13.0);
        }  else {
            emit BR_topSlider_ValChanged(amplifiedBR);
        }
    } else if (amplifiedBR < 0.0) { // negative
        emit BR_topSlider_ValChanged(0.0);
        if (amplifiedBR >= -IOConstants::MIN_SLIDER-11.0) {
            emit BR_botSlider_ValChanged(-IOConstants::MIN_SLIDER-11.0);
        }  else {
            emit BR_botSlider_ValChanged(amplifiedBR);
        }
    } else { // zero
        emit BR_botSlider_ValChanged(0.0);
        emit BR_topSlider_ValChanged(0.0);
    }
}

QtCharts::QChart* OutputHandler::getChart()
{
    return chart;
}


