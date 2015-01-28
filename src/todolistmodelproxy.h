
#ifndef TODOLISTMODELPROXY_H
#define TODOLISTMODELPROXY_H

#include <QtCore/QSortFilterProxyModel>

class TodoListItem;

class TodoListModelProxy : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_ENUMS(TodoListTypes)

public:
    enum TodoListTypes {
        UnfinishedTodoList,
        CompletedTodoList
    };

    TodoListModelProxy(QObject *parent = 0);
    TodoListModelProxy(const TodoListModelProxy &other);

    Q_INVOKABLE void setTodoListType(TodoListTypes type);
    Q_INVOKABLE TodoListItem *addItem();
    Q_INVOKABLE void updateItem(int id, const QVariant &value, int role);
    Q_INVOKABLE void removeItem(int id);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    TodoListTypes m_todoListType;
};

#endif
