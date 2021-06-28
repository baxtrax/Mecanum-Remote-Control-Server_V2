#ifndef SIMULATIONHANDLER_H
#define SIMULATIONHANDLER_H

#include "constants.h"
#include "helper.h"
#include "loggerhandler.h"

#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QVariantAnimation>
#include <QLabel>
#include <QSettings>

#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPhongAlphaMaterial>


class SimulationHandler : public QObject
{
    Q_OBJECT
public:
    SimulationHandler(LoggerHandler *loggerRef, QSettings *settingsRef);
    QWidget* getWidget();

public slots:
    void updateWithSettings();

signals:
    void updateDebugFPS(double);
    void setDebugFrameVisible(bool);
    void setDebugSepVisible(bool);
    void setDebugDataVisible(bool);
    void fpsDataVisible(bool);

private:

    LoggerHandler *logger;
    QSettings *settings;
    QWidget *simulationWidget;
};

#endif // SIMULATIONHANDLER_H
