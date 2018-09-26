#include <QCoreApplication>
#include <QString>

typedef struct
{
    QString trpe;
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




    return a.exec();
}
