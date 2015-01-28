
#ifndef PASSWORDCARD_H
#define PASSWORDCARD_H

#include <QtQml/QQmlEngine>

class QQmlComponent;
class QQmlContext;
class TaskListModel;
class TaskListModelProxy;
class TodoListModel;
class TodoListModelProxy;

class TadaList : public QQmlEngine
{
    Q_OBJECT

public:
    TadaList(QObject *parent = 0);
    ~TadaList();

public slots:
    void onQuit();

private:
    QQmlContext *m_context;
    QQmlComponent *m_component;

    TodoListModel *m_todoListModel;
    TodoListModelProxy *m_todoListModelCompleted;
    TodoListModelProxy *m_todoListModelUnfinished;
    TaskListModel *m_taskListModel;
    TaskListModelProxy *m_taskListModelProxy;
};

#endif
