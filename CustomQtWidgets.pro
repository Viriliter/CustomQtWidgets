QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    custombuttons.cpp \
    customindicators.cpp \
    customlabels.cpp \
    customprogressbars.cpp \
    customtextwidgets.cpp \
    customtoggles.cpp \
    customwidgets.cpp \
    main.cpp \
    mainwindow.cpp \
    swipewidget.cpp

HEADERS += \
    CustomColor.h \
    custombuttons.h \
    customindicators.h \
    customlabels.h \
    customprogressbars.h \
    customtextwidgets.h \
    customtoggles.h \
    customwidgets.h \
    mainwindow.h \
    swipewidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
