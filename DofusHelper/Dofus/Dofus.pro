QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Characters.cpp \
    CharactersRow.cpp \
    Dummy.cpp \
    Helper.cpp \
    Logs.cpp \
    QtWidgetsClass.cpp \
    SubWindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Account.h \
    Characters.h \
    CharactersRow.h \
    Dummy.h \
    Helper.h \
    Logs.h \
    QtWidgetsClass.h \
    SubWindow.h \
    common.h \
    mainwindow.h

FORMS += \
    DofusHelper_v3.ui \
    QtWidgetsClass.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    DofusHelper_v3.qrc

DISTFILES += \
    Dofus.pro.user
