#include "taskitem.h"

TaskItem::TaskItem(QObject *parent)
    : QObject(parent)
    , m_id(-1)
    , m_todoListId(-1)
    , m_order(0)
    , m_completed(false)
    , m_name()
{
}

TaskItem::TaskItem(TaskItem *item, QObject *parent)
    : QObject(parent)
    , m_id(item->id())
    , m_todoListId(item->todoListId())
    , m_order(item->order())
    , m_completed(item->completed())
    , m_name(item->name())
{
}

void TaskItem::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;

    emit idChanged();
}

void TaskItem::setTodoListId(int id)
{
    if (m_todoListId == id)
        return;

    m_todoListId = id;

    emit todoListIdChanged();
}

void TaskItem::setOrder(int order)
{
    if (m_order == order)
        return;

    m_order = order;

    emit orderChanged();
}

void TaskItem::setCompleted(bool completed)
{
    if (m_completed == completed)
        return;

    m_completed = completed;

    emit completedChanged();
}

void TaskItem::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;

    emit nameChanged();
}
