TEMPLATE = app

QT += qml quick
CONFIG += debug

SOURCES += main.cpp \
    cudpfetcher.cpp \
    ctcpfetcher.cpp \
    qnetfetcherbase.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    cudpfetcher.h \
    ctcpfetcher.h \
    qnetfetcherbase.h
