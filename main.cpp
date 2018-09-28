#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "JsonParse.h"
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QDateTime>
#include <myserver.h>
#include <myclient.h>




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer mServer;
    mServer.runServer(QHostAddress::Any, 7126);

    return a.exec();
}
