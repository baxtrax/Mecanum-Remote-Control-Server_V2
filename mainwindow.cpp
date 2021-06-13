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

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Possible just pass in Ui instead of each ui element indiv
    loggerHandler = new LoggerHandler(ui->loggerTextEdit);
    settingsHandler = new SettingsHandler(ui->conn_CamAddressText,
                                          ui->conn_CamPortText,
                                          ui->conn_CamEnButton,
                                          ui->conn_CommAddressText,
                                          ui->conn_CommPortText,
                                          ui->conn_CommEnButton,
                                          ui->graph_PerformEnButton,
                                          ui->graph_PerformQualCombo,
                                          ui->graph_PerformPointsSlider,
                                          ui->render_PerformFPSLimEnButton,
                                          ui->render_PerformQualCombo,
                                          ui->render_PerformFPSSlider,
                                          ui->render_ViewEnButton,
                                          ui->render_ViewCountEnButton,
                                          ui->render_ViewDebugEnButton,
                                          ui->appear_ThemeDarkEnButton);
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
    simulationHandler = new SimulationHandler(settingsHandler->getSettings());

    configureConnections();
    loggerHandler->clear();

    ui->loggerTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->loggerTextEdit->setVerticalScrollBar(ui->loggerVerticalScrollbar);

    ui->Application_Stack->setCurrentIndex(0);
    ui->home_toolButton->setChecked(true);

    window()->setWindowFlag(Qt::NoDropShadowWindowHint);

    //Add 3D widget
    ui->render_placeholder->setStyleSheet(NULL);
    ui->simulation_Frame->layout()
        ->replaceWidget(ui->render_placeholder,
                        simulationHandler->getWidget());
    ui->render_placeholder->deleteLater();
    ui->DebugInfoFrame->setVisible(false);

    qDebug()<< ui->simulation_Frame->layout();
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
            break;
        case Qt::Key_S:
            emit keyboard_SChanged(true);
            break;
        case Qt::Key_A:
            emit keyboard_AChanged(true);
            break;
        case Qt::Key_D:
            emit keyboard_DChanged(true);
            break;
        case Qt::Key_Q:
            emit keyboard_QChanged(true);
            break;
        case Qt::Key_E:
            emit keyboard_EChanged(true);
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
            break;
        case Qt::Key_S:
            emit keyboard_SChanged(false);
            break;
        case Qt::Key_A:
            emit keyboard_AChanged(false);
            break;
        case Qt::Key_D:
            emit keyboard_DChanged(false);
            break;
        case Qt::Key_Q:
            emit keyboard_QChanged(false);
            break;
        case Qt::Key_E:
            emit keyboard_EChanged(false);
            break;
        }
    }
}


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

    // Quick settings connections
    // TODO move these into the settings handler
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
    connect(ui->graph_PerformPointsSlider,
            &QSlider::valueChanged,
            this,
            [this](int value) { ui->graph_PerformPointsText->setNum(value); });
    connect(ui->render_PerformFPSSlider,
            &QSlider::valueChanged,
            this,
            [this](int value)
            {
                switch(value) {
                case 0:
                    ui->render_PerformFPSText->setNum(15);
                    break;
                case 1:
                    ui->render_PerformFPSText->setNum(30);
                    break;
                case 2:
                    ui->render_PerformFPSText->setNum(60);
                    break;
                }
            });
}

//MainWindow deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}

// TODO deal with focus and disabling input to robot while other pages
// are open
void MainWindow::on_home_toolButton_clicked()
{
    ui->Application_Stack->setCurrentIndex(0);
    ui->home_toolButton->setChecked(true);
    ui->settings_toolButton->setChecked(false);
    ui->info_toolButton->setChecked(false);
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
