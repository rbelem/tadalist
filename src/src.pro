TEMPLATE = app
TARGET = tadalist

QT += \
    qml \
    quick

HEADERS += \
    tadalist.h \
    todolistitem.h \
    todolistmodel.h \
    taskitem.h \
    tasklistmodel.h \
    tasklistmodelproxy.h

SOURCES += \
    main.cpp \
    tadalist.cpp \
    todolistitem.cpp \
    todolistmodel.cpp \
    taskitem.cpp \
    tasklistmodel.cpp \
    tasklistmodelproxy.cpp

RESOURCES += \
    ../images/images.qrc \
    ../qml/qml.qrc


# Default rules for deployment.
include(../deployment.pri)
