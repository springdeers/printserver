#include "JsonParse.h"


JsonParse::JsonParse()
{

}

// slot...HttpResultParseStore
bool JsonParse::Json_Parse(QString Json, score_info_st& score_info, QString& errmsg)
{
    qDebug() << "Json_Parse begin...";

    bool success = false;
    errmsg = "Json_Parse no error";

    int data_top,data_bottom;
    QString framehead= "$";
    QString frametail= "*";

    data_top=Json.indexOf(framehead,0);
    data_bottom=Json.indexOf(frametail,0);
    qDebug() << data_top << data_bottom;

    QString rec_data=Json.mid((data_top),(data_bottom));//去掉"*AA\r\n"字段
    qDebug() << "receive  data: " << rec_data;
    printf("----------------------");


    int len = rec_data.indexOf("{");
    qDebug() << "len = :" << len;
    QString buf=rec_data.right(rec_data.length()-len);

    qDebug()<<"buf :"<< buf;


    QByteArray data = buf.toUtf8();
    QJsonParseError jsonError;//Qt5新类
    QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);//Qt5新类
    if (jsonError.error == QJsonParseError::NoError)
    {

        if (json.isObject())
        {
            QJsonObject rootObj = json.object();

            //是否含有key  type
            if(rootObj.contains("type"))
            {
                QJsonValue value = rootObj.value("type");
                //判断是否是string类型
                if (value.isString()){
                    score_info.type = value.toString();
                }else{
                    errmsg = "type is not string!";
                }
            }else{
                errmsg = "type is not contains";
            }

            //是否含有key  code
            if(rootObj.contains("code"))
            {
                QJsonValue value = rootObj.value("code");
                //判断是否是string类型
                if (value.isString()){
                    score_info.code = value.toString();
                }else{
                    errmsg = "code is not string!";
                }
            }else{
                errmsg = "code is not contained!";
            }

            //是否含有key  cardid
            if(rootObj.contains("cardid"))
            {
                QJsonValue value = rootObj.value("cardid");
                //判断是否是string类型
                if (value.isString()){
                    score_info.cardid = value.toString();
                }else{
                    errmsg = "cardid is not string!";
                }
            }else{
                errmsg = "cardid is not contained!";
            }

            //是否含有key  comid
            if(rootObj.contains("comid"))
            {
                QJsonValue value = rootObj.value("comid");
                //判断是否是string类型
                if (value.isString()){
                    score_info.comid = value.toString();
                }else{
                    errmsg = "comid is not string!";
                }
            }else{
                errmsg = "comid is not contained!";
            }



            //是否含有key  name
            if(rootObj.contains("name"))
            {
                QJsonValue value = rootObj.value("name");
                //判断是否是string类型
                if (value.isString()){
                    score_info.name = value.toString();
                }else{
                    errmsg = "name is not string!";
                }
            }else{
                errmsg = "name is not contained!";
            }

            //是否含有key  finalscore
            if(rootObj.contains("finalscore"))
            {
                QJsonValue value = rootObj.value("finalscore");
                //判断是否是string类型
                if (value.isString()){
                    score_info.finalscore = value.toString();
                }else{
                    errmsg = "finalscore is not string!";
                }
            }else{
                errmsg = "finalscore is not contained!";
            }

            //是否含有key  credit_point
            if(rootObj.contains("credit_point"))
            {
                QJsonValue value = rootObj.value("credit_point");
                //判断是否是string类型
                if (value.isString()){
                    score_info.credit_point = value.toString();
                }else{
                    errmsg = "credit_point is not string!";
                }
            }else{
                errmsg = "credit_point is not contained!";
            }

            //是否含有key  grade_point
            if(rootObj.contains("grade_point"))
            {
                QJsonValue value = rootObj.value("grade_point");
                //判断是否是string类型
                if (value.isString()){
                    score_info.grade_point = value.toString();
                }else{
                    errmsg = "grade_point is not string!";
                }
            }else{
                errmsg = "grade_point is not contained!";
            }

            //是否含有key  class
            if(rootObj.contains("class"))
            {
                QJsonValue value = rootObj.value("class");
                //判断是否是string类型
                if (value.isString()){
                    score_info.score_class = value.toString();
                }else{
                    errmsg = "class is not string!";
                }
            }else{
                errmsg = "class is not contained!";
            }

            //是否含有key  suggestion
            if(rootObj.contains("suggestion"))
            {
                QJsonValue value = rootObj.value("suggestion");
                //判断是否是string类型
                if (value.isString()){
                    score_info.suggestion = value.toString();
                }else{
                    errmsg = "suggestion is not string!";
                }
            }else{
                errmsg = "suggestion is not contained!";
            }



            if(rootObj.contains("remainsobj"))
            {
                QJsonValue value = rootObj.value("remainsobj");
                if(value.isObject())
                {
                    QJsonObject obj = value.toObject();

                    //是否含有key  remains
                    if(obj.contains("remains"))
                    {
                        QJsonValue value = obj.value("remains");
                        //判断是否是string类型
                        if(value.isArray())
                        {
                            QJsonArray array = value.toArray();
                            int size = array.size();
                            score_info.remain_list.clear();
                            for(int i=0; i<size; i++)
                            {
                                QJsonValue arrayVal = array.at(i);
                                if(arrayVal.isNull())
                                {
                                    errmsg = "arrayVal is not null!";
                                }
                                if(arrayVal.isObject())
                                {
                                    QJsonObject arrayObj = arrayVal.toObject();
                                    if(arrayObj.contains("name"))
                                    {
                                        QJsonValue remainsVal = arrayObj.value("name");
                                        if(remainsVal.isString())
                                        {
                                            score_info.remain_list.append(remainsVal.toString());
                                            success = true;
                                        }else{
                                             errmsg = "remainsVal is not string";
                                        }
                                    }else{
                                        errmsg = "remainsObj name not contains!";
                                    }
                                }else{
                                    errmsg = "arrayVal is not object";
                                }
                            }

                        }else{
                            errmsg = "remains is not array";
                        }

                    }else{
                        errmsg = "remains is not contained!";
                    }

                }else{
                    errmsg = "remainsobj is not object";
                }
            }else{
                errmsg = "remainsobj is not contained";
            }




        }else{
            errmsg = "json is not object";
        }

    }else{
        errmsg = "json is error!";
    }

    qDebug() << errmsg;
    qDebug() << "Json_parse end...";
    return success;
}

