
#include "tadalistitem.h"
#include "tadalistmodel.h"

TadaListModel::TadaListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    initRoles();
}

TadaListModel::~TadaListModel()
{
}

QVariant TadaListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count())
        return QVariant();

    const TadaListItem *item = m_items[index.row()];

    if (role == IdRole)
        return item->id();

    if (role == BulletSizeRole)
        return item->bulletSize();

    if (role == CompletedRole)
        return item->completed();

    if (role == TadaListNameRole)
        return item->name();

    if (role == TadaListDescriptionRole)
        return item->description();

    return QVariant();
}

int TadaListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_items.count();
}

QHash<int, QByteArray> TadaListModel::roleNames() const
{
    return m_roles;
}

void TadaListModel::initRoles()
{
    m_roles[IdRole] = "tadaListId";
    m_roles[BulletSizeRole] = "bulletSize";
    m_roles[CompletedRole] = "tadaListCompleted";
    m_roles[TadaListNameRole] = "tadaListName";
    m_roles[TadaListDescriptionRole] = "tadaListDescription";
}
