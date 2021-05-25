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
#include "settingshandler.h"

GamepadHandler *gamepadHandler;
InputHandler *inputHandler;
KinematicsHandler *kinematicsHandler;
OutputHandler *outputHandler;
LoggerHandler *loggerHandler;
SimulationHandler *simulationHandler;
SettingsHandler *settingsHandler;

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
    outputHandler = new OutputHandler(ui->FR_topVSlider,
                                      ui->FR_botVSlider,
                                      ui->BL_topVSlider,
                                      ui->BL_botVSlider,
                                      ui->FL_topVSlider,
                                      ui->FL_botVSlider,
                                      ui->BR_topVSlider,
                                      ui->BR_botVSlider,
                                      ui->kinematicsGraphView,
                                      loggerHandler);
    simulationHandler = new SimulationHandler();
    settingsHandler = new SettingsHandler(ui->conn_CamAddressText,
                                          ui->conn_CamPortText,
                                          ui->conn_CamEnButton,
                                          ui->conn_CommAddressText,
                                          ui->conn_CommPortText,
                                          ui->conn_CommEnButton);

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
            SIGNAL(speedsChanged(double,double,double,double)),
            outputHandler,
            SLOT(updateSliders(double,double,double,double)));
    connect(kinematicsHandler,
            SIGNAL(functionChanged(double,double,double,double)),
            outputHandler,
            SLOT(updateChart(double,double,double,double)));
    connect(kinematicsHandler,
            SIGNAL(speedsChanged(double,double,double,double)),
            simulationHandler,
            SLOT(updateAnimators(double,double,double,double)));

    connect(ui->settings_ResetButton,
            SIGNAL(clicked()),
            settingsHandler,
            SLOT(resetSettings()));
    connect(ui->settings_ApplyButton,
            SIGNAL(clicked()),
            settingsHandler,
            SLOT(applySettings()));
    connect(ui->settings_CancelButton,
            SIGNAL(clicked()),
            settingsHandler,
            SLOT(displaySettings()));
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
