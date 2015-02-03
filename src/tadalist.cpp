
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
    m_taskListModelProxy->setSortRole(TaskListModel::OrderRole);
    m_taskListModelProxy->setSourceModel(m_taskListModel);

    m_context->setContextProperty("todoListModelCompleted", m_todoListModelCompleted);
    m_context->setContextProperty("todoListModelUnfinished", m_todoListModelUnfinished);
    m_context->setContextProperty("taskListModelProxy", m_taskListModelProxy);

    m_component->loadUrl(QUrl("qrc:///main.qml"));

    QObject *topLevel = m_component->create(m_context);

    connect(m_taskListModel, &TaskListModel::dataChanged,
            this, &TadaList::onTaskListDataChanged);
    connect(m_taskListModel, &TaskListModel::rowsInserted,
            this, &TadaList::onTaskListRowsInserted);
    connect(m_taskListModel, &TaskListModel::rowsRemoved,
            this, &TadaList::onTaskListRowsRemoved);
}

TadaList::~TadaList()
{
}

void TadaList::onQuit()
{
    qCritical() << "onQuit called";
}

void TadaList::onTaskListDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    QHash<int, int> changedItems;

    int i;
    for (i = topLeft.row(); i <= bottomRight.row(); ++i) {
        QModelIndex item = m_taskListModel->index(i, 0);
        int todoListId = item.data(TaskListModel::TodoListIdRole).toInt();
        bool taskCompleted = item.data(TaskListModel::CompletedRole).toBool();

        if (!changedItems.contains(todoListId))
            changedItems.insert(todoListId, 0);

        int count = changedItems.value(todoListId);
        changedItems.insert(todoListId, taskCompleted ? --count : ++count);
    }

    QHash<int, int>::const_iterator itr;
    for (itr = changedItems.constBegin(); itr != changedItems.constEnd(); ++itr) {
        QModelIndex todoListIndex = m_todoListModel->indexById(itr.key());
        int currentTasksLeft = m_todoListModel->data(todoListIndex, TodoListModel::TasksLeftRole).toInt();
        m_todoListModel->setData(todoListIndex, currentTasksLeft + itr.value(), TodoListModel::TasksLeftRole);
    }
}

void TadaList::onTaskListRowsInserted(const QModelIndex &parent, int start, int end)
{
    QModelIndex startItem = m_taskListModel->index(start, 0);
    QModelIndex endItem = m_taskListModel->index(end, 0);

    QHash<int, int> removedItems;

    for (int i = start; i <= end; ++i) {
        QModelIndex item = m_taskListModel->index(i, 0);
        if (true == item.data(TaskListModel::CompletedRole).toBool())
            continue;

        int todoListId = item.data(TaskListModel::TodoListIdRole).toInt();
        if (!removedItems.contains(todoListId)) {
            removedItems.insert(todoListId, 1);
        } else {
            int count = removedItems.value(todoListId);
            removedItems.insert(todoListId, ++count);
        }
    }

    QHash<int, int>::const_iterator itr;
    for (itr = removedItems.constBegin(); itr != removedItems.constEnd(); ++itr) {
        QModelIndex todoListIndex = m_todoListModel->indexById(itr.key());
        int currentTasksLeft = m_todoListModel->data(todoListIndex, TodoListModel::TasksLeftRole).toInt();
        m_todoListModel->setData(todoListIndex, currentTasksLeft + itr.value(), TodoListModel::TasksLeftRole);
    }
}

void TadaList::onTaskListRowsRemoved(const QModelIndex &parent, int start, int end)
{
    int removedItems = end - start + 1;
    QModelIndex todoListIndex = m_todoListModel->indexById(m_taskListModelProxy->todoListId());
    int currentTasksLeft = m_todoListModel->data(todoListIndex, TodoListModel::TasksLeftRole).toInt();

    m_todoListModel->setData(todoListIndex, currentTasksLeft - removedItems, TodoListModel::TasksLeftRole);
}
