#ifndef SIMULATIONHANDLER_H
#define SIMULATIONHANDLER_H

#include "constants.h"
#include "helper.h"
#include "loggerhandler.h"

#include <math.h>
#include <QDebug>
#include <QKeyEvent>
#include <QLabel>
#include <QObject>
#include <QQuaternion>
#include <QSettings>
#include <QVariantAnimation>
#include <QWidget>

#include "custom3dwindow.h"
#include <Qt3DCore/QAspectEngine>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QSortPolicy>

#include <Qt3DExtras/QExtrudedTextMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DRender/QMesh>

class SimulationHandler : public QObject
{
    Q_OBJECT
public:
    SimulationHandler(LoggerHandler *loggerRef, QSettings *settingsRef);
    QWidget *getWidget();

signals:
    void passKeyboard_WChanged(bool);
    void passKeyboard_SChanged(bool);
    void passKeyboard_AChanged(bool);
    void passKeyboard_DChanged(bool);
    void passKeyboard_QChanged(bool);
    void passKeyboard_EChanged(bool);

public slots:
    void updateWithSettings();
    void updateWheels(double, double, double, double);
    void updateArrow(double, double, double);
    void checkLoaded(Qt3DRender::QMesh::Status status);

private:
    // Variables
    LoggerHandler *logger;
    QSettings *settings;

    Qt3DCore::QEntity *root;
    Qt3DCore::QEntity *FRWheel;
    Qt3DCore::QEntity *BLWheel;
    Qt3DCore::QEntity *FLWheel;
    Qt3DCore::QEntity *BRWheel;
    Qt3DCore::QEntity *arrow;
    Qt3DCore::QEntity *arrowL;
    Qt3DCore::QEntity *arrowR;
    Qt3DCore::QEntity *baseFrame;

    QVariantAnimation *FRAnimation;
    QVariantAnimation *BLAnimation;
    QVariantAnimation *FLAnimation;
    QVariantAnimation *BRAnimation;

    Qt3DCore::QTransform *arrowTransform;
    Qt3DCore::QTransform *arrowLTransform;
    Qt3DCore::QTransform *arrowRTransform;

    Qt3DCore::QTransform *FRWheelTransform;
    Qt3DCore::QTransform *BLWheelTransform;
    Qt3DCore::QTransform *FLWheelTransform;
    Qt3DCore::QTransform *BRWheelTransform;

    Custom3DWindow *view;
    QWidget *simulationWidget;

    int loadedMeshesCount;
    int expectedLoadedMeshes;

    float FLcurrentRotation;
    float BRcurrentRotation;
    float FRcurrentRotation;
    float BLcurrentRotation;

    // Functions
    void setup3DView();
    void setupConnections();
    void setupMeshs();
    void setupFRAnimation();
    void setupBLAnimation();
    void setupFLAnimation();
    void setupBRAnimation();

    void alignMeshs();

    void generateMeshs(Qt3DExtras::QDiffuseSpecularMaterial *gridMaterial,
                       Qt3DExtras::QDiffuseSpecularMaterial *innerBaseMaterial,
                       Qt3DExtras::QDiffuseSpecularMaterial *frameMaterial,
                       Qt3DExtras::QDiffuseSpecularMaterial *arrowMaterial);

    void generateGrid(double size, Qt3DExtras::QDiffuseSpecularMaterial *gridMaterial);
    void generateGridLabels(double size, Qt3DExtras::QDiffuseSpecularMaterial *gridMaterial);
    Qt3DCore::QEntity *generateArrow(bool curved,
                                     bool mirrorCurve,
                                     Qt3DExtras::QDiffuseSpecularMaterial *arrowMaterial);
    Qt3DCore::QEntity *generateFrame(double baseLength,
                                     double baseWidth,
                                     double frameThickness,
                                     Qt3DExtras::QDiffuseSpecularMaterial *frameMaterial,
                                     Qt3DExtras::QDiffuseSpecularMaterial *inBaseMaterial);
    Qt3DCore::QEntity *generateWheel(int partCount,
                                     double wheelWidth,
                                     double wheelDiameter,
                                     double frameThickness,
                                     bool invert,
                                     Qt3DExtras::QDiffuseSpecularMaterial *wheelMaterial);


    void updateFRAnimation(double FRSpeed, int FRmappedDuration);
    void updateBLAnimation(double BLSpeed, int BLmappedDuration);
    void updateFLAnimation(double FLSpeed, int FLmappedDuration);
    void updateBRAnimation(double BRSpeed, int BRmappedDuration);
};

#endif // SIMULATIONHANDLER_H
