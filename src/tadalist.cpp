
#include "tadalist.h"

#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>

#include "todolistmodel.h"
#include "tasklistmodel.h"
#include "tasklistmodelproxy.h"

TadaList::TadaList(QObject *parent)
    : QQmlEngine(parent)
    , m_context(new QQmlContext(rootContext()))
    , m_component(new QQmlComponent(this))
    , m_todoListModel(new TodoListModel(this))
    , m_taskListModel(new TaskListModel(this))
    , m_taskListModelProxy(new TaskListModelProxy(this))
{
    QCoreApplication *app = QCoreApplication::instance();
    connect(app, SIGNAL(aboutToQuit()), SLOT(onQuit()));

    m_taskListModelProxy->setSourceModel(m_taskListModel);

    m_context->setContextProperty("todoListModel", m_todoListModel);
    m_context->setContextProperty("taskListModelProxy", m_taskListModelProxy);

    m_component->loadUrl(QUrl("qrc:///main.qml"));

    QObject *topLevel = m_component->create(m_context);
}

TadaList::~TadaList()
{
}

void TadaList::onQuit()
{
    qCritical() << "onQuit called";
}
