
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

TodoListItem *TodoListModel::addItem()
{
    int id = 1;

    if (rowCount()) {
        QList<TodoListItem *>::const_iterator itr;
        for (itr = m_items.constBegin(); itr != m_items.constEnd(); ++itr) {
            if (id < (*itr)->id())
                id = (*itr)->id();
        }

        id++;
    }

    TodoListItem *item = new TodoListItem(this);
    item->setId(id);
    item->setTasksLeft(0);
    item->setCompleted(false);
    item->setName(QString(QLatin1String("Todo List %1")).arg(id));
    item->setDescription("");

    beginInsertRows(QModelIndex(), m_items.count(), m_items.count());
    m_items.append(item);
    endInsertRows();

    return item;
}

QModelIndex TodoListModel::indexById(int id) const
{
    int i;
    QList<TodoListItem *>::const_iterator itr;
    for (i = 0, itr = m_items.constBegin(); itr != m_items.constEnd(); ++i, ++itr) {
        if (id == (*itr)->id())
            return index(i, 0);
    }

    return QModelIndex();
}

QVariant TodoListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count())
        return QVariant();

    TodoListItem *item = m_items.at(index.row());

    if (role == IdRole)
        return item->id();

    if (role == TasksLeftRole)
        return item->tasksLeft();

    if (role == CompletedRole)
        return item->completed();

    if (role == TodoListNameRole)
        return item->name();

    if (role == TodoListDescriptionRole)
        return item->description();

    return QVariant();
}

bool TodoListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() < 0 || index.row() >= m_items.count())
        return false;

    TodoListItem *item = m_items[index.row()];

    if (item == NULL)
        return false;

    QVector<int> changedRoles;
    changedRoles.append(role);

    if (role == IdRole)
        item->setId(value.toInt());
    else if (role == TasksLeftRole)
        item->setTasksLeft(value.toInt());
    else if (role == CompletedRole)
        item->setCompleted(value.toBool());
    else if (role == TodoListNameRole)
        item->setName(value.toString());
    else if (role == TodoListDescriptionRole)
        item->setDescription(value.toString());
    else
        return false;

    emit dataChanged(index, index, changedRoles);

    return true;
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
    m_roles[TasksLeftRole] = "tasksLeft";
    m_roles[CompletedRole] = "todoListCompleted";
    m_roles[TodoListNameRole] = "todoListName";
    m_roles[TodoListDescriptionRole] = "todoListDescription";
}
