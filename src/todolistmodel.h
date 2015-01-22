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
        BulletSizeRole,
        CompletedRole,
        TodoListNameRole,
        TodoListDescriptionRole
    };

    TodoListModel(QObject * parent = 0);
    ~TodoListModel();

    Q_INVOKABLE TodoListItem *addItem();
    Q_INVOKABLE void updateItem(int id, int role, const QVariant &value);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void initRoles();

    QList<TodoListItem *> m_items;
    QHash<int, QByteArray> m_roles;
};

#endif
