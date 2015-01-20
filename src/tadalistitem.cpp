#include "tadalistitem.h"

TadaListItem::TadaListItem(QObject *parent)
    : QObject(parent)
    , m_id(-1)
    , m_bulletSize(-1)
    , m_completed(false)
    , m_name()
    , m_description()
{
}

TadaListItem::TadaListItem(TadaListItem *item, QObject *parent)
    : QObject(parent)
    , m_id(item->id())
    , m_bulletSize(item->bulletSize())
    , m_completed(item->completed())
    , m_name(item->name())
    , m_description(item->description())
{
}

void TadaListItem::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;

    emit idChanged();
}

void TadaListItem::setBulletSize(int id)
{
    if (m_bulletSize == id)
        return;

    m_bulletSize = id;

    emit bulletSizeChanged();
}

void TadaListItem::setCompleted(bool completed)
{
    if (m_completed == completed)
        return;

    m_completed = completed;

    emit completedChanged();
}

void TadaListItem::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;

    emit nameChanged();
}

void TadaListItem::setDescription(const QString &description)
{
    if (m_description == description)
        return;

    m_description = description;

    emit descriptionChanged();
}
