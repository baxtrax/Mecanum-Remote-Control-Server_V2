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

    loggerHandler = new LoggerHandler();
    settingsHandler = new SettingsHandler(loggerHandler);
    gamepadHandler = new GamepadHandler(loggerHandler);
    inputHandler = new InputHandler(loggerHandler);
    kinematicsHandler = new KinematicsHandler(loggerHandler);
    outputHandler = new OutputHandler(loggerHandler);
    outputHandler->configureChartView(ui->kinematicsGraphView);

    simulationHandler = new SimulationHandler(loggerHandler,
                                              settingsHandler->getSettings());

    configureConnections();
    loggerHandler->clear();

    ui->loggerPlainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->loggerPlainTextEdit->setVerticalScrollBar(ui->loggerVerticalScrollbar);

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


}

bool MainWindow::event(QEvent *event)
{
    int returnV = QWidget::event(event);

    if (event->type() == QEvent::Polish)
    {
        loggerHandler->write(LoggerConstants::INFO, "Setup kinematics chart");
        settingsHandler->initSettings();
        settingsHandler->checkStatus();
        //Need to verify that 3D is working some how (need to research)
        loggerHandler->write(LoggerConstants::INFO, "Setup 3D visualation");
    }
    return returnV;
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
    connect(loggerHandler,
            &LoggerHandler::appendingText,
            ui->loggerPlainTextEdit,
            &QPlainTextEdit::appendHtml);
    connect(loggerHandler,
            &LoggerHandler::clearingText,
            ui->loggerPlainTextEdit,
            &QPlainTextEdit::clear);

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

    connect(inputHandler,
            &InputHandler::x_topSlider_ValChanged,
            ui->axisX_topVSlider,
            &QSlider::setValue);
    connect(inputHandler,
            &InputHandler::x_botSlider_ValChanged,
            ui->axisX_botVSlider,
            &QSlider::setValue);
    connect(inputHandler,
            &InputHandler::y_topSlider_ValChanged,
            ui->axisY_topVSlider,
            &QSlider::setValue);
    connect(inputHandler,
            &InputHandler::y_botSlider_ValChanged,
            ui->axisY_botVSlider,
            &QSlider::setValue);
    connect(inputHandler,
            &InputHandler::z_topSlider_ValChanged,
            ui->axisZ_topVSlider,
            &QSlider::setValue);
    connect(inputHandler,
            &InputHandler::z_botSlider_ValChanged,
            ui->axisZ_botVSlider,
            &QSlider::setValue);

    connect(outputHandler,
            &OutputHandler::FR_topSlider_ValChanged,
            ui->FR_topVSlider,
            &QSlider::setValue);
    connect(outputHandler,
            &OutputHandler::FR_botSlider_ValChanged,
            ui->FR_botVSlider,
            &QSlider::setValue);
    connect(outputHandler,
            &OutputHandler::BL_topSlider_ValChanged,
            ui->BL_topVSlider,
            &QSlider::setValue);
    connect(outputHandler,
            &OutputHandler::BL_botSlider_ValChanged,
            ui->BL_botVSlider,
            &QSlider::setValue);
    connect(outputHandler,
            &OutputHandler::FL_topSlider_ValChanged,
            ui->FL_topVSlider,
            &QSlider::setValue);
    connect(outputHandler,
            &OutputHandler::FL_botSlider_ValChanged,
            ui->FL_botVSlider,
            &QSlider::setValue);
    connect(outputHandler,
            &OutputHandler::BR_topSlider_ValChanged,
            ui->BR_topVSlider,
            &QSlider::setValue);
    connect(outputHandler,
            &OutputHandler::BR_botSlider_ValChanged,
            ui->BR_botVSlider,
            &QSlider::setValue);

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
    connect(kinematicsHandler,
            &KinematicsHandler::speedsChanged,
            this,
            [this](double FRSpeed,
                   double BLSpeed,
                   double FLSpeed,
                   double BRSpeed)
            {
                if(settingsHandler->getSettings()->value(SettingsConstants::RENDER_VIEW_DEBUG_EN, false).toBool())
                {
                    ui->debug_FR->setText(QString{"%1"}.arg(FRSpeed, 5, 'f', 4, '0'));
                    ui->debug_BL->setText(QString{"%1"}.arg(BLSpeed, 5, 'f', 4, '0'));
                    ui->debug_FL->setText(QString{"%1"}.arg(FLSpeed, 5, 'f', 4, '0'));
                    ui->debug_BR->setText(QString{"%1"}.arg(BRSpeed, 5, 'f', 4, '0'));
                }
            });


    connect(ui->settings_ResetButton,
            SIGNAL(clicked()),
            settingsHandler,
            SLOT(resetSettings()));
    connect(ui->settings_ApplyButton,
            &QRadioButton::clicked,
            this,
            [this]()
            {
                settingsHandler->
                    applySettings(ui->conn_CamAddressText->text(),
                                  ui->conn_CamPortText->text(),
                                  ui->conn_CamEnButton->isChecked(),
                                  ui->conn_CommAddressText->text(),
                                  ui->conn_CommPortText->text(),
                                  ui->conn_CommEnButton->isChecked(),
                                  ui->graph_PerformEnButton->isChecked(),
                                  ui->graph_PerformQualCombo->currentIndex(),
                                  ui->graph_PerformPointsSlider->value(),
                                  ui->render_PerformFPSLimEnButton->isChecked(),
                                  ui->render_PerformQualCombo->currentIndex(),
                                  ui->render_PerformFPSSlider->value(),
                                  ui->render_ViewEnButton->isChecked(),
                                  ui->render_ViewCountEnButton->isChecked(),
                                  ui->render_ViewDebugEnButton->isChecked(),
                                  ui->appear_ThemeDarkEnButton->isChecked());
            });
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

    connect(settingsHandler,
            &SettingsHandler::signalConn_CamAddressText,
            ui->conn_CamAddressText,
            &QLineEdit::setText);
    connect(settingsHandler,
            &SettingsHandler::signalConn_CamPortText,
            ui->conn_CamPortText,
            &QLineEdit::setText);
    connect(settingsHandler,
            &SettingsHandler::signalConn_CamEnButton,
            ui->conn_CamEnButton,
            &QRadioButton::setChecked);

    connect(settingsHandler,
            &SettingsHandler::signalConn_CommAddressText,
            ui->conn_CommAddressText,
            &QLineEdit::setText);
    connect(settingsHandler,
            &SettingsHandler::signalConn_CommPortText,
            ui->conn_CommPortText,
            &QLineEdit::setText);
    connect(settingsHandler,
            &SettingsHandler::signalConn_CommEnButton,
            ui->conn_CommEnButton,
            &QRadioButton::setChecked);

    connect(settingsHandler,
            &SettingsHandler::signalGraph_PerformEnButton,
            ui->graph_PerformEnButton,
            &QRadioButton::setChecked);
    connect(settingsHandler,
            &SettingsHandler::signalGraph_PerformQualCombo,
            ui->graph_PerformQualCombo,
            &QComboBox::setCurrentIndex);
    connect(settingsHandler,
            &SettingsHandler::signalGraph_PerformPointsSlider,
            ui->graph_PerformPointsSlider,
            &QSlider::setValue);

    connect(settingsHandler,
            &SettingsHandler::signalRender_PerformFPSLimEnButton,
            ui->render_PerformFPSLimEnButton,
            &QRadioButton::setChecked);
    connect(settingsHandler,
            &SettingsHandler::signalRender_PerformQualCombo,
            ui->render_PerformQualCombo,
            &QComboBox::setCurrentIndex);
    connect(settingsHandler,
            &SettingsHandler::signalRender_PerformFPSSlider,
            ui->render_PerformFPSSlider,
            &QSlider::setValue);

    connect(settingsHandler,
            &SettingsHandler::signalRender_ViewEnButton,
            ui->render_ViewEnButton,
            &QRadioButton::setChecked);
    connect(settingsHandler,
            &SettingsHandler::signalRender_ViewCountEnButton,
            ui->render_ViewCountEnButton,
            &QRadioButton::setChecked);
    connect(settingsHandler,
            &SettingsHandler::signalRender_ViewDebugEnButton,
            ui->render_ViewDebugEnButton,
            &QRadioButton::setChecked);

    connect(settingsHandler,
            &SettingsHandler::signalAppear_ThemeDarkEnButton,
            ui->appear_ThemeDarkEnButton,
            &QRadioButton::setChecked);


    connect(settingsHandler,
            SIGNAL(settingsUpdated()),
            simulationHandler,
            SLOT(updateWithSettings()));

    connect(simulationHandler,
            &SimulationHandler::updateDebugFPS,
            this,
            [this](double fps)
            {
                if(settingsHandler->getSettings()->value(SettingsConstants::RENDER_VIEW_DEBUG_EN, false).toBool()) {
                    ui->debug_FPS->setText(QString{"%1"}.arg(fps, 3, 'f', 1, '0'));
                }
            });
    connect(simulationHandler,
            &SimulationHandler::setDebugInfoFrameVisible,
            ui->DebugInfoFrame,
            &QFrame::setVisible);
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
