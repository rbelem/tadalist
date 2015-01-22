
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

int TodoListModel::addItem(const QString &name)
{
    int id = 0;

    if (rowCount()) {
        int id = m_items.at(0)->id();
        QList<TodoListItem *>::const_iterator itr;
        for (itr = m_items.constBegin(); itr != m_items.constEnd(); ++itr) {
            if (id < (*itr)->id())
                id = (*itr)->id();
        }

        id++;
    }

    TodoListItem *item = new TodoListItem();
    item->setId(id);
    item->setBulletSize(0);
    item->setCompleted(false);
    item->setName(name);
    item->setDescription("");

    beginInsertRows(QModelIndex(), m_items.count(), m_items.count());
    m_items.append(item);
    endInsertRows();

    return id;
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
