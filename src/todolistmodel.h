#ifndef TODOLISTMODEL_H
#define TODOLISTMODEL_H

#include <QtCore/QAbstractListModel>

class TodoListItem;

class TodoListModel : public QAbstractListModel
{
    Q_OBJECT

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

    Q_INVOKABLE int addItem(const QString &name);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void initRoles();

    QList<TodoListItem *> m_items;
    QHash<int, QByteArray> m_roles;
};

#endif
