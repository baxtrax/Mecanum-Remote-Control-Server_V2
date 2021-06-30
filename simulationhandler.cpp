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
    root = new Qt3DCore::QEntity();

    view = new Qt3DExtras::Qt3DWindow();
//    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x05050f)));
    simulationWidget = QWidget::createWindowContainer(view);
    simulationWidget->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);

    setup3DView();


    // Materials
    Qt3DExtras::QDiffuseSpecularMaterial *gridMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
    gridMaterial->setAmbient(QColor(255,255,255));
    gridMaterial->setAlphaBlendingEnabled(true);
    gridMaterial->setDiffuse(QColor(255,255,255,128));

    Qt3DExtras::QDiffuseSpecularMaterial *innerBaseMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
    innerBaseMaterial->setAmbient(QColor(226,35,255));
    innerBaseMaterial->setAlphaBlendingEnabled(true);
    innerBaseMaterial->setDiffuse(QColor(226,35,255,128));

    Qt3DExtras::QDiffuseSpecularMaterial *frameMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
    frameMaterial->setAmbient(QColor(255,255,255));
    frameMaterial->setDiffuse(QColor(255,255,255));

    Qt3DExtras::QDiffuseSpecularMaterial *FRBLMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
    FRBLMaterial->setAmbient(QColor(232,77,209));
    FRBLMaterial->setDiffuse(QColor(232,77,209));

    Qt3DExtras::QDiffuseSpecularMaterial *FLBRMaterial = new Qt3DExtras::QDiffuseSpecularMaterial();
    FLBRMaterial->setAmbient(QColor(79,70,250));
    FLBRMaterial->setDiffuse(QColor(79,70,250));


    FRWheel = generateWheel(9,
                            SimulationConstants::WHEEL_WIDTH,
                            SimulationConstants::WHEEL_DIAMETER,
                            SimulationConstants::FRAME_THICKNESS,
                            SimulationConstants::WHEEL_RIGHT,
                            frameMaterial);

    BLWheel = generateWheel(9,
                            SimulationConstants::WHEEL_WIDTH,
                            SimulationConstants::WHEEL_DIAMETER,
                            SimulationConstants::FRAME_THICKNESS,
                            SimulationConstants::WHEEL_RIGHT,
                            frameMaterial);

    FLWheel = generateWheel(9,
                            SimulationConstants::WHEEL_WIDTH,
                            SimulationConstants::WHEEL_DIAMETER,
                            SimulationConstants::FRAME_THICKNESS,
                            SimulationConstants::WHEEL_LEFT,
                            frameMaterial);

    BRWheel = generateWheel(9,
                            SimulationConstants::WHEEL_WIDTH,
                            SimulationConstants::WHEEL_DIAMETER,
                            SimulationConstants::FRAME_THICKNESS,
                            SimulationConstants::WHEEL_LEFT,
                            frameMaterial);

    baseFrame = generateFrame(SimulationConstants::INBASE_LENGTH,
                              SimulationConstants::INBASE_WIDTH,
                              SimulationConstants::FRAME_THICKNESS,
                              frameMaterial,
                              innerBaseMaterial);

    generateGrid(SimulationConstants::GRID_WIDTH,
                 gridMaterial);
    Qt3DCore::QTransform *baseTransform = new Qt3DCore::QTransform();
    baseTransform->setTranslation(QVector3D(0.0f,
                                            SimulationConstants::WHEEL_DIAMETER/2 + SimulationConstants::FRAME_THICKNESS,
                                            0.0f));
    baseFrame->addComponent(baseTransform);

    Qt3DCore::QTransform *FRTransform = new Qt3DCore::QTransform();
    FRTransform->setTranslation(QVector3D(-SimulationConstants::INBASE_WIDTH/2 - SimulationConstants::WHEEL_WIDTH/2,
                                          SimulationConstants::WHEEL_DIAMETER/2 + SimulationConstants::FRAME_THICKNESS,
                                          SimulationConstants::INBASE_LENGTH/2));
    FRWheel->addComponent(FRTransform);

    Qt3DCore::QTransform *BLTransform = new Qt3DCore::QTransform();
    BLTransform->setTranslation(QVector3D(SimulationConstants::INBASE_WIDTH/2 + SimulationConstants::WHEEL_WIDTH/2,
                                          SimulationConstants::WHEEL_DIAMETER/2 + SimulationConstants::FRAME_THICKNESS,
                                          -SimulationConstants::INBASE_LENGTH/2));
    BLWheel->addComponent(BLTransform);

    Qt3DCore::QTransform *FLTransform = new Qt3DCore::QTransform();
    FLTransform->setTranslation(QVector3D(SimulationConstants::INBASE_WIDTH/2 + SimulationConstants::WHEEL_WIDTH/2,
                                          SimulationConstants::WHEEL_DIAMETER/2 + SimulationConstants::FRAME_THICKNESS,
                                          SimulationConstants::INBASE_LENGTH/2));
    FLWheel->addComponent(FLTransform);

    Qt3DCore::QTransform *BRTransform = new Qt3DCore::QTransform();
    BRTransform->setTranslation(QVector3D(-SimulationConstants::INBASE_WIDTH/2 - SimulationConstants::WHEEL_WIDTH/2,
                                          SimulationConstants::WHEEL_DIAMETER/2 + SimulationConstants::FRAME_THICKNESS,
                                          -SimulationConstants::INBASE_LENGTH/2));
    BRWheel->addComponent(BRTransform);


    view->setRootEntity(root);




}

//Grab keyboard and send it over to the input handler
void SimulationHandler::setup3DView() {
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x05050f)));
    view->defaultFrameGraph()->setFrustumCullingEnabled(true);

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(-10.0f, 7.0f, 10.0f));
    cameraEntity->setUpVector(QVector3D(0, 1.0f, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    // Disable light
    Qt3DRender::QDirectionalLight *light = new Qt3DRender::QDirectionalLight();
    light->setColor("white");
    light->setIntensity(0);

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(root);
    lightEntity->addComponent(light);

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(root);
    camController->setCamera(cameraEntity);
}


void SimulationHandler::generateGrid(double width,
                                     Qt3DExtras::QDiffuseSpecularMaterial *gridMaterial) {

    Qt3DCore::QEntity *baseEntity = new Qt3DCore::QEntity(root);

    // Meshs
    Qt3DExtras::QPlaneMesh **gridLines = new Qt3DExtras::QPlaneMesh*[10];
    Qt3DCore::QTransform **lineTransform = new Qt3DCore::QTransform*[10];
    Qt3DCore::QEntity **lineEntity = new Qt3DCore::QEntity*[10];

    for (int i=0; i < 10; i++) {
        gridLines[i] = new Qt3DExtras::QPlaneMesh();
        gridLines[i]->setHeight(SimulationConstants::GRID_THICKNESS);
        gridLines[i]->setWidth(width+SimulationConstants::GRID_PAD);
    }

    for (int i=0; i < 10; i++) {
        lineTransform[i] = new Qt3DCore::QTransform();
    }

    // Transforms
    //Vertical
    lineTransform[0]->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 90.0f));
    lineTransform[1]->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 90.0f));
    lineTransform[1]->setTranslation(QVector3D(width/2, 0.0f, 0.0f));
    lineTransform[2]->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 90.0f));
    lineTransform[2]->setTranslation(QVector3D(-width/2, 0.0f, 0.0f));
    lineTransform[3]->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 90.0f));
    lineTransform[3]->setTranslation(QVector3D(-width/2+0.2, 0.0f, 0.0f));
    lineTransform[4]->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 90.0f));
    lineTransform[4]->setTranslation(QVector3D(width/2-0.2, 0.0f, 0.0f));

    //Horizontal
    lineTransform[5]->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
    lineTransform[6]->setTranslation(QVector3D(0.0f, 0.0f, width/2));
    lineTransform[7]->setTranslation(QVector3D(0.0f, 0.0f, -width/2));
    lineTransform[8]->setTranslation(QVector3D(0.0f, 0.0f, width/2-0.2));
    lineTransform[9]->setTranslation(QVector3D(0.0f, 0.0f, -width/2+0.2));

    //Entities
    for (int i=0; i < 10; i++) {
        lineEntity[i] = new Qt3DCore::QEntity(baseEntity);
        lineEntity[i]->addComponent(gridLines[i]);
        lineEntity[i]->addComponent(lineTransform[i]);
        lineEntity[i]->addComponent(gridMaterial);
    }
}


Qt3DCore::QEntity* SimulationHandler::generateFrame(double baseLength,
                                                    double baseWidth,
                                                    double frameThickness,
                                                    Qt3DExtras::QDiffuseSpecularMaterial *frameMaterial,
                                                    Qt3DExtras::QDiffuseSpecularMaterial *inBaseMaterial) {
    Qt3DCore::QEntity *frameEntity = new Qt3DCore::QEntity(root);

    // Frame
    // Meshs
    Qt3DExtras::QCylinderMesh *cyl1 = new Qt3DExtras::QCylinderMesh();
    cyl1->setLength(baseWidth);
    cyl1->setRadius(frameThickness);
    cyl1->setSlices(20);
    cyl1->setRings(2);

    Qt3DExtras::QCylinderMesh *cyl2 = new Qt3DExtras::QCylinderMesh();
    cyl2->setLength(baseWidth);
    cyl2->setRadius(frameThickness);
    cyl2->setSlices(20);
    cyl2->setRings(2);

    Qt3DExtras::QCylinderMesh *cyl3 = new Qt3DExtras::QCylinderMesh();
    cyl3->setLength(baseLength);
    cyl3->setRadius(frameThickness);
    cyl3->setSlices(20);
    cyl3->setRings(2);

    Qt3DExtras::QCylinderMesh *cyl4 = new Qt3DExtras::QCylinderMesh();
    cyl4->setLength(baseLength);
    cyl4->setRadius(frameThickness);
    cyl4->setSlices(20);
    cyl4->setRings(2);

    Qt3DExtras::QSphereMesh *sph1 = new Qt3DExtras::QSphereMesh();
    sph1->setRadius(frameThickness*2);
    sph1->generateTangents();

    Qt3DExtras::QSphereMesh *sph2 = new Qt3DExtras::QSphereMesh();
    sph2->setRadius(frameThickness*2);
    sph2->generateTangents();

    Qt3DExtras::QSphereMesh *sph3 = new Qt3DExtras::QSphereMesh();
    sph3->setRadius(frameThickness*2);
    sph3->generateTangents();

    Qt3DExtras::QSphereMesh *sph4 = new Qt3DExtras::QSphereMesh();
    sph4->setRadius(frameThickness*2);
    sph4->generateTangents();

    // Transforms
    Qt3DCore::QTransform *cyl1Transform = new Qt3DCore::QTransform();
    cyl1Transform->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 90.0f));
    cyl1Transform->setTranslation(QVector3D(0.0f, 0.0f, baseLength/2));

    Qt3DCore::QTransform *cyl2Transform = new Qt3DCore::QTransform();
    cyl2Transform->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 90.0f));
    cyl2Transform->setTranslation(QVector3D(0.0f, 0.0f, -baseLength/2));

    Qt3DCore::QTransform *cyl3Transform = new Qt3DCore::QTransform();
    cyl3Transform->setRotation(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 90.0f));
    cyl3Transform->setTranslation(QVector3D(baseWidth/2, 0.0f, 0.0f));

    Qt3DCore::QTransform *cyl4Transform = new Qt3DCore::QTransform();
    cyl4Transform->setRotation(QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 90.0f));
    cyl4Transform->setTranslation(QVector3D(-baseWidth/2, 0.0f, 0.0f));

    Qt3DCore::QTransform *sph1Transform = new Qt3DCore::QTransform();
    sph1Transform->setTranslation(QVector3D(baseWidth/2, 0.0f, baseLength/2));

    Qt3DCore::QTransform *sph2Transform = new Qt3DCore::QTransform();
    sph2Transform->setTranslation(QVector3D(-baseWidth/2, 0.0f, baseLength/2));

    Qt3DCore::QTransform *sph3Transform = new Qt3DCore::QTransform();
    sph3Transform->setTranslation(QVector3D(baseWidth/2, 0.0f, -baseLength/2));

    Qt3DCore::QTransform *sph4Transform = new Qt3DCore::QTransform();
    sph4Transform->setTranslation(QVector3D(-baseWidth/2, 0.0f, -baseLength/2));

    // Entities
    Qt3DCore::QEntity *cyl1Entity = new Qt3DCore::QEntity(frameEntity);
    cyl1Entity->addComponent(cyl1);
    cyl1Entity->addComponent(frameMaterial);
    cyl1Entity->addComponent(cyl1Transform);

    Qt3DCore::QEntity *cyl2Entity = new Qt3DCore::QEntity(frameEntity);
    cyl2Entity->addComponent(cyl2);
    cyl2Entity->addComponent(frameMaterial);
    cyl2Entity->addComponent(cyl2Transform);

    Qt3DCore::QEntity *cyl3Entity = new Qt3DCore::QEntity(frameEntity);
    cyl3Entity->addComponent(cyl3);
    cyl3Entity->addComponent(frameMaterial);
    cyl3Entity->addComponent(cyl3Transform);

    Qt3DCore::QEntity *cyl4Entity = new Qt3DCore::QEntity(frameEntity);
    cyl4Entity->addComponent(cyl4);
    cyl4Entity->addComponent(frameMaterial);
    cyl4Entity->addComponent(cyl4Transform);

    Qt3DCore::QEntity *sph1Entity = new Qt3DCore::QEntity(frameEntity);
    sph1Entity->addComponent(sph1);
    sph1Entity->addComponent(frameMaterial);
    sph1Entity->addComponent(sph1Transform);

    Qt3DCore::QEntity *sph2Entity = new Qt3DCore::QEntity(frameEntity);
    sph2Entity->addComponent(sph2);
    sph2Entity->addComponent(frameMaterial);
    sph2Entity->addComponent(sph2Transform);

    Qt3DCore::QEntity *sph3Entity = new Qt3DCore::QEntity(frameEntity);
    sph3Entity->addComponent(sph3);
    sph3Entity->addComponent(frameMaterial);
    sph3Entity->addComponent(sph3Transform);

    Qt3DCore::QEntity *sph4Entity = new Qt3DCore::QEntity(frameEntity);
    sph4Entity->addComponent(sph4);
    sph4Entity->addComponent(frameMaterial);
    sph4Entity->addComponent(sph4Transform);

    // Inner Base

    // Meshs
    Qt3DExtras::QPlaneMesh *innerBasePlane = new Qt3DExtras::QPlaneMesh();
    innerBasePlane->setHeight(baseLength);
    innerBasePlane->setWidth(baseWidth);

    // Entities
    Qt3DCore::QEntity *innerBaseEntity = new Qt3DCore::QEntity(frameEntity);
    innerBaseEntity->addComponent(innerBasePlane);
    innerBaseEntity->addComponent(inBaseMaterial);
    return frameEntity;
}

Qt3DCore::QEntity* SimulationHandler::generateWheel(int partCount,
                                                    double wheelWidth,
                                                    double wheelDiameter,
                                                    double frameThickness,
                                                    bool invert,
                                                    Qt3DExtras::QDiffuseSpecularMaterial *wheelMaterial) {
    Qt3DCore::QEntity *wEntity = new Qt3DCore::QEntity(root);

    //Double pointer setup
    Qt3DCore::QEntity **parts = new Qt3DCore::QEntity*[partCount];

    double angleBetween = 360.0/(double)partCount;
    double currentAngle = 0.0;

    //For each part
    for (int i=0; i<partCount; i++) {
        //LW 1
        //lw1Entity
        parts[i] = new Qt3DCore::QEntity(wEntity);
        currentAngle += angleBetween;

        // Meshs
        Qt3DExtras::QCylinderMesh *wCyl = new Qt3DExtras::QCylinderMesh();
        wCyl->setLength(wheelWidth);
        wCyl->setRadius(frameThickness);
        wCyl->setSlices(20);
        wCyl->setRings(2);

        Qt3DExtras::QSphereMesh *wSph1 = new Qt3DExtras::QSphereMesh();
        wSph1->setRadius(frameThickness*2);
        wSph1->setSlices(10);
        wSph1->setRings(10);

        Qt3DExtras::QSphereMesh *wSph2 = new Qt3DExtras::QSphereMesh();
        wSph2->setRadius(frameThickness*2);
        wSph2->setSlices(10);
        wSph2->setRings(10);

        // Transforms
        Qt3DCore::QTransform *wCylTransform = new Qt3DCore::QTransform();
        wCylTransform->setRotation(QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 90.0f));

        Qt3DCore::QTransform *wSph1Transform = new Qt3DCore::QTransform();
        wSph1Transform->setTranslation(QVector3D(wheelWidth/2, 0.0f, 0.0f));

        Qt3DCore::QTransform *wSph2Transform = new Qt3DCore::QTransform();
        wSph2Transform->setTranslation(QVector3D(-wheelWidth/2, 0.0f, 0.0f));

        // Entities
        Qt3DCore::QEntity *wCylEntity = new Qt3DCore::QEntity(parts[i]);
        wCylEntity->addComponent(wCyl);
        wCylEntity->addComponent(wCylTransform);
        wCylEntity->addComponent(wheelMaterial);

        Qt3DCore::QEntity *wSph1Entity = new Qt3DCore::QEntity(parts[i]);
        wSph1Entity->addComponent(wSph1);
        wSph1Entity->addComponent(wSph1Transform);
        wSph1Entity->addComponent(wheelMaterial);

        Qt3DCore::QEntity *wSph2Entity = new Qt3DCore::QEntity(parts[i]);
        wSph2Entity->addComponent(wSph2);
        wSph2Entity->addComponent(wSph2Transform);
        wSph2Entity->addComponent(wheelMaterial);

        // Rotating segments to 45 degrees around the axis of a vector pointing
        // to the center of the wheel.
        Qt3DCore::QTransform *partsTransform = new Qt3DCore::QTransform();
        double height = sin(currentAngle*MathConstants::PI/180.0);
        double width = cos(currentAngle*MathConstants::PI/180.0);
        if(invert) {
            partsTransform->setRotation(QQuaternion::fromAxisAndAngle(0.0,height,width,-45.0));
        } else {
            partsTransform->setRotation(QQuaternion::fromAxisAndAngle(0.0,height,width,45.0));
        }
        partsTransform->setTranslation(QVector3D(0, height*wheelDiameter/2, width*wheelDiameter/2));
        parts[i]->addComponent(partsTransform);
    }
    return wEntity;

}

void SimulationHandler::updateWithSettings()
{
    qDebug() << "simulation handler update";
    view->defaultFrameGraph()->
        setShowDebugOverlay(
            settings->value(SettingsConstants::RENDER_VIEW_DEBUG_EN,
                            SettingsConstants::D_RENDER_VIEW_DEBUG_EN).toBool());
}


// Getters
QWidget* SimulationHandler::getWidget()
{
    return simulationWidget;
}

