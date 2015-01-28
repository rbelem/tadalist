
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

void TaskListModelProxy::addItem()
{
    TaskListModel *model = qobject_cast<TaskListModel *>(sourceModel());
    model->addItem(m_todoListId);
}

void TaskListModelProxy::updateItem(int id, const QVariant &value, int role)
{
    QModelIndex itemIndex = index(id, 0);
    sourceModel()->setData(itemIndex, value, role);
}

void TaskListModelProxy::removeItem(int id)
{
    QModelIndex itemIndex = index(id, 0);
    sourceModel()->removeRow(itemIndex.row());
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
