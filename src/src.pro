TEMPLATE = app
TARGET = tadalist

QT += \
    qml \
    quick

HEADERS += \
    tadalist.h \
    tadalistitem.h \
    tadalistmodel.h \
    taskitem.h \
    tasklistmodel.h \
    tasklistmodelproxy.h

SOURCES += \
    main.cpp \
    tadalist.cpp \
    tadalistitem.cpp \
    tadalistmodel.cpp \
    taskitem.cpp \
    tasklistmodel.cpp \
    tasklistmodelproxy.cpp

RESOURCES += \
    ../images/images.qrc \
    ../qml/qml.qrc


# Default rules for deployment.
include(../deployment.pri)
