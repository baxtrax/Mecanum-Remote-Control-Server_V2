#include "settingshandler.h"

SettingsHandler::SettingsHandler(QLineEdit *conn_CamAddressTextRef,
                                 QLineEdit *conn_CamPortTextRef,
                                 QRadioButton *conn_CamEnButtonRef,
                                 QLineEdit *conn_CommAddressTextRef,
                                 QLineEdit *conn_CommPortTextRef,
                                 QRadioButton *conn_CommEnButtonRef)
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
    conn_CamPortText->setText(settings->value("connection/camera/port", "12345").toString());
    conn_CamEnButton->setChecked(settings->value("connection/camera/en", false).toBool());

    conn_CommAddressText->setText(settings->value("connection/socket/address", "123.123.123.123").toString());
    conn_CommPortText->setText(settings->value("connection/socket/port", "12345").toString());
    conn_CommEnButton->setChecked(settings->value("connection/socket/en", false).toBool());
}

void SettingsHandler::saveSettings()
{
    qDebug() << "Save Settings";
}
