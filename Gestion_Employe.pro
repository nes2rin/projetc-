QT       += core gui sql charts serialport network printsupport

QT       += core gui multimedia multimediawidgets
QT       +=widgets
QT +=svg
QT +=charts
QT +=printsupport
QT       += core gui axcontainer


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    arduino.cpp \
    chart.cpp \
    connect.cpp \
    connection.cpp \
    employe.cpp \
    employemodel.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow2.cpp \
    materiel.cpp \
    pdf.cpp \
    plante.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    rh.cpp \
    search.cpp \
    sms.cpp \
    smtp.cpp \
    smtpp.cpp \
    vente.cpp

HEADERS += \
    arduino.h \
    chart.h \
    connect.h \
    connection.h \
    employe.h \
    employemodel.h \
    login.h \
    mainwindow.h \
    mainwindow2.h \
    materiel.h \
    pdf.h \
    plante.h \
    qcustomplot.h \
    qrcode.h \
    rh.h \
    search.h \
    sms.h \
    smtp.h \
    smtpp.h \
    vente.h

FORMS += \
    login.ui \
    mainwindow.ui \
    mainwindow2.ui \
    rh.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../Desktop/projetc++/libeay32.dll \
    ../../Desktop/projetc++/ssleay32.dll

RESOURCES += \
    Resources.qrc
