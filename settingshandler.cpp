#include "settingshandler.h"

// Constructor
SettingsHandler::SettingsHandler(LoggerHandler *loggerRef)
{
    logger = loggerRef;
    settings = new QSettings(QSettings::IniFormat,
                             QSettings::UserScope,
                             "MechanumRemoteControl",
                             "settings");
}

/**
 * @brief Will read current settings from file and set them up in the program,
 * initilizing them.
 */
void SettingsHandler::initSettings()
{
    settings->sync();
    displaySettings();
    emit settingsUpdated();
}

/**
 * @brief Resets the settings to defaults values and
 */
void SettingsHandler::resetSettings()
{
    emit signalConn_CamAddressText(SettingsConstants::D_CONN_CAM_ADDRESS);
    emit signalConn_CamPortText(SettingsConstants::D_CONN_CAM_PORT);
    emit signalConn_CamEnButton(SettingsConstants::D_CONN_CAM_EN);
    emit signalConn_CommAddressText(SettingsConstants::D_CONN_COMM_ADDRESS);
    emit signalConn_CommPortText(SettingsConstants::D_CONN_COMM_PORT);
    emit signalConn_CommEnButton(SettingsConstants::D_CONN_COMM_EN);
    emit signalGraph_PerformEnButton(SettingsConstants::D_GRAPH_PERF_EN);
    emit signalGraph_PerformQualCombo(SettingsConstants::D_GRAPH_PERF_QUAL);
    emit signalGraph_PerformPointsSlider(SettingsConstants::D_GRAPH_PERF_POINTS);
    emit signalGraph_PerformAccelEnButton(SettingsConstants::D_GRAPH_PERF_ACCEL);
    emit signalRender_ViewEnButton(SettingsConstants::D_RENDER_VIEW_EN);
    emit signalRender_ViewDebugEnButton(SettingsConstants::D_RENDER_VIEW_DEBUG_EN);
    emit signalAppear_ThemeDarkEnButton(SettingsConstants::D_APPEAR_THEME_DARK_EN);
    // Test
}

/**
 * @brief Apply current settings to file, will also proprogate changes
 * throughout the program.
 */
void SettingsHandler::applySettings(QString conn_CamAddressText,
                                    QString conn_CamPortText,
                                    bool conn_CamEnButton,
                                    QString conn_CommAddressText,
                                    QString conn_CommPortText,
                                    bool conn_CommEnButton,
                                    bool graph_PerformEnButton,
                                    int graph_PerformQualCombo,
                                    int graph_PerformPointsSlider,
                                    bool graph_PerformAccel,
                                    bool render_ViewEnButton,
                                    bool render_ViewDebugEnButton,
                                    bool appear_ThemeDarkEnButton)
{
    saveSettings(conn_CamAddressText,
                 conn_CamPortText,
                 conn_CamEnButton,
                 conn_CommAddressText,
                 conn_CommPortText,
                 conn_CommEnButton,
                 graph_PerformEnButton,
                 graph_PerformQualCombo,
                 graph_PerformPointsSlider,
                 graph_PerformAccel,
                 render_ViewEnButton,
                 render_ViewDebugEnButton,
                 appear_ThemeDarkEnButton);
    emit settingsUpdated();
}

/**
 * @brief Reads settings file and display them in GUI
 */
void SettingsHandler::displaySettings()
{
    // Camera Socket
    emit signalConn_CamAddressText(
        settings->value(SettingsConstants::CONN_CAM_ADDRESS, SettingsConstants::D_CONN_CAM_ADDRESS)
            .toString());
    emit signalConn_CamPortText(
        settings->value(SettingsConstants::CONN_CAM_PORT, SettingsConstants::D_CONN_CAM_PORT)
            .toString());
    emit signalConn_CamEnButton(
        settings->value(SettingsConstants::CONN_CAM_EN, SettingsConstants::D_CONN_CAM_EN).toBool());

    // Communication Socket
    emit signalConn_CommAddressText(
        settings->value(SettingsConstants::CONN_COMM_ADDRESS, SettingsConstants::D_CONN_COMM_ADDRESS)
            .toString());
    emit signalConn_CommPortText(
        settings->value(SettingsConstants::CONN_COMM_PORT, SettingsConstants::D_CONN_COMM_PORT)
            .toString());
    emit signalConn_CommEnButton(
        settings->value(SettingsConstants::CONN_COMM_EN, SettingsConstants::D_CONN_COMM_EN).toBool());

    // Graph
    emit signalGraph_PerformEnButton(
        settings->value(SettingsConstants::GRAPH_PERF_EN, SettingsConstants::D_GRAPH_PERF_EN)
            .toBool());
    emit signalGraph_PerformQualCombo(
        settings->value(SettingsConstants::GRAPH_PERF_QUAL, SettingsConstants::D_GRAPH_PERF_QUAL)
            .toInt());
    emit signalGraph_PerformPointsSlider(
        settings->value(SettingsConstants::GRAPH_PERF_POINTS, SettingsConstants::D_GRAPH_PERF_POINTS)
            .toInt());
    emit signalGraph_PerformAccelEnButton(
        settings->value(SettingsConstants::GRAPH_PERF_ACCEL, SettingsConstants::D_GRAPH_PERF_ACCEL)
            .toBool());

    // Render
    emit signalRender_ViewEnButton(
        settings->value(SettingsConstants::RENDER_VIEW_EN, SettingsConstants::D_RENDER_VIEW_EN)
            .toBool());
    emit signalRender_ViewDebugEnButton(settings
                                            ->value(SettingsConstants::RENDER_VIEW_DEBUG_EN,
                                                    SettingsConstants::D_RENDER_VIEW_DEBUG_EN)
                                            .toBool());

    // Appearance
    emit signalAppear_ThemeDarkEnButton(settings
                                            ->value(SettingsConstants::APPEAR_THEME_DARK_EN,
                                                    SettingsConstants::D_APPEAR_THEME_DARK_EN)
                                            .toBool());
}

/**
 * @brief Grabs current user entered settings and saves them to file.
 */
void SettingsHandler::saveSettings(QString conn_CamAddressText,
                                   QString conn_CamPortText,
                                   bool conn_CamEnButton,
                                   QString conn_CommAddressText,
                                   QString conn_CommPortText,
                                   bool conn_CommEnButton,
                                   bool graph_PerformEnButton,
                                   int graph_PerformQualCombo,
                                   int graph_PerformPointsSlider,
                                   bool graph_PerformAccel,
                                   bool render_ViewEnButton,
                                   bool render_ViewDebugEnButton,
                                   bool appear_ThemeDarkEnButton)
{
    // Camera Socket
    settings->setValue(SettingsConstants::CONN_CAM_ADDRESS, conn_CamAddressText);
    settings->setValue(SettingsConstants::CONN_CAM_PORT, conn_CamPortText);
    settings->setValue(SettingsConstants::CONN_CAM_EN, conn_CamEnButton);

    // Communication Socket
    settings->setValue(SettingsConstants::CONN_COMM_ADDRESS, conn_CommAddressText);
    settings->setValue(SettingsConstants::CONN_COMM_PORT, conn_CommPortText);
    settings->setValue(SettingsConstants::CONN_COMM_EN, conn_CommEnButton);

    // Graph
    settings->setValue(SettingsConstants::GRAPH_PERF_EN, graph_PerformEnButton);
    settings->setValue(SettingsConstants::GRAPH_PERF_QUAL, graph_PerformQualCombo);
    settings->setValue(SettingsConstants::GRAPH_PERF_POINTS, graph_PerformPointsSlider);
    settings->setValue(SettingsConstants::GRAPH_PERF_ACCEL, graph_PerformAccel);

    // Render
    settings->setValue(SettingsConstants::RENDER_VIEW_EN, render_ViewEnButton);
    settings->setValue(SettingsConstants::RENDER_VIEW_DEBUG_EN, render_ViewDebugEnButton);

    // Appearance
    settings->setValue(SettingsConstants::APPEAR_THEME_DARK_EN, appear_ThemeDarkEnButton);
}

/**
 * @brief Checks and reports status of settings file that is designated to be loaded.
 */
void SettingsHandler::checkStatus()
{
    settings->sync();

    switch (settings->status()) {
    case QSettings::NoError:
        logger->write(LoggerConstants::INFO, "Successfully loaded settings");
        break;
    case QSettings::AccessError:
        logger->write(LoggerConstants::ERR, "Could not access settings file");
        break;
    case QSettings::FormatError:
        logger->write(LoggerConstants::ERR, "Could not load settings file");
        break;
    }
}

// Getters
/**
 * @brief Gets the current instance of settings for other programs to grab from.
 * @return settings
 */
QSettings *SettingsHandler::getSettings()
{
    return settings;
}
