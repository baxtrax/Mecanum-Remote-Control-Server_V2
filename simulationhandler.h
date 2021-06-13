#ifndef SIMULATIONHANDLER_H
#define SIMULATIONHANDLER_H

#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QVariantAnimation>
#include <QLabel>
#include <QSettings>

#include <QtDataVisualization/Q3DScatter>
#include <QtDataVisualization/QScatter3DSeries>
#include <QtDataVisualization/QScatterDataProxy>
#include <QtDataVisualization/QScatterDataItem>
#include <QtDataVisualization/QCustom3DItem>

#include "constants.h"
#include "helper.h"

using namespace QtDataVisualization;

class SimulationHandler : public QObject
{
    Q_OBJECT
public:
    SimulationHandler(QSettings *settingsRef, QFrame *debugInfoFrameRef);
    QWidget* getWidget();

public slots:
    void updateAnimators(double, double, double, double);
    void updateWithSettings();


private:
    QSettings *settings;
    QFrame *debugInfoFrame;
    QWidget *simulationWidget;
    QScatter3DSeries *FLBRSeries;
    QScatter3DSeries *FRBLSeries;
    QScatterDataArray *wheelDataArray;
    QCustom3DItem *FRWheelMesh;
    QCustom3DItem *BLWheelMesh;
    QCustom3DItem *FLWheelMesh;
    QCustom3DItem *BRWheelMesh;
    Q3DScatter *graph;
    QVariantAnimation *FRAnimation;
    QVariantAnimation *BLAnimation;
    QVariantAnimation *FLAnimation;
    QVariantAnimation *BRAnimation;
    QQuaternion FLcurrentRotation;
    QQuaternion BRcurrentRotation;
    QQuaternion FRcurrentRotation;
    QQuaternion BLcurrentRotation;

    int FRmappedDuration;
    int BLmappedDuration;
    int FLmappedDuration;
    int BRmappedDuration;

    void setupFRAnimation();
    void setupBLAnimation();
    void setupFLAnimation();
    void setupBRAnimation();

    void setup3DOjects();
    void setupGraph();

    void updateFRAnimation(double FRSpeed);
    void updateBLAnimation(double BLSpeed);
    void updateFLAnimation(double FLSpeed);
    void updateBRAnimation(double BRSpeed);

};

#endif // SIMULATIONHANDLER_H
