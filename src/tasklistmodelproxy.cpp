
#include "tasklistmodelproxy.h"

#include "tasklistmodel.h"

TaskListModelProxy::TaskListModelProxy(QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_todoListId(-1)
{
}

TaskListModelProxy::TaskListModelProxy(const TaskListModelProxy &other)
    : QSortFilterProxyModel(0)
    , m_todoListId(-1)
{
}

void TaskListModelProxy::setTodoListId(int id)
{
    if (id == m_todoListId)
        return;

    m_todoListId = id;
}

bool TaskListModelProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    int sourceTodoListId = index.data(TaskListModel::TodoListIdRole).toInt();
    if (sourceTodoListId == m_todoListId)
        return true;

    return false;
}

bool TaskListModelProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return true;
}
