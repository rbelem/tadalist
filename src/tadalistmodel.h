
#ifndef TADALISTMODEL_H
#define TADALISTMODEL_H

#include <QtCore/QAbstractListModel>

class TadaListItem;

class TadaListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum TadaItemRoles {
        IdRole = Qt::UserRole + 1,
        BulletSizeRole,
        CompletedRole,
        TadaListNameRole,
        TadaListDescriptionRole
    };

    TadaListModel(QObject * parent = 0);
    ~TadaListModel();

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

private:
    void initRoles();

    QList<TadaListItem *> m_items;
    QHash<int, QByteArray> m_roles;
};

#endif
