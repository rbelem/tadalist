
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
    invalidateFilter();
}

void TaskListModelProxy::addItem()
{
    TaskListModel *model = qobject_cast<TaskListModel *>(sourceModel());
    model->addItem(m_todoListId);
}

void TaskListModelProxy::updateItem(int id, const QVariant &value, int role)
{
    QModelIndex proxyIndex = index(id, 0);
    QModelIndex sourceIndex = mapToSource(proxyIndex);
    sourceModel()->setData(sourceIndex, value, role);
    invalidate();
    sort(0);
}

void TaskListModelProxy::removeItem(int id)
{
    QModelIndex proxyIndex = index(id, 0);
    QModelIndex sourceIndex = mapToSource(proxyIndex);
    sourceModel()->removeRow(sourceIndex.row());
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
    bool leftCompleted = left.data(TaskListModel::CompletedRole).toBool();
    bool rightCompleted = right.data(TaskListModel::CompletedRole).toBool();
    if (leftCompleted != rightCompleted) {
        return leftCompleted ? false : true;
    }

    int leftOrder = left.data(TaskListModel::OrderRole).toInt();
    int rightOrder = right.data(TaskListModel::OrderRole).toInt();
    if (leftOrder < rightOrder)
        return true;

    return false;
}
