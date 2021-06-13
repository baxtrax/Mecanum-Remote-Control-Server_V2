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
    settings->value("connection/camera/port", "12345");
    settings->value("connection/camera/en", false);

    settings->value("connection/socket/address", "123.123.123.123");
    settings->value("connection/socket/port", "12345");
    settings->value("connection/socket/en", false);

    settings->value("graph/performance/en", false);
    settings->value("graph/performance/qual", 0);
    settings->value("graph/performance/points", 15);

    settings->value("render/performance/FPS_en", false);
    settings->value("render/performance/qual", 0);
    settings->value("render/performance/FPS_lim", 0);

    settings->value("render/view/en", false);
    settings->value("render/view/count_en", false);
    settings->value("render/view/debug_en", false);
    settings->value("appear/theme/dark_en", false);
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
    conn_CamPortText->setText(settings->value("connection/camera/port", "12345").toString());
    conn_CamEnButton->setChecked(settings->value("connection/camera/en", false).toBool());

    conn_CommAddressText->setText(settings->value("connection/socket/address", "123.123.123.123").toString());
    conn_CommPortText->setText(settings->value("connection/socket/port", "12345").toString());
    conn_CommEnButton->setChecked(settings->value("connection/socket/en", false).toBool());

    graph_PerformEnButton->setChecked(settings->value("graph/performance/en", false).toBool());
    graph_PerformQualCombo->setCurrentIndex(settings->value("graph/performance/qual", 0).toInt());
    graph_PerformPointsSlider->setValue(settings->value("graph/performance/points", 15).toInt());

    render_PerformFPSLimEnButton->setChecked(settings->value("render/performance/FPS_en", false).toBool());
    render_PerformQualCombo->setCurrentIndex(settings->value("render/performance/qual", 0).toInt());
    render_PerformFPSSlider->setValue(settings->value("render/performance/FPS_lim", 0).toInt());

    render_ViewEnButton->setChecked(settings->value("render/view/en", false).toBool());
    render_ViewCountEnButton->setChecked(settings->value("render/view/count_en", false).toBool());
    render_ViewDebugEnButton->setChecked(settings->value("render/view/debug_en", false).toBool());
    appear_ThemeDarkEnButton->setChecked(settings->value("appear/theme/dark_en", false).toBool());
}

void SettingsHandler::saveSettings()
{
    qDebug() << "Save Settings";
    settings->setValue(SettingsConstants::CONN_CAM_ADDRESS, conn_CamAddressText->text());

    settings->setValue("connection/camera/port", conn_CamPortText->text());
    settings->setValue("connection/camera/en", conn_CamEnButton->isChecked());

    settings->setValue("connection/socket/address", conn_CommAddressText->text());
    settings->setValue("connection/socket/port", conn_CommPortText->text());
    settings->setValue("connection/socket/en", conn_CommEnButton->isChecked());

    settings->setValue("graph/performance/en", graph_PerformEnButton->isChecked());
    settings->setValue("graph/performance/qual", graph_PerformQualCombo->currentIndex());
    settings->setValue("graph/performance/points", graph_PerformPointsSlider->value());

    settings->setValue("render/performance/FPS_en", render_PerformFPSLimEnButton->isChecked());
    settings->setValue("render/performance/qual", render_PerformQualCombo->currentIndex());
    settings->setValue("render/performance/FPS_lim", render_PerformFPSSlider->value());

    settings->setValue("render/view/en", render_ViewEnButton->isChecked());
    settings->setValue("render/view/count_en", render_ViewCountEnButton->isChecked());
    settings->setValue("render/view/debug_en", render_ViewDebugEnButton->isChecked());

    settings->setValue("appear/theme/dark_en", appear_ThemeDarkEnButton->isChecked());
}

QSettings* SettingsHandler::getSettings()
{
    return settings;
}


