QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    frame.cpp \
    framemodel.cpp \
    main.cpp \
    mainwindow.cpp \
    productionmodel.cpp \
    semanticweb.cpp \
    semanticwebobject.cpp

HEADERS += \
    database.h \
    frame.h \
    framemodel.h \
    mainwindow.h \
    productionmodel.h \
    semanticweb.h \
    semanticwebobject.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Media.qrc

win32:RC_ICONS += $$PWD/images/Logo.ico
