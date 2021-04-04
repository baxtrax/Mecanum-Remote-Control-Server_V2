#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartView>

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

#include "gamepadhandler.h"
#include "inputhandler.h"
#include "kinematicshandler.h"
#include "outputhandler.h"
#include "loggerhandler.h"

GamepadHandler *gamepadHandler;
InputHandler *inputHandler;
KinematicsHandler *kinematicsHandler;
OutputHandler *outputHandler;
LoggerHandler *loggerHandler;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loggerHandler = new LoggerHandler(ui->loggerTextEdit);
    gamepadHandler = new GamepadHandler();
    inputHandler = new InputHandler(ui->axisX_topVSlider,
                                    ui->axisX_botVSlider,
                                    ui->axisY_topVSlider,
                                    ui->axisY_botVSlider,
                                    ui->axisZ_topVSlider,
                                    ui->axisZ_botVSlider);
    kinematicsHandler = new KinematicsHandler();
    outputHandler = new OutputHandler(ui->FRBL_topVSlider,
                                      ui->FRBL_botVSlider,
                                      ui->FLBR_topVSlider,
                                      ui->FLBR_botVSlider,
                                      ui->kinematicsGraphView);

    configureConnections();
    loggerHandler->clear();
    loggerHandler->write(LoggerConstants::DEBUG, "test");
    loggerHandler->write(LoggerConstants::INFO, "test");
    loggerHandler->write(LoggerConstants::WARNING, "test");
    loggerHandler->write(LoggerConstants::ERR, "test");
    loggerHandler->write(LoggerConstants::FATAL, "test");
    loggerHandler->write("test");

    //Initially start on home page.
    ui->home_toolButton->setCheckable(true);
    ui->home_toolButton->setDown(true);
    //ui->home_toolButton->setDisabled(true);
    //TODO scroll bar a little too thicc, fix its size alittle
    ui->loggerTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->loggerTextEdit->setVerticalScrollBar(ui->loggerVerticalScrollbar);

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

    QWidget *container = QWidget::createWindowContainer(view);
    ui->simulation_Frame->layout()->addWidget(container);
}


/**
 * @brief Is called when any key is pressed down and emits signals for each
 * key pressed.
 * @param A key pressed event
 */
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat() == false)
    {
        switch(event->key())
        {
        case Qt::Key_W:
            emit keyboard_WChanged(true);
            //qDebug() << "Keyboard W" << true;
            break;
        case Qt::Key_S:
            emit keyboard_SChanged(true);
            //qDebug() << "Keyboard S" << true;
            break;
        case Qt::Key_A:
            emit keyboard_AChanged(true);
            //qDebug() << "Keyboard A" << true;
            break;
        case Qt::Key_D:
            emit keyboard_DChanged(true);
            //qDebug() << "Keyboard D" << true;
            break;
        case Qt::Key_Q:
            emit keyboard_QChanged(true);
            //qDebug() << "Keyboard Q" << true;
            break;
        case Qt::Key_E:
            emit keyboard_EChanged(true);
            //qDebug() << "Keyboard E" << true;
            break;
        }
    }
}


/**
 * @brief Is called when any key is released and emits signals for each
 * key pressed.
 * @param A key release event
 */
void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat() == false)
    {
        switch(event->key())
        {
        case Qt::Key_W:
            emit keyboard_WChanged(false);
            //qDebug() << "Keyboard W" << false;
            break;
        case Qt::Key_S:
            emit keyboard_SChanged(false);
            //qDebug() << "Keyboard S" << false;
            break;
        case Qt::Key_A:
            emit keyboard_AChanged(false);
            //qDebug() << "Keyboard A" << false;
            break;
        case Qt::Key_D:
            emit keyboard_DChanged(false);
            //qDebug() << "Keyboard D" << false;
            break;
        case Qt::Key_Q:
            emit keyboard_QChanged(false);
            //qDebug() << "Keyboard Q" << false;
            break;
        case Qt::Key_E:
            emit keyboard_EChanged(false);
            //qDebug() << "Keyboard E" << true;
            break;
        }
    }
}

//TODO connect inputHandler inputsChanged tp kinematicsHandler updateSpeed
//update speeds emit speedsChanged(fl/br, fr/bl)

/**
 * @brief Configures connections of slots and signals of a MainWindow object
 */
void MainWindow::configureConnections()
{
    connect(gamepadHandler,
            SIGNAL(gamepad_axisLeftXChanged(double)),
            inputHandler,
            SLOT(gamepad_axisLeftXSetter(double)));
    connect(gamepadHandler,
            SIGNAL(gamepad_axisLeftYChanged(double)),
            inputHandler,
            SLOT(gamepad_axisLeftYSetter(double)));
    connect(gamepadHandler,
            SIGNAL(gamepad_axisRightXChanged(double)),
            inputHandler,
            SLOT(gamepad_axisRightXSetter(double)));
    connect(this,
            SIGNAL(keyboard_WChanged(bool)),
            inputHandler,
            SLOT(keyboard_WSetter(bool)));
    connect(this,
            SIGNAL(keyboard_SChanged(bool)),
            inputHandler,
            SLOT(keyboard_SSetter(bool)));
    connect(this,
            SIGNAL(keyboard_AChanged(bool)),
            inputHandler,
            SLOT(keyboard_ASetter(bool)));
    connect(this,
            SIGNAL(keyboard_DChanged(bool)),
            inputHandler,
            SLOT(keyboard_DSetter(bool)));
    connect(this,
            SIGNAL(keyboard_QChanged(bool)),
            inputHandler,
            SLOT(keyboard_QSetter(bool)));
    connect(this,
            SIGNAL(keyboard_EChanged(bool)),
            inputHandler,
            SLOT(keyboard_ESetter(bool)));
    connect(inputHandler,
            SIGNAL(inputsChanged(double, double, double)),
            kinematicsHandler,
            SLOT(updateSpeeds(double, double, double)));
    connect(kinematicsHandler,
            SIGNAL(speedsChanged(double, double)),
            outputHandler,
            SLOT(updateSliders(double, double)));
    connect(kinematicsHandler,
            SIGNAL(functionChanged(double, double, double, double)),
            outputHandler,
            SLOT(updateChart(double, double, double, double)));
}

//MainWindow deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}

