#include "simulationhandler.h"

// Coordinate system
//           | y+
//           |
//  x+       |
//  ---------+
//          /
//         /
//        / z+
//

// Constructor
SimulationHandler::SimulationHandler(LoggerHandler *loggerRef,
                                     QSettings *settingsRef)
{
    logger = loggerRef;
    settings = settingsRef;

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x05050f)));
    simulationWidget = QWidget::createWindowContainer(view);
    simulationWidget->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);

    // Root Entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DRender::QDirectionalLight *light = new Qt3DRender::QDirectionalLight();
    light->setColor("white");
    light->setIntensity(0);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform();
    lightTransform->setTranslation(cameraEntity->position());

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    lightEntity->addComponent(light);
    lightEntity->addComponent(lightTransform);

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Plane
    Qt3DExtras::QPlaneMesh *plane = new Qt3DExtras::QPlaneMesh();
    plane->setHeight(10.0);
    plane->setWidth(10.0);

    Qt3DExtras::QPhongMaterial *planeMaterial = new Qt3DExtras::QPhongMaterial();
    planeMaterial->setAmbient(QColor(QRgb(0xa6d8ff)));


    Qt3DCore::QEntity *planeEntity = new Qt3DCore::QEntity(rootEntity);
    planeEntity->addComponent(plane);
    planeEntity->addComponent(planeMaterial);


    // Cyl
    Qt3DExtras::QCylinderMesh *cyl = new Qt3DExtras::QCylinderMesh();
    cyl->setLength(2);
    cyl->setRadius(1);
    cyl->setSlices(10);
    cyl->setRings(5);

    Qt3DExtras::QPhongMaterial *cylMaterial = new Qt3DExtras::QPhongMaterial();
    cylMaterial->setAmbient(QColor(QRgb(0xffa6a6)));
    //cylMaterial->setShininess(0);


    Qt3DCore::QTransform *cylTransform = new Qt3DCore::QTransform();
    cylTransform->setScale(0.5f);
    cylTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
    cylTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DCore::QEntity *cylEntity = new Qt3DCore::QEntity(rootEntity);
    cylEntity->addComponent(cyl);
    cylEntity->addComponent(cylMaterial);
    cylEntity->addComponent(cylTransform);

    // Plane 2
    Qt3DExtras::QPlaneMesh *plane2 = new Qt3DExtras::QPlaneMesh();
    plane2->setHeight(2.0);
    plane2->setWidth(2.0);

    Qt3DExtras::QPhongAlphaMaterial *plane2Material = new Qt3DExtras::QPhongAlphaMaterial();
    plane2Material->setAmbient(QColor(QRgb(0xff0000)));
    plane2Material->setAlpha(0.5);

    Qt3DCore::QTransform *plane2Transform = new Qt3DCore::QTransform();
    plane2Transform->setTranslation(QVector3D(0.0f, 1.0f, 0.0f));


    Qt3DCore::QEntity *plane2Entity = new Qt3DCore::QEntity(rootEntity);
    plane2Entity->addComponent(plane2);
    plane2Entity->addComponent(plane2Material);
    plane2Entity->addComponent(plane2Transform);

    view->setRootEntity(rootEntity);




}

void SimulationHandler::updateWithSettings()
{
    qDebug() << "simulation handler update";

    if (!settings->value(SettingsConstants::RENDER_VIEW_DEBUG_EN, SettingsConstants::D_RENDER_VIEW_DEBUG_EN).toBool() &&
        !settings->value(SettingsConstants::RENDER_VIEW_COUNT_EN, SettingsConstants::D_RENDER_VIEW_COUNT_EN).toBool()) {
        emit setDebugFrameVisible(false);
    } else {
        emit setDebugFrameVisible(true);
    }

    if (settings->value(SettingsConstants::RENDER_VIEW_DEBUG_EN, SettingsConstants::D_RENDER_VIEW_DEBUG_EN).toBool() &&
        settings->value(SettingsConstants::RENDER_VIEW_COUNT_EN, SettingsConstants::D_RENDER_VIEW_COUNT_EN).toBool()) {
        emit setDebugSepVisible(true);
    } else {
        emit setDebugSepVisible(false);
    }

    emit setDebugDataVisible(settings->value(SettingsConstants::RENDER_VIEW_DEBUG_EN, SettingsConstants::D_RENDER_VIEW_DEBUG_EN).toBool());
    emit fpsDataVisible(settings->value(SettingsConstants::RENDER_VIEW_COUNT_EN, SettingsConstants::D_RENDER_VIEW_COUNT_EN).toBool());
}
// Getters
QWidget* SimulationHandler::getWidget()
{
    return simulationWidget;
}

