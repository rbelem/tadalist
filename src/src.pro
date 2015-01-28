TEMPLATE = app
TARGET = tadalist

QT += \
    qml \
    quick

HEADERS += \
    tadalist.h \
    taskitem.h \
    tasklistmodel.h \
    tasklistmodelproxy.h \
    todolistitem.h \
    todolistmodel.h \
    todolistmodelproxy.h

SOURCES += \
    main.cpp \
    tadalist.cpp \
    taskitem.cpp \
    tasklistmodel.cpp \
    tasklistmodelproxy.cpp \
    todolistitem.cpp \
    todolistmodel.cpp \
    todolistmodelproxy.cpp

RESOURCES += \
    ../images/images.qrc \
    ../qml/qml.qrc


# Default rules for deployment.
include(../deployment.pri)
