#include "settingshandler.h"

SettingsHandler::SettingsHandler(LoggerHandler *loggerRef)
{
    logger = loggerRef;
    settings = new QSettings(QSettings::IniFormat,
                             QSettings::UserScope,
                             "MechanumRemoteControl", "settings");
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
    qDebug() << "Reset Settings";    
    emit signalConn_CamAddressText("123.123.123.123");
    emit signalConn_CamPortText("12345");
    emit signalConn_CamEnButton(false);
    emit signalConn_CommAddressText("123.123.123.123");
    emit signalConn_CommPortText("12345");
    emit signalConn_CommEnButton(false);
    emit signalGraph_PerformEnButton(false);
    emit signalGraph_PerformQualCombo(0);
    emit signalGraph_PerformPointsSlider(15);
    emit signalRender_PerformFPSLimEnButton(false);
    emit signalRender_PerformQualCombo(0);
    emit signalRender_PerformFPSSlider(0);
    emit signalRender_ViewEnButton(false);
    emit signalRender_ViewCountEnButton(false);
    emit signalRender_ViewDebugEnButton(false);
    emit signalAppear_ThemeDarkEnButton(false);

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
                                    bool render_PerformFPSLimEnButton,
                                    int render_PerformQualCombo,
                                    int render_PerformFPSSlider,
                                    bool render_ViewEnButton,
                                    bool render_ViewCountEnButton,
                                    bool render_ViewDebugEnButton,
                                    bool appear_ThemeDarkEnButton)
{
    qDebug() << "Apply Settings";
    saveSettings(conn_CamAddressText,
                 conn_CamPortText,
                 conn_CamEnButton,
                 conn_CommAddressText,
                 conn_CommPortText,
                 conn_CommEnButton,
                 graph_PerformEnButton,
                 graph_PerformQualCombo,
                 graph_PerformPointsSlider,
                 render_PerformFPSLimEnButton,
                 render_PerformQualCombo,
                 render_PerformFPSSlider,
                 render_ViewEnButton,
                 render_ViewCountEnButton,
                 render_ViewDebugEnButton,
                 appear_ThemeDarkEnButton);
    emit settingsUpdated();
}


/**
 * @brief Reads settings file and display them in GUI
 */
void SettingsHandler::displaySettings()
{
    qDebug() << "Display Settings";
    //qDebug() << settings->value(SettingsConstants::CONN_CAM_ADDRESS).toString();
    emit signalConn_CamAddressText(
        settings->value(
                    SettingsConstants::CONN_CAM_ADDRESS,
                    "123.123.123.123").toString());
    emit signalConn_CamPortText(
        settings->value(
                    SettingsConstants::CONN_CAM_PORT,
                    "12345").toString());
    emit signalConn_CamEnButton(
        settings->value(
                    SettingsConstants::CONN_CAM_EN,
                    false).toBool());

    emit signalConn_CommAddressText(
        settings->value(
                    SettingsConstants::CONN_SOCK_ADDRESS,
                    "123.123.123.123").toString());
    emit signalConn_CommPortText(
        settings->value(
                    SettingsConstants::CONN_SOCK_PORT,
                    "12345").toString());
    emit signalConn_CommEnButton(
        settings->value(
                    SettingsConstants::CONN_SOCK_EN,
                    false).toBool());

    emit signalGraph_PerformEnButton(
        settings->value(
                    SettingsConstants::GRAPH_PERF_EN,
                    false).toBool());
    emit signalGraph_PerformQualCombo(
        settings->value(
                    SettingsConstants::GRAPH_PERF_QUAL,
                    0).toInt());
    emit signalGraph_PerformPointsSlider(
        settings->value(
                    SettingsConstants::GRAPH_PERF_POINTS,
                    15).toInt());

    emit signalRender_PerformFPSLimEnButton(
        settings->value(
                    SettingsConstants::RENDER_PERF_FPS_EN,
                    false).toBool());
    emit signalRender_PerformQualCombo(
        settings->value(
                    SettingsConstants::RENDER_PERF_QUAL,
                    0).toInt());
    emit signalRender_PerformFPSSlider(
        settings->value(
                    SettingsConstants::RENDER_PERF_FPS_LIM,
                    0).toInt());

    emit signalRender_ViewEnButton(
        settings->value(
                    SettingsConstants::RENDER_VIEW_EN,
                    false).toBool());
    emit signalRender_ViewCountEnButton(
        settings->value(
                    SettingsConstants::RENDER_VIEW_COUNT_EN,
                    false).toBool());
    emit signalRender_ViewDebugEnButton(
        settings->value(
                    SettingsConstants::RENDER_VIEW_DEBUG_EN,
                    false).toBool());
    emit signalAppear_ThemeDarkEnButton(
        settings->value(
                    SettingsConstants::APPEAR_THEME_DARK_EN,
                    false).toBool());
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
                                   bool render_PerformFPSLimEnButton,
                                   int render_PerformQualCombo,
                                   int render_PerformFPSSlider,
                                   bool render_ViewEnButton,
                                   bool render_ViewCountEnButton,
                                   bool render_ViewDebugEnButton,
                                   bool appear_ThemeDarkEnButton)
{
    qDebug() << "Save Settings";
    settings->setValue(
        SettingsConstants::CONN_CAM_ADDRESS,
        conn_CamAddressText);

    settings->setValue(
        SettingsConstants::CONN_CAM_PORT,
        conn_CamPortText);
    settings->setValue(
        SettingsConstants::CONN_CAM_EN,
        conn_CamEnButton);

    settings->setValue(
        SettingsConstants::CONN_SOCK_ADDRESS,
        conn_CommAddressText);
    settings->setValue(
        SettingsConstants::CONN_SOCK_PORT,
        conn_CommPortText);
    settings->setValue(
        SettingsConstants::CONN_SOCK_EN,
        conn_CommEnButton);

    settings->setValue(
        SettingsConstants::GRAPH_PERF_EN,
        graph_PerformEnButton);
    settings->setValue(
        SettingsConstants::GRAPH_PERF_QUAL,
        graph_PerformQualCombo);
    settings->setValue(
        SettingsConstants::GRAPH_PERF_POINTS,
        graph_PerformPointsSlider);

    settings->setValue(
        SettingsConstants::RENDER_PERF_FPS_EN,
        render_PerformFPSLimEnButton);
    settings->setValue(
        SettingsConstants::RENDER_PERF_QUAL,
        render_PerformQualCombo);
    settings->setValue(
        SettingsConstants::RENDER_PERF_FPS_LIM,
        render_PerformFPSSlider);

    settings->setValue(
        SettingsConstants::RENDER_VIEW_EN,
        render_ViewEnButton);
    settings->setValue(
        SettingsConstants::RENDER_VIEW_COUNT_EN,
        render_ViewCountEnButton);
    settings->setValue(
        SettingsConstants::RENDER_VIEW_DEBUG_EN,
        render_ViewDebugEnButton);

    settings->setValue(
        SettingsConstants::APPEAR_THEME_DARK_EN,
        appear_ThemeDarkEnButton);
}


void SettingsHandler::checkStatus()
{
    settings->sync();
    qDebug() << settings->fileName();
    switch(settings->status()) {
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


/**
 * @brief Gets the current instance of settings for other programs to grab from.
 * @return Qsettings pointer
 */
QSettings* SettingsHandler::getSettings()
{
    return settings;
}


