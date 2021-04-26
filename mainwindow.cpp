#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartView>

#include "gamepadhandler.h"
#include "inputhandler.h"
#include "kinematicshandler.h"
#include "outputhandler.h"
#include "loggerhandler.h"
#include "simulationhandler.h"

GamepadHandler *gamepadHandler;
InputHandler *inputHandler;
KinematicsHandler *kinematicsHandler;
OutputHandler *outputHandler;
LoggerHandler *loggerHandler;
SimulationHandler *simulationHandler;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loggerHandler = new LoggerHandler(ui->loggerTextEdit);
    gamepadHandler = new GamepadHandler(loggerHandler);
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
                                      ui->kinematicsGraphView,
                                      loggerHandler);
    simulationHandler = new SimulationHandler();

    configureConnections();
    loggerHandler->clear();

    ui->loggerTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->loggerTextEdit->setVerticalScrollBar(ui->loggerVerticalScrollbar);

    ui->Application_Stack->setCurrentIndex(0);
    ui->home_toolButton->setChecked(true);
    ui->s_kine_perf_QualityCB->view()
        ->window()->setWindowFlag(Qt::NoDropShadowWindowHint);

    ui->simulation_Frame->layout()->addWidget(simulationHandler->getWidget());
    loggerHandler->write(LoggerConstants::INFO, "Setup 3D visualation");
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
            SIGNAL(inputsChanged(double,double,double)),
            kinematicsHandler,
            SLOT(updateSpeeds(double,double,double)));
    connect(kinematicsHandler,
            SIGNAL(speedsChanged(double,double)),
            outputHandler,
            SLOT(updateSliders(double,double)));
    connect(kinematicsHandler,
            SIGNAL(functionChanged(double,double,double,double)),
            outputHandler,
            SLOT(updateChart(double,double,double,double)));
    connect(kinematicsHandler,
            SIGNAL(speedsChanged(double,double)),
            simulationHandler,
            SLOT(updateAnimators(double,double)));

}

//MainWindow deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_home_toolButton_clicked()
{
    ui->Application_Stack->setCurrentIndex(0);
    ui->home_toolButton->setChecked(true);
    ui->settings_toolButton->setChecked(false);
    ui->info_toolButton->setChecked(false);
    //Disable focus on other pages by setting focus and also disabling
    //input handler
    //this->setFocus(ui->)

}

void MainWindow::on_settings_toolButton_clicked()
{
    ui->Application_Stack->setCurrentIndex(1);
    ui->home_toolButton->setChecked(false);
    ui->settings_toolButton->setChecked(true);
    ui->info_toolButton->setChecked(false);
}

void MainWindow::on_info_toolButton_clicked()
{
    ui->Application_Stack->setCurrentIndex(2);
    ui->home_toolButton->setChecked(false);
    ui->settings_toolButton->setChecked(false);
    ui->info_toolButton->setChecked(true);
}

void MainWindow::on_s_kine_perf_FPSSlider_valueChanged(int value)
{
    qDebug() << "test";
    switch(value) {
        case 0:
            ui->s_kine_perf_FPSLabel->setNum(15);
            break;
        case 1:
            ui->s_kine_perf_FPSLabel->setNum(30);
            break;
        case 2:
            ui->s_kine_perf_FPSLabel->setNum(60);
            break;
    }

}
