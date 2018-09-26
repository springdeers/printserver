#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "JsonParse.h"




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString str = "{\"type\":\"score\","
                  "\"code\":\"0\","
                  "\"cardid\":\"304068\","
                  "\"comid\":\"101\","
                  "\"name\":\"李明\","
                  "\"finalscore\":\"70.7\","
                  "\"credit_point\":\"9.4\","
                  "\"grade_point\":\"86.0\","
                  "\"class\":\"Good\","
                  "\"suggestion\":\"Good job!You can get better!\" ,"
                  "\"remains\": [{\"name\":\"垃圾分类\"},"
                                  "{\"name\":\"模拟报警\"},"
                                  "{\"name\":\"虚拟灭火\"},"
                                  "{\"name\":\"交通抢答\"},"
                                  "{\"name\":\"消防抢答\"},"
                                  "{\"name\":\"家庭药箱\"},"
                                  "{\"name\":\"球幕影院\"},"
                                  "{\"name\":\"地震小屋\"},"
                                  "{\"name\":\"烟雾逃生\"},"
                                  "{\"name\":\"消防飞行棋\"},"
                                  "{\"name\":\"VR宾馆火场逃生\"},"
                                  "{\"name\":\"VR隐患排查\"},"
                                  "{\"name\":\"VR电梯\"},"
                                  "{\"name\":\"VR地震\"},"
                                  "{\"name\":\"VR驾驶\"}]}";



    score_info_st score_info;
    QString errmsg;
    JsonParse jsonparse;
    if( jsonparse.Json_Parse(str,score_info,errmsg))
    {
        qDebug() << "score_info.name" <<score_info.name;
        qDebug() << "score_info.type" <<score_info.type;
        qDebug() << "score_info.code" <<score_info.code;
        qDebug() << "score_info.cardid" << score_info.cardid;
        qDebug() << "score_info.comid" << score_info.comid;
        qDebug() << "score_info.credit_point" << score_info.credit_point;
        qDebug() << "score_info.score_class" << score_info.score_class;
        qDebug() << "score_info.finalscore"<<score_info.finalscore;
        qDebug() << "score_info.suggestion"<<score_info.suggestion;
        qDebug() << "score_info.class"<<score_info.score_class;
//        qDebug() << "score_info.remain"<<score_info.remain_list;
        int size = score_info.remain_list.size();
        for(int i=0; i<size; i++)
        {
            qDebug() << score_info.remain_list.at(i);
        }
    }
    else
    {
        qDebug() << "json parse error!";
    }





    return a.exec();
}
