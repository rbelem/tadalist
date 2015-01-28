
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
    QModelIndex itemIndex = index(id, 0);
    sourceModel()->setData(itemIndex, value, role);
}

void TodoListModelProxy::removeItem(int id)
{
    QModelIndex itemIndex = index(id, 0);
    sourceModel()->removeRow(itemIndex.row());
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
