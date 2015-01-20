
#include "tasklistmodelproxy.h"

#include "tasklistmodel.h"

TaskListModelProxy::TaskListModelProxy(QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_tadaListId(-1)
{
}

TaskListModelProxy::TaskListModelProxy(const TaskListModelProxy &other)
    : QSortFilterProxyModel(0)
    , m_tadaListId(-1)
{
}

void TaskListModelProxy::setTadaListId(int id)
{
    if (id == m_tadaListId)
        return;

    m_tadaListId = id;
}

bool TaskListModelProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    int sourceTadaListId = index.data(TaskListModel::TodoListIdRole).toInt();
    if (sourceTadaListId == m_tadaListId)
        return true;

    return false;
}

bool TaskListModelProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return true;
}
