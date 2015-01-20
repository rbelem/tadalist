#ifndef TASKITEM_H
#define TASKITEM_H

#include <QtCore/QObject>

class TaskItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged);
    Q_PROPERTY(int todoListId READ todoListId WRITE setTodoListId NOTIFY todoListIdChanged);
    Q_PROPERTY(int order READ order WRITE setOrder NOTIFY orderChanged);
    Q_PROPERTY(bool completed READ completed WRITE setCompleted NOTIFY completedChanged);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);

public:
    TaskItem(QObject *parent = 0);
    TaskItem(TaskItem *sourceItem, QObject *parent = 0);

    void setId(int id);
    int id() const { return m_id; }

    void setTodoListId(int id);
    int todoListId() const { return m_todoListId; }

    void setOrder(int order);
    int order() const { return m_order; }

    void setCompleted(bool completed);
    bool completed() const { return m_completed; }

    void setName(const QString &name);
    QString name() const { return m_name; }

signals:
    void idChanged();
    void todoListIdChanged();
    void orderChanged();
    void completedChanged();
    void nameChanged();

private:
    int m_id;
    int m_todoListId;
    int m_order;
    bool m_completed;
    QString m_name;
};

#endif
