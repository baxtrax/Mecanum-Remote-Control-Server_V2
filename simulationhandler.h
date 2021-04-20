#ifndef SIMULATIONHANDLER_H
#define SIMULATIONHANDLER_H

#include <QObject>
#include <QDebug>
#include <QWidget>

#include <QtDataVisualization/Q3DScatter>
#include <QtDataVisualization/QScatter3DSeries>
#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/QScatterDataItem>

#include "constants.h"

using namespace QtDataVisualization;

class SimulationHandler
{
public:
    SimulationHandler();
    QWidget* getWidget();
private:
    QWidget *simulationWidget;
    QScatter3DSeries *FLSeries;
    QScatter3DSeries *BRSeries;
    QScatter3DSeries *FRSeries;
    QScatter3DSeries *BLSeries;
    QScatterDataArray *wheelDataArray;
};

#endif // SIMULATIONHANDLER_H
