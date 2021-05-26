#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QObject>
#include <QDebug>
#include <QSettings>

#include <QLineEdit>
#include <QRadioButton>
#include <QComboBox>

class SettingsHandler : public QObject
{
    Q_OBJECT
public:
    SettingsHandler(QLineEdit *conn_CamAddressTextRef,
                    QLineEdit *conn_CamPortTextRef,
                    QRadioButton *conn_CamEnButtonRef,
                    QLineEdit *conn_CommAddressTextRef,
                    QLineEdit *conn_CommPortTextRef,
                    QRadioButton *conn_CommEnButtonRef,
                    QRadioButton *graph_PerformEnButtonRef,
                    QComboBox *graph_PerformQualComboRef);

public slots:
    void resetSettings();
    void applySettings();
    void displaySettings();

private:
    QSettings *settings;

    QLineEdit *conn_CamAddressText;
    QLineEdit *conn_CamPortText;
    QRadioButton *conn_CamEnButton;
    QLineEdit *conn_CommAddressText;
    QLineEdit *conn_CommPortText;
    QRadioButton *conn_CommEnButton;
    QRadioButton *graph_PerformEnButton;
    QComboBox *graph_PerformQualCombo;

    void initSettings();
    void saveSettings();

signals:
    void settingsUpdated();
};

#endif // SETTINGSHANDLER_H
