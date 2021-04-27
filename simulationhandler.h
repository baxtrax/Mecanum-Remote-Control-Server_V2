#ifndef SIMULATIONHANDLER_H
#define SIMULATIONHANDLER_H

#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QVariantAnimation>

#include <QtDataVisualization/Q3DScatter>
#include <QtDataVisualization/QScatter3DSeries>
#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/QScatterDataItem>
#include <QtDataVisualization/QCustom3DItem>

#include "constants.h"

using namespace QtDataVisualization;

class SimulationHandler : public QObject
{
    Q_OBJECT
public:
    SimulationHandler();
    QWidget* getWidget();

public slots:
    void updateAnimators(double, double);

private:
    QWidget *simulationWidget;
    QScatter3DSeries *FLBRSeries;
    QScatter3DSeries *FRBLSeries;
    QScatterDataArray *wheelDataArray;
    QCustom3DItem *FRWheelMesh;
    QCustom3DItem *BLWheelMesh;
    QCustom3DItem *FLWheelMesh;
    QCustom3DItem *BRWheelMesh;
    Q3DScatter *graph;
    QVariantAnimation *FLBRAnimation;
    QVariantAnimation *FRBLAnimation;
    QQuaternion FLcurrentRotation;
    QQuaternion BRcurrentRotation;
    QQuaternion FRcurrentRotation;
    QQuaternion BLcurrentRotation;

    void setup3DOjects();
    void setupGraph();

};

#endif // SIMULATIONHANDLER_H
