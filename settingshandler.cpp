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

void SettingsHandler::initSettings()
{
    displaySettings();
    emit settingsUpdated();
}

void SettingsHandler::resetSettings()
{
    qDebug() << "Reset Settings";
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
    conn_CamAddressText->setText(settings->value("connection/camera/address", "123.123.123.123").toString());
    conn_CamPortText->setText(settings->value("connection/camera/port", 12345).toString());
    conn_CamEnButton->setChecked(settings->value("connection/camera/en", false).toBool());

    conn_CommAddressText->setText(settings->value("connection/socket/address", "123.123.123.123").toString());
    conn_CommPortText->setText(settings->value("connection/socket/port", 12345).toString());
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
}
