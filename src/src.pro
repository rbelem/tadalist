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
    ../images/images.qrc \
    ../qml/qml.qrc


# Default rules for deployment.
include(../deployment.pri)
