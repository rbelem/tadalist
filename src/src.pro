TEMPLATE = app
TARGET = tadalist

QT += \
    qml \
    quick

HEADERS += \
    tadalist.h

SOURCES += \
    tadalist.cpp \
    main.cpp

RESOURCES += \
    ../qml/qml.qrc


# Default rules for deployment.
include(../deployment.pri)
