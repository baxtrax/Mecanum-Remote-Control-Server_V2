#ifndef SIMULATIONHANDLER_H
#define SIMULATIONHANDLER_H

#include <QObject>
#include <QDebug>
#include <QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>

class SimulationHandler
{
public:
    SimulationHandler();
    QWidget* getWidget();
private:
    QWidget *simulationWidget;
};

#endif // SIMULATIONHANDLER_H
