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

    // Base
    Qt3DExtras::QPlaneMesh *base = new Qt3DExtras::QPlaneMesh();
    base->setHeight(10.0);
    base->setWidth(10.0);

    Qt3DExtras::QPhongAlphaMaterial *baseMaterial = new Qt3DExtras::QPhongAlphaMaterial();
    baseMaterial->setAmbient(QColor(QRgb(0x7517f8)));
    baseMaterial->setAlpha(0.25);


    Qt3DCore::QEntity *baseEntity = new Qt3DCore::QEntity(rootEntity);
    baseEntity->addComponent(base);
    baseEntity->addComponent(baseMaterial);


    // Frame
    Qt3DExtras::QPhongMaterial *cylMaterial = new Qt3DExtras::QPhongMaterial();
    cylMaterial->setAmbient(QColor(QRgb(0xffffff)));

    Qt3DExtras::QCylinderMesh *cyl1 = new Qt3DExtras::QCylinderMesh();
    cyl1->setLength(SimulationConstants::BASE_WIDTH);
    cyl1->setRadius(SimulationConstants::FRAME_THICKNESS);
    cyl1->setSlices(20);
    cyl1->setRings(2);

    Qt3DExtras::QCylinderMesh *cyl2 = new Qt3DExtras::QCylinderMesh();
    cyl2->setLength(SimulationConstants::BASE_WIDTH);
    cyl2->setRadius(SimulationConstants::FRAME_THICKNESS);
    cyl2->setSlices(20);
    cyl2->setRings(2);

    Qt3DExtras::QCylinderMesh *cyl3 = new Qt3DExtras::QCylinderMesh();
    cyl3->setLength(SimulationConstants::BASE_LENGTH);
    cyl3->setRadius(SimulationConstants::FRAME_THICKNESS);
    cyl3->setSlices(20);
    cyl3->setRings(2);

    Qt3DExtras::QCylinderMesh *cyl4 = new Qt3DExtras::QCylinderMesh();
    cyl4->setLength(SimulationConstants::BASE_LENGTH);
    cyl4->setRadius(SimulationConstants::FRAME_THICKNESS);
    cyl4->setSlices(20);
    cyl4->setRings(2);


    Qt3DCore::QTransform *cyl1Transform = new Qt3DCore::QTransform();
    cyl1Transform->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 90.0f));
    cyl1Transform->setTranslation(QVector3D(0.0f, 1.0f, SimulationConstants::BASE_LENGTH/2));

    Qt3DCore::QTransform *cyl2Transform = new Qt3DCore::QTransform();
    cyl2Transform->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 90.0f));
    cyl2Transform->setTranslation(QVector3D(0.0f, 1.0f, -SimulationConstants::BASE_LENGTH/2));

    Qt3DCore::QTransform *cyl3Transform = new Qt3DCore::QTransform();
    cyl3Transform->setRotation(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 90.0f));
    cyl3Transform->setTranslation(QVector3D(SimulationConstants::BASE_WIDTH/2, 1.0f, 0.0f));

    Qt3DCore::QTransform *cyl4Transform = new Qt3DCore::QTransform();
    cyl4Transform->setRotation(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 90.0f));
    cyl4Transform->setTranslation(QVector3D(-SimulationConstants::BASE_WIDTH/2, 1.0f, 0.0f));


    Qt3DCore::QEntity *cyl1Entity = new Qt3DCore::QEntity(rootEntity);
    cyl1Entity->addComponent(cyl1);
    cyl1Entity->addComponent(cylMaterial);
    cyl1Entity->addComponent(cyl1Transform);

    Qt3DCore::QEntity *cyl2Entity = new Qt3DCore::QEntity(rootEntity);
    cyl2Entity->addComponent(cyl2);
    cyl2Entity->addComponent(cylMaterial);
    cyl2Entity->addComponent(cyl2Transform);

    Qt3DCore::QEntity *cyl3Entity = new Qt3DCore::QEntity(rootEntity);
    cyl3Entity->addComponent(cyl3);
    cyl3Entity->addComponent(cylMaterial);
    cyl3Entity->addComponent(cyl3Transform);

    Qt3DCore::QEntity *cyl4Entity = new Qt3DCore::QEntity(rootEntity);
    cyl4Entity->addComponent(cyl4);
    cyl4Entity->addComponent(cylMaterial);
    cyl4Entity->addComponent(cyl4Transform);

    // Plane 2
    Qt3DExtras::QPlaneMesh *plane2 = new Qt3DExtras::QPlaneMesh();
    plane2->setHeight(SimulationConstants::BASE_LENGTH);
    plane2->setWidth(SimulationConstants::BASE_WIDTH);

    Qt3DExtras::QPhongAlphaMaterial *plane2Material = new Qt3DExtras::QPhongAlphaMaterial();
    plane2Material->setAmbient(QColor(QRgb(0xe223ff)));
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

