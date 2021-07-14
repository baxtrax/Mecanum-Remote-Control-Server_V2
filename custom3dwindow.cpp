#include "custom3dwindow.h"

Custom3DWindow::Custom3DWindow(QScreen *screen):Qt3DExtras::Qt3DWindow(screen)
{

}
Custom3DWindow::~Custom3DWindow()
{

}

void Custom3DWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat() == false)
    {
        switch(event->key())
        {
        case Qt::Key_W:
            emit passKeyboard_WChanged(true);
            break;
        case Qt::Key_S:
            emit passKeyboard_SChanged(true);
            break;
        case Qt::Key_A:
            emit passKeyboard_AChanged(true);
            break;
        case Qt::Key_D:
            emit passKeyboard_DChanged(true);
            break;
        case Qt::Key_Q:
            emit passKeyboard_QChanged(true);
            break;
        case Qt::Key_E:
            emit passKeyboard_EChanged(true);
            break;
        }
    }
}

void Custom3DWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat() == false)
    {
        switch(event->key())
        {
        case Qt::Key_W:
            emit passKeyboard_WChanged(false);
            break;
        case Qt::Key_S:
            emit passKeyboard_SChanged(false);
            break;
        case Qt::Key_A:
            emit passKeyboard_AChanged(false);
            break;
        case Qt::Key_D:
            emit passKeyboard_DChanged(false);
            break;
        case Qt::Key_Q:
            emit passKeyboard_QChanged(false);
            break;
        case Qt::Key_E:
            emit passKeyboard_EChanged(false);
            break;
        }
    }
}
