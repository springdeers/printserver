#include "myclient.h"
#include <QTextCodec>

MyClient::MyClient(QObject *parent) :
    QObject(parent)
{
}

void MyClient::sendMsg(QString msg)
{
    qDebug()<<"send msg: "<<msg;
    socket->write(msg.toLocal8Bit().constData());
    socket->flush();
}

QString MyClient::recvMsg()
{
    while (socket->bytesAvailable())
    {
        temp = socket->readAll();
    }

    QTextCodec* pCodec = QTextCodec::codecForName("gbk");
    if(!pCodec) return false;
    QString qstr = pCodec->toUnicode(temp);
    qDebug() << qstr;

    return qstr;

}
