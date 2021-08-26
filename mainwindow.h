#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void keyboard_WChanged(bool);
    void keyboard_SChanged(bool);
    void keyboard_AChanged(bool);
    void keyboard_DChanged(bool);
    void keyboard_QChanged(bool);
    void keyboard_EChanged(bool);

private:
    Ui::MainWindow *ui;
    void configureConnections();

private slots:
    void on_home_toolButton_clicked();
    void on_settings_toolButton_clicked();
    void on_info_toolButton_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *);
    bool event(QEvent *event);
};
#endif // MAINWINDOW_H NICWOLE CUTEST
