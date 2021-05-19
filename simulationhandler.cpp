#include "simulationhandler.h"

//           | y+
//           |
//  x+       |
//  ---------+
//          /
//         /
//        / z+
//

SimulationHandler::SimulationHandler()
{
    setupGraph();

    FLcurrentRotation = FLWheelMesh->rotation();
    BRcurrentRotation = BRWheelMesh->rotation();
    FRcurrentRotation = FRWheelMesh->rotation();
    BLcurrentRotation = BLWheelMesh->rotation();

    setupFRAnimation();
    setupBLAnimation();
    setupFLAnimation();
    setupBRAnimation();

    connect(FRAnimation, &QVariantAnimation::valueChanged, // FR
            this, [this](const QVariant value) {
        FRWheelMesh->setRotation(
                    FRcurrentRotation *
                    QQuaternion::fromAxisAndAngle(1.0f,0.0f,0.0f,
                                                  value.toFloat()));
    });

    connect(BLAnimation, &QVariantAnimation::valueChanged, // BL
            this, [this](const QVariant value) {
        BLWheelMesh->setRotation(
                    BLcurrentRotation *
                    QQuaternion::fromAxisAndAngle(-1.0f,0.0f,0.0f,
                                                  value.toFloat()));
    });

    connect(FLAnimation, &QVariantAnimation::valueChanged, // FL
            this, [this](const QVariant value) {
        FLWheelMesh->setRotation(
                    FLcurrentRotation *
                    QQuaternion::fromAxisAndAngle(-1.0f,0.0f,0.0f,
                                                  -value.toFloat()));
    });

    connect(BRAnimation, &QVariantAnimation::valueChanged, // BR
            this, [this](const QVariant value) {
        BRWheelMesh->setRotation(
                    BRcurrentRotation *
                    QQuaternion::fromAxisAndAngle(1.0f,0.0f,0.0f,
                                                  -value.toFloat()));
    });

    FRAnimation->setLoopCount(0);
    BLAnimation->setLoopCount(0);
    FLAnimation->setLoopCount(0);
    BRAnimation->setLoopCount(0);
}

QWidget* SimulationHandler::getWidget()
{
    return simulationWidget;
}

void SimulationHandler::updateAnimators(double FRSpeed,
                                        double BLSpeed,
                                        double FLSpeed,
                                        double BRSpeed)
{
    //100000 for slow, 1000 for fast
    FRmappedDuration =  linearMap(abs(FRSpeed), 0.0, 1.0,
                                 SimulationConstants::MIN_WHEEL_ROT_DURATION,
                                 SimulationConstants::MAX_WHEEL_ROT_DURATION);
    BLmappedDuration =  linearMap(abs(BLSpeed), 0.0, 1.0,
                                 SimulationConstants::MIN_WHEEL_ROT_DURATION,
                                 SimulationConstants::MAX_WHEEL_ROT_DURATION);
    FLmappedDuration =  linearMap(abs(FLSpeed), 0.0, 1.0,
                                 SimulationConstants::MIN_WHEEL_ROT_DURATION,
                                 SimulationConstants::MAX_WHEEL_ROT_DURATION);
    BRmappedDuration =  linearMap(abs(BRSpeed), 0.0, 1.0,
                                 SimulationConstants::MIN_WHEEL_ROT_DURATION,
                                 SimulationConstants::MAX_WHEEL_ROT_DURATION);

    updateFRAnimation(FRSpeed);
    updateBLAnimation(BLSpeed);
    updateFLAnimation(FLSpeed);
    updateBRAnimation(BRSpeed);
}

void SimulationHandler::updateFRAnimation(double FRSpeed) {
    if(FRSpeed == 0.0) {
        //Capture current rotation and set it as reset
        FRcurrentRotation = FRWheelMesh->rotation();
        FRAnimation->setLoopCount(0);
    } else if (FRSpeed > 0.0) {
        FRAnimation->setDuration(FRmappedDuration);
        FRAnimation->setEndValue(QVariant(360.0)); // Forward
        FRAnimation->setLoopCount(-1);
    } else if (FRSpeed < 0.0) {
        FRAnimation->setDuration(FRmappedDuration);
        FRAnimation->setEndValue(QVariant(-360.0)); // Backward
        FRAnimation->setLoopCount(-1);
    }
}

void SimulationHandler::updateBLAnimation(double BLSpeed) {
    if(BLSpeed == 0.0) {
        //Capture current rotation and set it as reset
        BLcurrentRotation = BLWheelMesh->rotation();
        BLAnimation->setLoopCount(0);
    } else if (BLSpeed > 0.0) {
        BLAnimation->setDuration(BLmappedDuration);
        BLAnimation->setEndValue(QVariant(360.0)); // Forward
        BLAnimation->setLoopCount(-1);
    } else if (BLSpeed < 0.0) {
        BLAnimation->setDuration(BLmappedDuration);
        BLAnimation->setEndValue(QVariant(-360.0)); // Backward
        BLAnimation->setLoopCount(-1);
    }
}
void SimulationHandler::updateFLAnimation(double FLSpeed) {
    if(FLSpeed == 0.0) {
        //Capture current rotation and set it as reset
        FLcurrentRotation = FLWheelMesh->rotation();
        FLAnimation->setLoopCount(0);
    } else if (FLSpeed > 0.0) {
        FLAnimation->setDuration(FLmappedDuration);
        FLAnimation->setEndValue(QVariant(360.0)); // Forward
        FLAnimation->setLoopCount(-1);
    } else if (FLSpeed < 0.0) {
        FLAnimation->setDuration(FLmappedDuration);
        FLAnimation->setEndValue(QVariant(-360.0)); // Backward
        FLAnimation->setLoopCount(-1);
    }
}
void SimulationHandler::updateBRAnimation(double BRSpeed) {
    if(BRSpeed == 0.0) {
        //Capture current rotation and set it as reset
        BRcurrentRotation = BRWheelMesh->rotation();
        BRAnimation->setLoopCount(0);
    } else if (BRSpeed > 0.0) {
        BRAnimation->setDuration(BRmappedDuration);
        BRAnimation->setEndValue(QVariant(360.0)); // Forward
        BRAnimation->setLoopCount(-1);
    } else if (BRSpeed < 0.0) {
        BRAnimation->setDuration(BRmappedDuration);
        BRAnimation->setEndValue(QVariant(-360.0)); // Backward
        BRAnimation->setLoopCount(-1);
    }
}

void SimulationHandler::setupGraph()
{
    graph = new Q3DScatter();
    graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    graph->scene()->activeCamera()->setCameraPosition(-135,22.5,160);
    graph->scene()->activeCamera()->setTarget(QVector3D(0,0,0));

    graph->activeTheme()->setType(Q3DTheme::ThemeUserDefined);
    graph->activeTheme()->setBackgroundEnabled(false);
    graph->activeTheme()->setWindowColor(QColor(5, 5, 15));
    graph->activeTheme()->setFont(QFont("Open Sans", 12));
    graph->activeTheme()->setLabelBackgroundEnabled(false);
    graph->activeTheme()->setLabelTextColor(QColor(QRgb(0xffffff)));
    graph->activeTheme()->setLightColor(QColor(QRgb(0xffffff)));
    graph->activeTheme()->setLightStrength(6.0f);
    graph->activeTheme()->setGridLineColor(QColor(QRgb(0xffffff)));
    graph->activeTheme()->setColorStyle(Q3DTheme::ColorStyleObjectGradient);

    graph->axisX()->setSegmentCount(2);
    graph->axisY()->setSegmentCount(2);
    graph->axisZ()->setSegmentCount(2);
    graph->axisX()->setMax(SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisX()->setMin(-SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisY()->setMax(SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisY()->setMin(0.0);
    graph->axisZ()->setMax(SimulationConstants::MAX_GRAPH_SIZE);
    graph->axisZ()->setMin(-SimulationConstants::MAX_GRAPH_SIZE);

    graph->setSelectionMode(QAbstract3DGraph::SelectionNone);

    setup3DOjects();

    simulationWidget = QWidget::createWindowContainer(graph);
}


void SimulationHandler::setup3DOjects()
{
    QImage color = QImage(2.0, 2.0, QImage::Format_RGB32);
    color.fill(QRgb(0xFFFFFF));

    FRWheelMesh = new
        QCustom3DItem(":/obj/resources/RightMech.obj",
                      QVector3D(SimulationConstants::BASE_WIDTH/2.0f,
                                SimulationConstants::WHEEL_HEIGHT/2.0f,
                                SimulationConstants::BASE_LENGTH/2.0f),
                      QVector3D(0.05f,0.05f,0.05f),
                      QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,180.0f),
                      color);

    BLWheelMesh = new
        QCustom3DItem(":/obj/resources/RightMech.obj",
                      QVector3D(-SimulationConstants::BASE_WIDTH/2.0f,
                                SimulationConstants::WHEEL_HEIGHT/2.0f,
                                -SimulationConstants::BASE_LENGTH/2.0f),
                      QVector3D(0.05f,0.05f,0.05f),
                      QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,0.0f),
                      color);

    FLWheelMesh = new
        QCustom3DItem(":/obj/resources/LeftMech.obj",
                      QVector3D(-SimulationConstants::BASE_WIDTH/2.0f,
                                SimulationConstants::WHEEL_HEIGHT/2.0f,
                                SimulationConstants::BASE_LENGTH/2.0f),
                      QVector3D(0.05f,0.05f,0.05f),
                      QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,180.0f),
                      color);

    BRWheelMesh = new
        QCustom3DItem(":/obj/resources/LeftMech.obj",
                      QVector3D(SimulationConstants::BASE_WIDTH/2.0f,
                                SimulationConstants::WHEEL_HEIGHT/2.0f,
                                -SimulationConstants::BASE_LENGTH/2.0f),
                      QVector3D(0.05f,0.05f,0.05f),
                      QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,0.0f),
                      color);

    QCustom3DItem *BCyl = new
        QCustom3DItem(":/obj/resources/Cylinder.obj",
                      QVector3D(0.0,
                                SimulationConstants::WHEEL_HEIGHT/2.0f,
                                -SimulationConstants::BASE_LENGTH/2.0f),
                      QVector3D(SimulationConstants::FRAME_THICKNESS,
                                SimulationConstants::FRAME_THICKNESS,
                                SimulationConstants::BASE_WIDTH),
                      QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,90.0f),
                      color);

    QCustom3DItem *FCyl = new
        QCustom3DItem(":/obj/resources/Cylinder.obj",
                      QVector3D(0.0,
                                SimulationConstants::WHEEL_HEIGHT/2.0f,
                                SimulationConstants::BASE_LENGTH/2.0f),
                      QVector3D(SimulationConstants::FRAME_THICKNESS,
                                SimulationConstants::FRAME_THICKNESS,
                                SimulationConstants::BASE_WIDTH),
                      QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,90.0f),
                      color);

    QCustom3DItem *LCyl = new
        QCustom3DItem(":/obj/resources/Cylinder.obj",
                      QVector3D(-SimulationConstants::BASE_WIDTH/2.0f,
                                SimulationConstants::WHEEL_HEIGHT/2.0f,
                                0.0),
                      QVector3D(SimulationConstants::FRAME_THICKNESS,
                                SimulationConstants::FRAME_THICKNESS,
                                SimulationConstants::BASE_LENGTH),
                      QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,0.0f),
                      color);
    QCustom3DItem *RCyl = new
        QCustom3DItem(":/obj/resources/Cylinder.obj",
                      QVector3D(SimulationConstants::BASE_WIDTH/2.0f,
                                SimulationConstants::WHEEL_HEIGHT/2.0f,
                                0.0),
                      QVector3D(SimulationConstants::FRAME_THICKNESS,
                                SimulationConstants::FRAME_THICKNESS,
                                SimulationConstants::BASE_LENGTH),
                      QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,0.0f),
                      color);

    QLinearGradient lightPinkBruise_Gradient(QPointF(0, 0), QPointF(1, 0));
    lightPinkBruise_Gradient.setColorAt(0.0, QRgb(0xDD3CFD));
    lightPinkBruise_Gradient.setColorAt(1, QRgb(0xFF6F7A));
    lightPinkBruise_Gradient.setCoordinateMode(QGradient::LogicalMode);

    QLinearGradient darkUltramarine_Gradient(QPointF(0, 0),QPointF(1, 0));
    darkUltramarine_Gradient.setColorAt(0.0, QRgb(0x7517F8));
    darkUltramarine_Gradient.setColorAt(1.0, QRgb(0x02A4FF));
    darkUltramarine_Gradient.setCoordinateMode(QGradient::LogicalMode);

    QScatterDataProxy *FRBLDataProxy = new QScatterDataProxy();
    FRBLDataProxy->addItem(QScatterDataItem(QVector3D( //FR
        SimulationConstants::BASE_WIDTH/2.0f,
        SimulationConstants::WHEEL_HEIGHT/2.0f,
        SimulationConstants::BASE_LENGTH/2.0f)));
    FRBLDataProxy->addItem(QScatterDataItem(QVector3D( //BL
        -SimulationConstants::BASE_WIDTH/2.0f,
        SimulationConstants::WHEEL_HEIGHT/2.0f,
        -SimulationConstants::BASE_LENGTH/2.0f)));
    FRBLSeries = new QScatter3DSeries(FRBLDataProxy);
    FRBLSeries->setItemLabelVisible(false);
    FRBLSeries->setMesh(QAbstract3DSeries::MeshSphere);
    FRBLSeries->setItemSize(0.15f);
    FRBLSeries->setMeshSmooth(true);
    FRBLSeries->setBaseGradient(lightPinkBruise_Gradient);

    QScatterDataProxy *FLBRDataProxy = new QScatterDataProxy();
    FLBRDataProxy->addItem(QScatterDataItem(QVector3D( //FL
        -SimulationConstants::BASE_WIDTH/2.0f,
        SimulationConstants::WHEEL_HEIGHT/2.0f,
        SimulationConstants::BASE_LENGTH/2.0f)));
    FLBRDataProxy->addItem(QScatterDataItem(QVector3D( //BR
        SimulationConstants::BASE_WIDTH/2.0f,
        SimulationConstants::WHEEL_HEIGHT/2.0f,
        -SimulationConstants::BASE_LENGTH/2.0f)));

    FLBRSeries = new QScatter3DSeries(FLBRDataProxy);
    FLBRSeries->setMesh(QAbstract3DSeries::MeshSphere);
    FLBRSeries->setItemSize(0.15f);
    FLBRSeries->setMeshSmooth(true);
    FLBRSeries->setBaseGradient(darkUltramarine_Gradient);
    FLBRSeries->setItemLabelVisible(true);

    graph->addSeries(FRBLSeries);
    graph->addSeries(FLBRSeries);

    graph->addCustomItem(FRWheelMesh);
    graph->addCustomItem(BLWheelMesh);
    graph->addCustomItem(FLWheelMesh);
    graph->addCustomItem(BRWheelMesh);

    graph->addCustomItem(BCyl);
    graph->addCustomItem(FCyl);
    graph->addCustomItem(LCyl);
    graph->addCustomItem(RCyl);
}

void SimulationHandler::setupFRAnimation() {
    FRAnimation = new QVariantAnimation();
    FRAnimation->setStartValue(QVariant(0.0));
    FRAnimation->setEndValue(QVariant(360.0));
    FRAnimation->setDuration(100000);
    FRAnimation->setLoopCount(-1);
    FRAnimation->start();
}

void SimulationHandler::setupBLAnimation() {
    BLAnimation = new QVariantAnimation();
    BLAnimation->setStartValue(QVariant(0.0));
    BLAnimation->setEndValue(QVariant(360.0));
    BLAnimation->setDuration(100000);
    BLAnimation->setLoopCount(-1);
    BLAnimation->start();
}

void SimulationHandler::setupFLAnimation() {
    FLAnimation = new QVariantAnimation();
    FLAnimation->setStartValue(QVariant(0.0));
    FLAnimation->setEndValue(QVariant(360.0));
    FLAnimation->setDuration(100000);
    FLAnimation->setLoopCount(-1);
    FLAnimation->start();
}

void SimulationHandler::setupBRAnimation() {
    BRAnimation = new QVariantAnimation();
    BRAnimation->setStartValue(QVariant(0.0));
    BRAnimation->setEndValue(QVariant(360.0));
    BRAnimation->setDuration(100000);
    BRAnimation->setLoopCount(-1);
    BRAnimation->start();
}


