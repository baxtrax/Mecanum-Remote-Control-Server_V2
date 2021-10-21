QT += core gui charts datavisualization 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# TODO, get rid of resources_big and handle big images as external
CONFIG += c++17 resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    communicationhandler.cpp \
    custom3dwindow.cpp \
    gamepadhandler.cpp \
    helper.cpp \
    inputhandler.cpp \
    kinematicshandler.cpp \
    loggerhandler.cpp \
    main.cpp \
    mainwindow.cpp \
    outputhandler.cpp \
    settingshandler.cpp \
    simulationhandler.cpp

HEADERS += \
    communicationhandler.h \
    constants.h \
    custom3dwindow.h \
    gamepadhandler.h \
    helper.h \
    inputhandler.h \
    kinematicshandler.h \
    loggerhandler.h \
    mainwindow.h \
    outputhandler.h \
    settingshandler.h \
    simulationhandler.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
