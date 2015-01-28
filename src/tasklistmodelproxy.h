
#ifndef TASKLISTMODELPROXY_H
#define TASKLISTMODELPROXY_H

#include <QtCore/QSortFilterProxyModel>

class TaskListModelProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    TaskListModelProxy(QObject *parent = 0);
    TaskListModelProxy(const TaskListModelProxy &other);

    Q_INVOKABLE void setTodoListId(int id);
    Q_INVOKABLE void addItem();
    Q_INVOKABLE void updateItem(int id, const QVariant &value, int role);
    Q_INVOKABLE void removeItem(int id);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    int m_todoListId;
};

#endif
