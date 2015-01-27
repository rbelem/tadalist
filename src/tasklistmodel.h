
#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QtCore/QAbstractListModel>

class TaskItem;

class TaskListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(TaskItemRoles)

public:
    enum TaskItemRoles {
        IdRole = Qt::UserRole + 1,
        TodoListIdRole,
        OrderRole,
        CompletedRole,
        TaskNameRole
    };

    TaskListModel(QObject * parent = 0);
    ~TaskListModel();

    int addItem(int todoListId);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void initRoles();

    QList<TaskItem *> m_items;
    QHash<int, QByteArray> m_roles;
};

#endif
