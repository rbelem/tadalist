
#include "todolistmodelproxy.h"

#include "todolistitem.h"
#include "todolistmodel.h"

TodoListModelProxy::TodoListModelProxy(QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_todoListType(UnfinishedTodoList)
{
}

TodoListModelProxy::TodoListModelProxy(const TodoListModelProxy &other)
    : QSortFilterProxyModel(0)
    , m_todoListType(UnfinishedTodoList)
{
}

void TodoListModelProxy::setTodoListType(TodoListTypes type)
{
    if (type == m_todoListType)
        return;

    m_todoListType = type;
}

TodoListItem *TodoListModelProxy::addItem()
{
    TodoListModel *model = qobject_cast<TodoListModel *>(sourceModel());
    return model->addItem();
}

void TodoListModelProxy::updateItem(int id, const QVariant &value, int role)
{
    QModelIndex proxyIndex = index(id, 0);
    QModelIndex sourceIndex = mapToSource(proxyIndex);
    sourceModel()->setData(sourceIndex, value, role);
}

void TodoListModelProxy::removeItem(int id)
{
    QModelIndex proxyIndex = index(id, 0);
    QModelIndex sourceIndex = mapToSource(proxyIndex);
    sourceModel()->removeRow(sourceIndex.row());
}

bool TodoListModelProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex itemIndex = sourceModel()->index(source_row, 0, source_parent);
    bool completed = itemIndex.data(TodoListModel::CompletedRole).toBool();

    if ((m_todoListType == UnfinishedTodoList) && (completed == false))
        return true;

    if ((m_todoListType == CompletedTodoList) && (completed == true))
        return true;

    return false;
}

bool TodoListModelProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return true;
}
