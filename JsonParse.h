#ifndef _JSONPARSE_H_
#define _JSONPARSE_H_
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>



class JsonParse
{
public:
    JsonParse();
    bool Json_Parse(QString str);
};

#endif // JSONPARSE_H
