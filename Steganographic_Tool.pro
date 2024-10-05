QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    InserterBMP.cpp \
    main.cpp \
    mainwindow.cpp\
    EasyBMP/EasyBMP.cpp

HEADERS += \
    InserterBMP.h \
    mainwindow.h \
    EasyBMP/EasyBMP.h

INCLUDEPATH += EasyBMP

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE = appIcon.rc
