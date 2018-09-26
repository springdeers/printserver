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

typedef struct
{
    QString type;
    QString code;
    QString cardid;
    QString comid;
    QString name;
    QString finalscore;
    QString credit_point;
    QString grade_point;
    QString score_class;
    QString suggestion;
    QStringList remain_list;

}score_info_st, *score_info_t;


class JsonParse
{
private:
    score_info_st score_info;
public:
    JsonParse();
    bool Json_Parse(QString Json, score_info_st &score_info, QString& errmsg);
};

#endif // JSONPARSE_H
