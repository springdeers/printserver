#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>
#include <QHashIterator>
#include <QString>
#include <QMutex>
#include <QJsonObject>
#include <QJsonDocument>
#include "myclient.h"

#include <QTextDocument>
#include <QTextFrame>
#include <QTextBlock>
#include <QTextEdit>
#include <QPrinterInfo>
#include <QDebug>
#include "JsonParse.h"
#include <QDateTime>

// JSON LATER
#define PRINTER_NAME_ONE     "HP MFP M436 PCL6"
#define PRINTER_NAME_TWO     "HP MFP M436 PCL7"
#define PRINTER_NAME_THREE   "HP MFP M436 PCL8"
#define PRINTER_NAME_FOUR    "HP MFP M436 PCL9"

#define PRINTER_ONE     0
#define PRINTER_TWO     1
#define PRINTER_THREE   2
#define PRINTER_FOUR    3
#define PRINTER_X       PRINTER_ONE

#define COM1            101
#define COM2            102
#define COM3            103
#define COM4            104


class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);

    void runServer(QHostAddress address, int port);

    QString InitAck_cmd_send();
    QString AuthAck_cmd_send();
    QString pong_cmd_send();
    QString PrintAck_cmd_send();

    QString make_checkSum(QString & str);

    void PrintDataProcess(MyClient* clientSocket, QString recvStr);
    unsigned char LongHToAscii(unsigned char* SrcBuff,unsigned char* DataBuff,unsigned int Len);
    void paiban(score_info_st score_info);
    void do_the_print(QPrinterInfo info, QTextEdit *edit, QString name);

signals:
    void signalReceiveDate(QString str);

public slots:
    void newConnection();
    void closedConnection();
    void ReceiveDataProcess();

private:
    QTcpServer *server;
    QHash<QTcpSocket*, MyClient*> clientsList;
    QHash<QTcpSocket*, MyClient*>::iterator i;
    QMutex mutex;

};

#endif // MYSERVER_H
