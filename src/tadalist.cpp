
#include "tadalist.h"

#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>

#include "todolistitem.h"
#include "todolistmodel.h"
#include "todolistmodelproxy.h"
#include "tasklistmodel.h"
#include "tasklistmodelproxy.h"

TadaList::TadaList(QObject *parent)
    : QQmlEngine(parent)
    , m_context(new QQmlContext(rootContext()))
    , m_component(new QQmlComponent(this))
    , m_todoListModel(new TodoListModel(this))
    , m_todoListModelCompleted(new TodoListModelProxy(this))
    , m_todoListModelUnfinished(new TodoListModelProxy(this))
    , m_taskListModel(new TaskListModel(this))
    , m_taskListModelProxy(new TaskListModelProxy(this))
{
    QCoreApplication *app = QCoreApplication::instance();
    connect(app, SIGNAL(aboutToQuit()), SLOT(onQuit()));

    qmlRegisterType<TaskListModel>("com.ics.tadalist", 0, 1, "TaskListModel");
    qmlRegisterType<TodoListItem>("com.ics.tadalist", 0, 1, "TodoListItem");
    qmlRegisterType<TodoListModel>("com.ics.tadalist", 0, 1, "TodoListModel");
    qmlRegisterType<TodoListModelProxy>("com.ics.tadalist", 0, 1, "TodoListModelProxy");

    m_todoListModelCompleted->setTodoListType(TodoListModelProxy::CompletedTodoList);
    m_todoListModelCompleted->setSourceModel(m_todoListModel);
    m_todoListModelUnfinished->setTodoListType(TodoListModelProxy::UnfinishedTodoList);
    m_todoListModelUnfinished->setSourceModel(m_todoListModel);
    m_taskListModelProxy->setSourceModel(m_taskListModel);

    m_context->setContextProperty("todoListModelCompleted", m_todoListModelCompleted);
    m_context->setContextProperty("todoListModelUnfinished", m_todoListModelUnfinished);
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
