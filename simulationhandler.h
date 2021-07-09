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
#include <Qt3DRender/QClearBuffers>
#include <Qt3DRender/QViewport>
#include <Qt3DRender/QLayerFilter>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QRenderSurfaceSelector>
#include <Qt3DRender/QSortPolicy>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DRender/QAbstractTexture>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QText2DEntity>
#include <Qt3DExtras/QExtrudedTextMesh>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DRender/QLayer>



class SimulationHandler : public QObject
{
    Q_OBJECT
public:
    SimulationHandler(LoggerHandler *loggerRef, QSettings *settingsRef);
    QWidget* getWidget();

public slots:
    void updateWithSettings();
    void updateWheels(double,double,double,double);
    void updateArrow(double, double, double);
    void checkLoaded(Qt3DRender::QMesh::Status status);

private:

    LoggerHandler *logger;
    QSettings *settings;
    Qt3DCore::QEntity *root;
    Qt3DCore::QEntity *FRWheel;
    Qt3DCore::QEntity *BLWheel;
    Qt3DCore::QEntity *FLWheel;
    Qt3DCore::QEntity *BRWheel;

    Qt3DCore::QEntity *arrow;
    Qt3DCore::QTransform *arrowTransform;

    Qt3DCore::QEntity *arrowL;
    Qt3DCore::QTransform *arrowLTransform;

    Qt3DCore::QEntity *arrowR;
    Qt3DCore::QTransform *arrowRTransform;

    Qt3DCore::QEntity *baseFrame;
    Qt3DExtras::Qt3DWindow *view;
    Qt3DRender::QLayer *transparentLayer;
    Qt3DRender::QLayer *opaqueLayer;
    QWidget *simulationWidget;

    int loadedMeshesCount;
    int expectedLoadedMeshes;

    void setup3DView();

    Qt3DCore::QEntity* generateArrow(bool curved,
                                     bool mirrorCurve,
                                     Qt3DExtras::QDiffuseSpecularMaterial *arrowMaterial);
    void generateGrid(double size,
                      Qt3DExtras::QDiffuseSpecularMaterial *gridMaterial);
    void generateGridLabels(double size,
                            Qt3DExtras::QDiffuseSpecularMaterial *gridMaterial);
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
