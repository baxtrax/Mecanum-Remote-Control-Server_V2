#include "settingshandler.h"

SettingsHandler::SettingsHandler(QLineEdit *conn_CamAddressTextRef,
                                 QLineEdit *conn_CamPortTextRef,
                                 QRadioButton *conn_CamEnButtonRef,
                                 QLineEdit *conn_CommAddressTextRef,
                                 QLineEdit *conn_CommPortTextRef,
                                 QRadioButton *conn_CommEnButtonRef,
                                 QRadioButton *graph_PerformEnButtonRef,
                                 QComboBox *graph_PerformQualComboRef,
                                 QSlider *graph_PerformPointsSliderRef,
                                 QRadioButton *render_PerformFPSLimEnButtonRef,
                                 QComboBox *render_PerformQualComboRef,
                                 QSlider *render_PerformFPSSliderRef,
                                 QRadioButton *render_ViewEnButtonRef,
                                 QRadioButton *render_ViewCountEnButtonRef,
                                 QRadioButton *render_ViewDebugEnButtonRef,
                                 QRadioButton *appear_ThemeDarkEnButtonRef)
{
    settings = new QSettings(QSettings::IniFormat,
                             QSettings::UserScope,
                             "MechanumRemoteControl", "settings");
    qDebug() << settings->fileName();

    conn_CamAddressText = conn_CamAddressTextRef;
    conn_CamPortText = conn_CamPortTextRef;
    conn_CamEnButton = conn_CamEnButtonRef;

    conn_CommAddressText = conn_CommAddressTextRef;
    conn_CommPortText = conn_CommPortTextRef;
    conn_CommEnButton = conn_CommEnButtonRef;

    graph_PerformEnButton = graph_PerformEnButtonRef;
    graph_PerformQualCombo = graph_PerformQualComboRef;
    graph_PerformPointsSlider = graph_PerformPointsSliderRef;

    render_PerformFPSLimEnButton = render_PerformFPSLimEnButtonRef;
    render_PerformQualCombo = render_PerformQualComboRef;
    render_PerformFPSSlider = render_PerformFPSSliderRef;

    render_ViewEnButton = render_ViewEnButtonRef;
    render_ViewCountEnButton = render_ViewCountEnButtonRef;
    render_ViewDebugEnButton = render_ViewDebugEnButtonRef;

    appear_ThemeDarkEnButton = appear_ThemeDarkEnButtonRef;

    initSettings();
}
/**
 * @brief Used to initilize settings
 */
void SettingsHandler::initSettings()
{
    displaySettings();
    emit settingsUpdated();
}

void SettingsHandler::resetSettings()
{
    qDebug() << "Reset Settings";
    settings->value(SettingsConstants::CONN_CAM_ADDRESS, "123.123.123.123");
    settings->value(SettingsConstants::CONN_CAM_PORT, "12345");
    settings->value(SettingsConstants::CONN_CAM_EN, false);

    settings->value(SettingsConstants::CONN_SOCK_ADDRESS, "123.123.123.123");
    settings->value(SettingsConstants::CONN_SOCK_PORT, "12345");
    settings->value(SettingsConstants::CONN_SOCK_EN, false);

    settings->value(SettingsConstants::GRAPH_PERF_EN, false);
    settings->value(SettingsConstants::GRAPH_PERF_QUAL, 0);
    settings->value(SettingsConstants::GRAPH_PERF_POINTS, 15);

    settings->value(SettingsConstants::RENDER_PERF_FPS_EN, false);
    settings->value(SettingsConstants::RENDER_PERF_QUAL, 0);
    settings->value(SettingsConstants::RENDER_PERF_FPS_LIM, 0);

    settings->value(SettingsConstants::RENDER_VIEW_EN, false);
    settings->value(SettingsConstants::RENDER_VIEW_COUNT_EN, false);
    settings->value(SettingsConstants::RENDER_VIEW_DEBUG_EN, false);
    settings->value(SettingsConstants::APPEAR_THEME_DARK_EN, false);
    displaySettings();

}

void SettingsHandler::applySettings()
{
    qDebug() << "Apply Settings";
    saveSettings();
    emit settingsUpdated();
}

void SettingsHandler::displaySettings()
{
    qDebug() << "Display Settings";
    conn_CamAddressText->setText(settings->value(SettingsConstants::CONN_CAM_ADDRESS, "123.123.123.123").toString());
    conn_CamPortText->setText(settings->value(SettingsConstants::CONN_CAM_PORT, "12345").toString());
    conn_CamEnButton->setChecked(settings->value(SettingsConstants::CONN_CAM_EN, false).toBool());

    conn_CommAddressText->setText(settings->value(SettingsConstants::CONN_SOCK_ADDRESS, "123.123.123.123").toString());
    conn_CommPortText->setText(settings->value(SettingsConstants::CONN_SOCK_PORT, "12345").toString());
    conn_CommEnButton->setChecked(settings->value(SettingsConstants::CONN_SOCK_EN, false).toBool());

    graph_PerformEnButton->setChecked(settings->value(SettingsConstants::GRAPH_PERF_EN, false).toBool());
    graph_PerformQualCombo->setCurrentIndex(settings->value(SettingsConstants::GRAPH_PERF_QUAL, 0).toInt());
    graph_PerformPointsSlider->setValue(settings->value(SettingsConstants::GRAPH_PERF_POINTS, 15).toInt());

    render_PerformFPSLimEnButton->setChecked(settings->value(SettingsConstants::RENDER_PERF_FPS_EN, false).toBool());
    render_PerformQualCombo->setCurrentIndex(settings->value(SettingsConstants::RENDER_PERF_QUAL, 0).toInt());
    render_PerformFPSSlider->setValue(settings->value(SettingsConstants::RENDER_PERF_FPS_LIM, 0).toInt());

    render_ViewEnButton->setChecked(settings->value(SettingsConstants::RENDER_VIEW_EN, false).toBool());
    render_ViewCountEnButton->setChecked(settings->value(SettingsConstants::RENDER_VIEW_COUNT_EN, false).toBool());
    render_ViewDebugEnButton->setChecked(settings->value(SettingsConstants::RENDER_VIEW_DEBUG_EN, false).toBool());
    appear_ThemeDarkEnButton->setChecked(settings->value(SettingsConstants::APPEAR_THEME_DARK_EN, false).toBool());
}

void SettingsHandler::saveSettings()
{
    qDebug() << "Save Settings";
    settings->setValue(SettingsConstants::CONN_CAM_ADDRESS, conn_CamAddressText->text());

    settings->setValue(SettingsConstants::CONN_CAM_PORT, conn_CamPortText->text());
    settings->setValue(SettingsConstants::CONN_CAM_EN, conn_CamEnButton->isChecked());

    settings->setValue(SettingsConstants::CONN_SOCK_ADDRESS, conn_CommAddressText->text());
    settings->setValue(SettingsConstants::CONN_SOCK_PORT, conn_CommPortText->text());
    settings->setValue(SettingsConstants::CONN_SOCK_EN, conn_CommEnButton->isChecked());

    settings->setValue(SettingsConstants::GRAPH_PERF_EN, graph_PerformEnButton->isChecked());
    settings->setValue(SettingsConstants::GRAPH_PERF_QUAL, graph_PerformQualCombo->currentIndex());
    settings->setValue(SettingsConstants::GRAPH_PERF_POINTS, graph_PerformPointsSlider->value());

    settings->setValue(SettingsConstants::RENDER_PERF_FPS_EN, render_PerformFPSLimEnButton->isChecked());
    settings->setValue(SettingsConstants::RENDER_PERF_QUAL, render_PerformQualCombo->currentIndex());
    settings->setValue(SettingsConstants::RENDER_PERF_FPS_LIM, render_PerformFPSSlider->value());

    settings->setValue(SettingsConstants::RENDER_VIEW_EN, render_ViewEnButton->isChecked());
    settings->setValue(SettingsConstants::RENDER_VIEW_COUNT_EN, render_ViewCountEnButton->isChecked());
    settings->setValue(SettingsConstants::RENDER_VIEW_DEBUG_EN, render_ViewDebugEnButton->isChecked());

    settings->setValue(SettingsConstants::APPEAR_THEME_DARK_EN, appear_ThemeDarkEnButton->isChecked());
}

QSettings* SettingsHandler::getSettings()
{
    return settings;
}


