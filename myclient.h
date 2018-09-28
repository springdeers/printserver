#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class MyClient : public QObject
{
    Q_OBJECT
public:
    explicit MyClient(QObject *parent = 0);

    QTcpSocket *socket;

    void sendMsg(QString msg);
    QString recvMsg();

signals:

public slots:

private:
    QByteArray temp;

};

#endif // MYCLIENT_H
