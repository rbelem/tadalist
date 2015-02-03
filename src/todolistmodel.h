#ifndef TODOLISTMODEL_H
#define TODOLISTMODEL_H

#include <QtCore/QAbstractListModel>

class TodoListItem;

class TodoListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(TodoItemRoles)

public:
    enum TodoItemRoles {
        IdRole = Qt::UserRole + 1,
        TasksLeftRole,
        CompletedRole,
        TodoListNameRole,
        TodoListDescriptionRole
    };

    TodoListModel(QObject * parent = 0);
    ~TodoListModel();

    TodoListItem *addItem();
    QModelIndex indexById(int id) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void initRoles();

    QList<TodoListItem *> m_items;
    QHash<int, QByteArray> m_roles;
};

#endif
