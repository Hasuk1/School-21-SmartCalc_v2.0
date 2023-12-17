QT       += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
ICON = icon.png
TARGET = SmartCalc_v2.0

SOURCES += \
    ../model/calculator_model.cc \
    ../model/credit_model.cc \
    ../model/deposit_model.cc \
    calculator.cc \
    credit.cc \
    deposit.cc \
    graph.cc \
    main.cc \
    qcustomplot.cpp

HEADERS += \
    ../controller/calculator_controller.h \
    ../controller/credit_controller.h \
    ../controller/deposit_controller.h \
    ../model/calculator_model.h \
    ../model/credit_model.h \
    ../model/deposit_model.h \
    calculator.h \
    credit.h \
    deposit.h \
    graph.h \
    qcustomplot.h

FORMS += \
    calculator.ui \
    credit.ui \
    deposit.ui \
    graph.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
