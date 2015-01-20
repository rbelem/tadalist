
#include "tasklistmodel.h"
#include "taskitem.h"

TaskListModel::TaskListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    initRoles();
}

TaskListModel::~TaskListModel()
{
}

QVariant TaskListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count())
        return QVariant();

    const TaskItem *item = m_items[index.row()];

    if (role == IdRole)
        return item->id();

    if (role == TodoListIdRole)
        return item->todoListId();

    if (role == OrderRole)
        return item->order();

    if (role == CompletedRole)
        return item->completed();

    if (role == TaskNameRole)
        return item->name();

    return QVariant();
}

bool TaskListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_items.count())
        return false;

    TaskItem *item = m_items[index.row()];

    if (role == IdRole)
        item->setId(value.toInt());
    else if (role == TodoListIdRole)
        item->setTodoListId(value.toInt());
    else if (role == OrderRole)
        item->setOrder(value.toInt());
    else if (role == CompletedRole)
        item->setCompleted(value.toBool());
    else if (role == TaskNameRole)
        item->setName(value.toString());
    else
        return false;

    return true;
}

int TaskListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_items.count();
}

QHash<int, QByteArray> TaskListModel::roleNames() const
{
    return m_roles;
}

void TaskListModel::initRoles()
{
    m_roles[IdRole] = "taskId";
    m_roles[TodoListIdRole] = "todoListId";
    m_roles[OrderRole] = "taskOrder";
    m_roles[CompletedRole] = "taskCompleted";
    m_roles[TaskNameRole] = "taskName";
}
