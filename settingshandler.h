#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include "constants.h"
#include "loggerhandler.h"

#include <QDebug>
#include <QObject>
#include <QSettings>

#include <QComboBox>
#include <QLineEdit>
#include <QRadioButton>

class SettingsHandler : public QObject
{
    Q_OBJECT
public:
    // Functions
    SettingsHandler();
    QSettings *getSettings();
    void applySettings(QString conn_CamAddressText,
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
                       bool appear_ThemeDarkEnButton,
                       bool appear_ThemeCLogsEnButton,
                       bool appear_ThemeCTimeEnButton);
    void checkStatus();
    void initSettings();
    void setLogger(LoggerHandler *loggerRef);

public slots:
    void resetSettings();
    void displaySettings();
    void storeWinSize(QSize);

signals:
    void signalConn_CamAddressText(QString);
    void signalConn_CamEnButton(bool);
    void signalConn_CommAddressText(QString);
    void signalConn_CommPortText(QString);
    void signalConn_CommEnButton(bool);
    void signalGraph_PerformEnButton(bool);
    void signalGraph_PerformQualCombo(int);
    void signalGraph_PerformPointsSlider(int);
    void signalGraph_PerformAccelEnButton(bool);
    void signalRender_ViewEnButton(bool);
    void signalRender_ViewDebugEnButton(bool);
    void signalAppear_ThemeDarkEnButton(bool);
    void signalAppear_ThemeCLogsEnButton(bool);
    void signalAppear_ThemeTLogsEnButton(bool);
    void settingsUpdated();
    void updateMinWResize(bool, bool);

private:
    QSettings *settings;
    LoggerHandler *logger;

    void saveSettings(QString conn_CamAddressText,
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
                      bool appear_ThemeDarkEnButton,
                      bool appear_ThemeCLogsEnButton,
                      bool appear_ThemeCTimeEnButton);
};

#endif // SETTINGSHANDLER_H
