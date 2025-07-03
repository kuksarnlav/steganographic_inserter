QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    backend/include/EasyBMP/EasyBMP.cpp \
    backend/src/Method.cpp \
    backend/src/MethodKutter.cpp \
    backend/src/MethodLSB.cpp \
    backend/src/MethodZhaoKoch.cpp \
    backend/src/Viewer.cpp \
    backend/src/Statistics.cpp

HEADERS += \
    mainwindow.h \
    backend/include/EasyBMP/EasyBMP.h \
    backend/include/Method.h \
    backend/include/MethodKutter.h \
    backend/include/MethodLSB.h \
    backend/include/MethodZhaoKoch.h \
    backend/include/types.h \
    backend/include/Viewer.h \
    backend/src/Statistics.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/backend/include
INCLUDEPATH += $$PWD/backend/include/EasyBMP

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
