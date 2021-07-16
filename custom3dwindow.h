#ifndef CUSTOM3DWINDOW_H
#define CUSTOM3DWINDOW_H

#include <QDebug>
#include <QKeyEvent>
#include <Qt3DExtras/Qt3DWindow>

class Custom3DWindow : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT
public:
    Custom3DWindow(QScreen *screen = nullptr);
    ~Custom3DWindow();
signals:
    void passKeyboard_WChanged(bool);
    void passKeyboard_SChanged(bool);
    void passKeyboard_AChanged(bool);
    void passKeyboard_DChanged(bool);
    void passKeyboard_QChanged(bool);
    void passKeyboard_EChanged(bool);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // CUSTOM3DWINDOW_H
