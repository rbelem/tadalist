#ifndef TODOLISTITEM_H
#define TODOLISTITEM_H

#include <QtCore/QObject>

class TodoListItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged);
    Q_PROPERTY(int bulletSize READ bulletSize WRITE setBulletSize NOTIFY bulletSizeChanged);
    Q_PROPERTY(bool completed READ completed WRITE setCompleted NOTIFY completedChanged);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QString description READ description WRITE setName NOTIFY nameChanged);

public:
    TodoListItem(QObject *parent = 0);
    TodoListItem(TodoListItem *sourceItem, QObject *parent = 0);

    void setId(int id);
    int id() const { return m_id; }

    void setBulletSize(int id);
    int bulletSize() const { return m_bulletSize; }

    void setCompleted(bool completed);
    bool completed() const { return m_completed; }

    void setName(const QString &name);
    QString name() const { return m_name; }

    void setDescription(const QString &description);
    QString description() const { return m_description; }

signals:
    void idChanged();
    void bulletSizeChanged();
    void completedChanged();
    void nameChanged();
    void descriptionChanged();

private:
    int m_id;
    int m_bulletSize;
    bool m_completed;
    QString m_name;
    QString m_description;
};

#endif
