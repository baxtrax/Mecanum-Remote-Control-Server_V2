#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

#include "camerahandler.h"
#include "communicationhandler.h"
#include "gamepadhandler.h"
#include "inputhandler.h"
#include "kinematicshandler.h"
#include "loggerhandler.h"
#include "outputhandler.h"
#include "settingshandler.h"
#include "simulationhandler.h"

GamepadHandler *gamepadHandler;
InputHandler *inputHandler;
KinematicsHandler *kinematicsHandler;
OutputHandler *outputHandler;
LoggerHandler *loggerHandler;
SimulationHandler *simulationHandler;
SettingsHandler *settingsHandler;
CommunicationHandler *communicationHandler;
CameraHandler *cameraHandler;

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Passing in no actual logger below, need to repass in
    settingsHandler = new SettingsHandler();
    loggerHandler = new LoggerHandler(settingsHandler->getSettings());
    settingsHandler->setLogger(loggerHandler); // Need to pass in logger for later use
    communicationHandler = new CommunicationHandler(loggerHandler, settingsHandler->getSettings());
    gamepadHandler = new GamepadHandler(loggerHandler);
    inputHandler = new InputHandler(loggerHandler);
    kinematicsHandler = new KinematicsHandler(loggerHandler);
    outputHandler = new OutputHandler(loggerHandler, settingsHandler->getSettings());
    outputHandler->configureChartView(ui->kinematicsGraphView);
    simulationHandler = new SimulationHandler(loggerHandler, settingsHandler->getSettings());
    cameraHandler = new CameraHandler(loggerHandler, settingsHandler->getSettings());

    configureConnections();

    // Start to setup UI for user
    loggerHandler->clear();
    ui->loggerPlainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->loggerPlainTextEdit->setVerticalScrollBar(ui->loggerVerticalScrollbar);
    ui->Application_Stack->setCurrentIndex(0);
    ui->home_toolButton->setChecked(true);

    window()->setWindowFlag(Qt::NoDropShadowWindowHint);

    // Add 3D widget
    ui->render_placeholder->setStyleSheet(NULL);
    ui->simulation_Frame->layout()->replaceWidget(ui->render_placeholder,
                                                  simulationHandler->getWidget());
    ui->render_placeholder->deleteLater();

    // Add Camera widget
    ui->camera_placeholder->setStyleSheet(NULL);
    ui->camera_Frame->layout()->replaceWidget(ui->camera_placeholder, cameraHandler->getWidget());
    ui->camera_placeholder->deleteLater();

    int x = settingsHandler->getSettings()
                ->value(SettingsConstants::WINDOW_SIZE_X, SettingsConstants::D_WINDOW_SIZE_X)
                .toInt();

    int y = settingsHandler->getSettings()
                ->value(SettingsConstants::WINDOW_SIZE_Y, SettingsConstants::D_WINDOW_SIZE_Y)
                .toInt();
    resize(QSize(x, y));
}

/**
 * @brief Overloaded event function that uses events to control UI and application function.
 * @param event
 * @return status
 */
bool MainWindow::event(QEvent *event)
{
    int returnV = QWidget::event(event);

    if (event->type() == QEvent::Polish) {
        // Chart error checking and logging
        if (outputHandler->getChart()) {
            loggerHandler->write(LoggerConstants::INFO, "Setup kinematics chart");
        } else {
            loggerHandler->write(LoggerConstants::ERR, "Failed to setup kinematics chart");
        }

        // 3D error checking and logging
        if (simulationHandler->getWidget()) {
            loggerHandler->write(LoggerConstants::INFO, "Setup 3D visualization");
        } else {
            loggerHandler->write(LoggerConstants::ERR, "Failed to setup 3D visualization");
        }

        settingsHandler->initSettings();
        settingsHandler->checkStatus();
    }
    return returnV;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    //Scale settings
    if (this->size().width() < 1214) {
        QBoxLayout *swapLayout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
        swapLayout->addWidget(ui->MainSettingsWidget1);
        swapLayout->addWidget(ui->MainSettingsWidget2);
        swapLayout->insertSpacing(1, 16);
        swapLayout->setContentsMargins(0, 0, 0, 0);
        delete ui->scrollAreaWidgetContents->layout();
        ui->scrollAreaWidgetContents->setLayout(swapLayout);
    } else {
        QBoxLayout *swapLayout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
        swapLayout->addWidget(ui->MainSettingsWidget1);
        swapLayout->addWidget(ui->MainSettingsWidget2);
        swapLayout->insertSpacing(1, 16);
        swapLayout->setContentsMargins(0, 0, 0, 0);
        delete ui->scrollAreaWidgetContents->layout();
        ui->scrollAreaWidgetContents->setLayout(swapLayout);
    }
}

/**
 * @brief Is called when any key is pressed down and emits signals for each
 * key pressed.
 * @param A key pressed event.
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat() == false) {
        switch (event->key()) {
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
 * @param A key release event.
 */
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat() == false) {
        switch (event->key()) {
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

void MainWindow::closeEvent(QCloseEvent *)
{
    settingsHandler->storeWinSize(this->size());
}

/**
 * @brief Configures connections of slots and signals of a MainWindow object.
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
    connect(this, SIGNAL(keyboard_WChanged(bool)), inputHandler, SLOT(keyboard_WSetter(bool)));
    connect(this, SIGNAL(keyboard_SChanged(bool)), inputHandler, SLOT(keyboard_SSetter(bool)));
    connect(this, SIGNAL(keyboard_AChanged(bool)), inputHandler, SLOT(keyboard_ASetter(bool)));
    connect(this, SIGNAL(keyboard_DChanged(bool)), inputHandler, SLOT(keyboard_DSetter(bool)));
    connect(this, SIGNAL(keyboard_QChanged(bool)), inputHandler, SLOT(keyboard_QSetter(bool)));
    connect(this, SIGNAL(keyboard_EChanged(bool)), inputHandler, SLOT(keyboard_ESetter(bool)));
    connect(inputHandler,
            SIGNAL(inputsChanged(double, double, double)),
            kinematicsHandler,
            SLOT(updateSpeeds(double, double, double)));

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

    connect(outputHandler,
            &OutputHandler::setChartVisibility,
            ui->kinematicsGraphView,
            &QChartView::setVisible);
    connect(kinematicsHandler,
            SIGNAL(speedsChanged(double, double, double, double)),
            outputHandler,
            SLOT(updateSliders(double, double, double, double)));
    connect(kinematicsHandler,
            SIGNAL(functionChanged(double, double, double, double)),
            outputHandler,
            SLOT(updateChart(double, double, double, double)));
    connect(kinematicsHandler,
            SIGNAL(speedsChanged(double, double, double, double)),
            simulationHandler,
            SLOT(updateWheels(double, double, double, double)));
    connect(kinematicsHandler,
            SIGNAL(functionChanged(double, double, double, double)),
            simulationHandler,
            SLOT(updateArrow(double, double, double)));

    connect(kinematicsHandler,
            SIGNAL(speedsChanged(double, double, double, double)),
            communicationHandler,
            SLOT(sendMovementData(double, double, double, double)));

    connect(ui->settings_ResetButton, SIGNAL(clicked()), settingsHandler, SLOT(resetSettings()));
    connect(ui->settings_ApplyButton, &QRadioButton::clicked, this, [this]() {
        settingsHandler->applySettings(ui->conn_CamAddressText->text(),
                                       ui->conn_CamEnButton->isChecked(),
                                       ui->conn_CommAddressText->text(),
                                       ui->conn_CommPortText->text(),
                                       ui->conn_CommEnButton->isChecked(),
                                       ui->graph_PerformEnButton->isChecked(),
                                       ui->graph_PerformQualCombo->currentIndex(),
                                       ui->graph_PerformPointsSlider->value(),
                                       ui->graph_PerformAccelEnButton->isChecked(),
                                       ui->render_ViewEnButton->isChecked(),
                                       ui->render_ViewDebugEnButton->isChecked(),
                                       ui->appear_ThemeDarkEnButton->isChecked(),
                                       ui->appear_ThemeCLogsEnButton->isChecked(),
                                       ui->appear_ThemeTLogsEnButton->isChecked());
    });
    connect(ui->settings_CancelButton, SIGNAL(clicked()), settingsHandler, SLOT(displaySettings()));

    connect(ui->graph_PerformPointsSlider, &QSlider::valueChanged, this, [this](int value) {
        ui->graph_PerformPointsText->setNum(value);
    });

    connect(settingsHandler,
            &SettingsHandler::signalConn_CamAddressText,
            ui->conn_CamAddressText,
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
            &SettingsHandler::signalGraph_PerformAccelEnButton,
            ui->graph_PerformAccelEnButton,
            &QRadioButton::setChecked);

    connect(settingsHandler,
            &SettingsHandler::signalRender_ViewEnButton,
            ui->render_ViewEnButton,
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
            &SettingsHandler::signalAppear_ThemeCLogsEnButton,
            ui->appear_ThemeCLogsEnButton,
            &QRadioButton::setChecked);

    connect(settingsHandler,
            &SettingsHandler::signalAppear_ThemeTLogsEnButton,
            ui->appear_ThemeTLogsEnButton,
            &QRadioButton::setChecked);

    connect(settingsHandler,
            SIGNAL(settingsUpdated()),
            simulationHandler,
            SLOT(updateWithSettings()));
    connect(settingsHandler, SIGNAL(settingsUpdated()), outputHandler, SLOT(updateWithSettings()));
    connect(settingsHandler, SIGNAL(settingsUpdated()), loggerHandler, SLOT(updateWithSettings()));
    connect(settingsHandler,
            SIGNAL(settingsUpdated()),
            communicationHandler,
            SLOT(updateWithSettings()));
    connect(settingsHandler, SIGNAL(settingsUpdated()), cameraHandler, SLOT(updateWithSettings()));

    connect(settingsHandler, &SettingsHandler::settingsUpdated, this, [this]() {
        swapControl(settingsHandler->getSettings()
                        ->value(SettingsConstants::RENDER_VIEW_EN,
                                SettingsConstants::D_RENDER_VIEW_EN)
                        .toBool(),
                    settingsHandler->getSettings()
                        ->value(SettingsConstants::CONN_CAM_EN, SettingsConstants::D_CONN_CAM_EN)
                        .toBool());
    });

    connect(settingsHandler,
            &SettingsHandler::updateMinWResize,
            this,
            [this](bool graphEn, bool renderEn) {
                //This is not a GOOD exmaple on how to control scaling (im just lazy)
                if (renderEn) {
                    this->setMinimumWidth(1625);
                } else if (graphEn) {
                    this->setMinimumWidth(852);
                } else {
                    this->setMinimumWidth(674);
                }
            });

    connect(simulationHandler,
            &SimulationHandler::passKeyboard_WChanged,
            inputHandler,
            &InputHandler::keyboard_WSetter);
    connect(simulationHandler,
            &SimulationHandler::passKeyboard_SChanged,
            inputHandler,
            &InputHandler::keyboard_SSetter);
    connect(simulationHandler,
            &SimulationHandler::passKeyboard_AChanged,
            inputHandler,
            &InputHandler::keyboard_ASetter);
    connect(simulationHandler,
            &SimulationHandler::passKeyboard_DChanged,
            inputHandler,
            &InputHandler::keyboard_DSetter);
    connect(simulationHandler,
            &SimulationHandler::passKeyboard_QChanged,
            inputHandler,
            &InputHandler::keyboard_QSetter);
    connect(simulationHandler,
            &SimulationHandler::passKeyboard_EChanged,
            inputHandler,
            &InputHandler::keyboard_ESetter);

    connect(simulationHandler, &SimulationHandler::meshesLoaded, this, [] {
        loggerHandler->write(LoggerConstants::INFO, "Loaded all 3D meshes");
    });

    connect(communicationHandler, &CommunicationHandler::connectionStatus, this, [this](bool status) {
        if (status) {
            ui->communicationStatus->setDown(true);
            ui->communicationStatus->setText("Connected");
        } else {
            ui->communicationStatus->setDown(false);
            ui->communicationStatus->setText("Disconnected");
        }
    });

    connect(ui->refreshConnections,
            &QToolButton::pressed,
            communicationHandler,
            &CommunicationHandler::refreshConnection);
}

void MainWindow::swapControl(bool sim, bool cam)
{
    // Dont like how there are so many if statments
    if (sim && !cam) {
        ui->Viewport_Frame->setCurrentIndex(0);
        ui->swapWidget->hide();
        ui->Viewport_Frame->show();
    } else if (!sim && cam) {
        ui->Viewport_Frame->setCurrentIndex(1);
        ui->swapWidget->hide();
        ui->Viewport_Frame->show();
    } else if (sim && cam) {
        ui->swapWidget->show();
        ui->Viewport_Frame->show();
    } else if (!sim && !cam) {
        ui->swapWidget->hide();
        ui->Viewport_Frame->hide();
    }
}

// TODO deal with focus and disabling input to robot while other pages
// are open
/**
 * @brief Sets the look of the nav buttons and moves to Control page on the stacked widget.
 */
void MainWindow::on_home_toolButton_clicked()
{
    ui->Application_Stack->setCurrentIndex(0);
    ui->home_toolButton->setChecked(true);
    ui->settings_toolButton->setChecked(false);
    ui->info_toolButton->setChecked(false);
}

/**
 * @brief Sets the look of the nav buttons and moves to Settings page on the stacked widget.
 */
void MainWindow::on_settings_toolButton_clicked()
{
    ui->Application_Stack->setCurrentIndex(1);
    ui->home_toolButton->setChecked(false);
    ui->settings_toolButton->setChecked(true);
    ui->info_toolButton->setChecked(false);
}

/**
 * @brief Sets the look of the nav buttons and moves to Info page on the stacked widget.
 */
void MainWindow::on_info_toolButton_clicked()
{
    ui->Application_Stack->setCurrentIndex(2);
    ui->home_toolButton->setChecked(false);
    ui->settings_toolButton->setChecked(false);
    ui->info_toolButton->setChecked(true);
}

void MainWindow::on_swapViewsButton_clicked()
{
    if (ui->Viewport_Frame->currentIndex() == 0) {
        ui->Viewport_Frame->setCurrentIndex(1);
    } else {
        ui->Viewport_Frame->setCurrentIndex(0);
    }
}

// Deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}
