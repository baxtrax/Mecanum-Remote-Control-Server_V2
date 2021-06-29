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
#include <math.h>

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
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QDiffuseSpecularMaterial>


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

    void wheelsGenerated();

private:

    LoggerHandler *logger;
    QSettings *settings;
    Qt3DCore::QEntity *root;
    Qt3DCore::QEntity *FRWheel;
    Qt3DCore::QEntity *BLWheel;
    Qt3DCore::QEntity *FLWheel;
    Qt3DCore::QEntity *BRWheel;
    Qt3DCore::QEntity *baseFrame;
    QWidget *simulationWidget;

    void setup3DView(Qt3DExtras::Qt3DWindow *view);

    void generateBase(double width,
                             double height,
                             Qt3DExtras::QDiffuseSpecularMaterial *planeMaterial);
    Qt3DCore::QEntity* generateFrame(double baseLength,
                                     double baseWidth,
                                     double frameThickness,
                                     Qt3DExtras::QDiffuseSpecularMaterial *frameMaterial,
                                     Qt3DExtras::QDiffuseSpecularMaterial *inBaseMaterial);
    Qt3DCore::QEntity* generateWheel(int partCount,
                                     double wheelWidth,
                                     double wheelDiameter,
                                     double frameThickness,
                                     bool invert,
                                     Qt3DExtras::QDiffuseSpecularMaterial *wheelMaterial);

};

#endif // SIMULATIONHANDLER_H
