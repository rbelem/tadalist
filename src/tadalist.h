
#ifndef PASSWORDCARD_H
#define PASSWORDCARD_H

#include <QtQml/QQmlEngine>

class QQmlComponent;
class QQmlContext;
class TodoListModel;

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
};

#endif
