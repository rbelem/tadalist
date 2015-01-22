
#include "todolistitem.h"
#include "todolistmodel.h"

TodoListModel::TodoListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    initRoles();
}

TodoListModel::~TodoListModel()
{
}

QVariant TodoListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count())
        return QVariant();

    const TodoListItem *item = m_items[index.row()];

    if (role == IdRole)
        return item->id();

    if (role == BulletSizeRole)
        return item->bulletSize();

    if (role == CompletedRole)
        return item->completed();

    if (role == TodoListNameRole)
        return item->name();

    if (role == TodoListDescriptionRole)
        return item->description();

    return QVariant();
}

int TodoListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_items.count();
}

QHash<int, QByteArray> TodoListModel::roleNames() const
{
    return m_roles;
}

void TodoListModel::initRoles()
{
    m_roles[IdRole] = "todoListId";
    m_roles[BulletSizeRole] = "bulletSize";
    m_roles[CompletedRole] = "todoListCompleted";
    m_roles[TodoListNameRole] = "todoListName";
    m_roles[TodoListDescriptionRole] = "todoListDescription";
}
