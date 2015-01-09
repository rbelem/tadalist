#include <QtGui/QGuiApplication>

#include "tadalist.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TadaList view;

    return app.exec();
}
