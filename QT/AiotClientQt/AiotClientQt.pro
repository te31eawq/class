QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network charts webenginewidgets sql

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cameracapture.cpp \
    keyboard.cpp \
    keyled.cpp \
    main.cpp \
    mainwidget.cpp \
    socketclient.cpp \
    tab1devcontrol.cpp \
    tab2socketclient.cpp \
    tab3controlpannel.cpp \
    tab4chartplot.cpp \
    tab5database.cpp \
    tab6webcamera.cpp \
    tab7camsecurity.cpp

HEADERS += \
    cameracapture.h \
    keyboard.h \
    keyled.h \
    mainwidget.h \
    socketclient.h \
    tab1devcontrol.h \
    tab2socketclient.h \
    tab3controlpannel.h \
    tab4chartplot.h \
    tab5database.h \
    tab6webcamera.h \
    tab7camsecurity.h

FORMS += \
    keyboard.ui \
    mainwidget.ui \
    tab1devcontrol.ui \
    tab2socketclient.ui \
    tab3controlpannel.ui \
    tab4chartplot.ui \
    tab5database.ui \
    tab6webcamera.ui \
    tab7camsecurity.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    AiotClient.qrc

INCLUDEPATH += /usr/local/include/opencv4
LIBS += `pkg-config opencv4 --cflags --libs`
