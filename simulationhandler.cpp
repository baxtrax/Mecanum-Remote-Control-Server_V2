#include "simulationhandler.h"

SimulationHandler::SimulationHandler()
{
    //3D Stuffs
    Qt3DCore::QEntity *scene = new Qt3DCore::QEntity();
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(scene);

    Qt3DCore::QEntity *cylinderEntity = new Qt3DCore::QEntity(scene);
    Qt3DExtras::QCylinderMesh *cylinderMesh = new Qt3DExtras::QCylinderMesh;
    cylinderMesh->setRadius(5);
    cylinderMesh->setLength(10);

    cylinderMesh->setRings(4);
    cylinderMesh->setSlices(10);

    //Transform cylinder
    Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform;
    cylinderTransform->setScale3D(QVector3D(1, 1, 1)); //Keep scaled at typical for now
    cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 45.0f));

    //Add configurations to cylinder
    cylinderEntity->addComponent(cylinderMesh);
    cylinderEntity->addComponent(cylinderTransform);
    cylinderEntity->addComponent(material);

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    Qt3DExtras::QOrbitCameraController *cameraController = new Qt3DExtras::QOrbitCameraController(scene);
    cameraController->setLinearSpeed(50.0f);
    cameraController->setLookSpeed(180.0f);
    cameraController->setCamera(camera);

    view->setRootEntity(scene);
    //view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x191932)));
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x05050f)));

    simulationWidget = QWidget::createWindowContainer(view);
}

QWidget* SimulationHandler::getWidget()
{
    return simulationWidget;
}
