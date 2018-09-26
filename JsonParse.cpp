#include "JsonParse.h"


JsonParse::JsonParse()
{

}
/*
// slot...HttpResultParseStore
bool JsonParse::Json_Parse(QString str)
{
    qDebug() << "Json_Parse begin...";

    bool success = false;
    QString data1;

    QString buf = str;
    QByteArray data = buf.toUtf8();

    QJsonParseError jsonError;//Qt5新类
    QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);//Qt5新类
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (json.isObject())
        {
            QJsonObject rootObj = json.object();
            //是否含有key  rslt
            if(rootObj.contains("rslt"))
            {
                QJsonValue value = rootObj.value("bdid");
                //判断是否是string类型
                if (value.isString())
                {
                    data1 = value.toString();
                    if(data1=="ok")
                    {

                        if (rootObj.contains("data"))//是否包含指定的key
                        {
                            QJsonValue value = rootObj.value("data");//得到键值data所对应的数值

                            if(value.isArray())
                            {
                                QJsonArray array = value.toArray();
                                //int size = array.size();

                                QJsonValue arrayVal = array.at(0);
                                if(arrayVal.isNull())
                                {
                                    // arrayVal is null
                                    ret = "arrayVal is null";
                                }
                                QJsonObject arrayobj = arrayVal.toObject();


                                // AAAAAAAA    data parse  AAAAAAAA
                                // arrayobj is our obj, it contains every point we need such as id and name etc.

                                // data.id  --> taskid
                                if(arrayobj.contains("id"))
                                {
                                    QJsonValue idVal = arrayobj.value("id");
                                    if(idVal.isDouble())
                                    {
                                        data1 = QString::number(idVal.toVariant().toInt(),10);

                                        ret = "id ok";
                                    }
                                    else
                                    {
                                        ret = "idVal is string";
                                    }
                                }
                                else
                                {
                                    // id not contained
                                    ret = "id not contained";
                                }


                                // data.name:"押运"  -> taskname
                                if(arrayobj.contains("name"))
                                {
                                    QJsonValue val = arrayobj.value("name");
                                    if(val.isString())
                                    {
//                                        m_ui_param->task_name = val.toString();
                                        ret = "name ok";
                                    }
                                    else
                                    {
                                        ret = "name is not string";
                                    }
                                }
                                else
                                {
                                    ret = "name not contained";
                                }

                                // "from1":"海一",
                                if(arrayobj.contains("from1"))
                                {
                                    QJsonValue val = arrayobj.value("from1");
                                    if(val.isString())
                                    {
                                        m_ui_param->from = val.toString();
                                        ret = "from1 ok";
                                    }
                                    else
                                    {
                                        ret = "from1 is not string";
                                    }
                                }
                                else
                                {
                                    ret = "from1 not contained";
                                }



                                //"to1":"空二",
                                if(arrayobj.contains("to1"))
                                {
                                    QJsonValue val = arrayobj.value("to1");
                                    if(val.isString())
                                    {
//                                        m_ui_param->to = val.toString();
                                        ret = "to1 ok";
                                    }
                                    else
                                    {
                                        ret = "to1 is not string";
                                    }
                                }
                                else
                                {
                                    ret = "to1 not contained";
                                }

                                //"timestart":"2018-06-03 24:11:11",
                                if(arrayobj.contains("timestart"))
                                {
                                    QJsonValue val = arrayobj.value("timestart");
                                    if(val.isString())
                                    {
//                                        m_ui_param->task_acquire_time = val.toString();
                                        ret = "timestart ok";
                                    }
                                    else
                                    {
                                        ret = "timestart is not string";
                                    }
                                }
                                else
                                {
                                    ret = "timestart not contained";
                                }

                                //"timeend":"2018-06-05 24:11:11",
                                if(arrayobj.contains("timeend"))
                                {
                                    QJsonValue val = arrayobj.value("timeend");
                                    if(val.isString())
                                    {
//                                        m_ui_param->task_plan_finish_time = val.toString();
                                        ret = "timeend ok";
                                    }
                                    else
                                    {
                                        ret = "timeend is not string";
                                    }
                                }
                                else
                                {
                                    ret = "timeend not contained";
                                }



                                //"maxmisstime":"24"
                                if(arrayobj.contains("maxmisstime"))
                                {
                                    QJsonValue val = arrayobj.value("maxmisstime");
                                    if(val.isString())
                                    {
//                                        m_ui_param->task_allow_offset_time = val.toString();
                                        ret = "maxmisstime ok";
                                    }
                                    else
                                    {
                                        ret = "maxmisstime is not string";
                                    }
                                }
                                else
                                {
                                    ret = "maxmisstime not contained";
                                }


                                if(arrayobj.contains("executor_code"))
                                {
                                    QJsonValue val = arrayobj.value("executor_code");
                                    if(val.isString())
                                    {
//                                        /m_ui_param->executor_code = val.toString();
                                        ret = "executor_code ok";
                                    }
                                    else
                                    {
                                        ret = "executor_code is not string";
                                    }
                                }
                                else
                                {
                                    ret = "executor_code not contained";
                                }

                                // data."reportfreq":10
                                if(arrayobj.contains("reportfreq"))
                                {
                                    QJsonValue val = arrayobj.value("reportfreq");
                                    if(val.isDouble())
                                    {
                                        // QString::number(val.toVariant().toInt(),10);
                                        int temp = (val.toInt());
                                        if(temp <=0)  temp = 10;
//                                        m_ui_param->reportfreq = temp*1000;
                                        ret = "reportfreq ok";
                                        ret = "ok";
                                    }
                                    else
                                    {
                                        ret = "reportfreq is not double";
                                    }
                                }
                                else
                                {
                                    ret = "reportfreq not contained";
                                }


                                // "executeor" 数组
                                if(arrayobj.contains("executeor"))
                                {
                                    QJsonValue val = arrayobj.value("executeor");
                                    if(val.isArray())
                                    {
                                        QJsonArray array = val.toArray();
                                        int size = array.size();
                                        for(int i=0; i<size; i++)
                                        {
                                            QJsonValue arrayVal = array.at(i);
                                            if(arrayVal.isNull)
                                            {
                                                ret = "arrayVal is NULL";
                                            }
                                            QJsonObject executeor_obj = arrayVal.toObject();
                                            if(executeor_obj.contains("code"))
                                            {
                                                QJsonValue codeVal = executeor_obj.value("code");
                                                if(codeVal.isString())
                                                {
                                                    //保存执行人代号
                                                    // executeor_List[size] = codeVal.toString();
                                                    ret = "ok";
                                                }
                                                else
                                                {
                                                    ret = "codeVal is not string";
                                                }
                                            }
                                            else
                                            {
                                                ret = "executeor code not contained";
                                            }
                                        }
                                    }
                                    else
                                    {
                                        ret = "executeor is not array";
                                    }
                                }
                                else
                                {
                                    ret = "executeor not contained";
                                }
                            }
                            else
                            {
                                ret = "data is not array";
                            }
                        }
                        else
                        {
                            ret = "data is not string";
                        }
                    }
                    else
                    {
                        // rslt error
                        ret = "rslt error";
                    }
                }
                else
                {
                    // rslt is not string
                    ret = "rslt is not string";
                }
            }
            else
            {
                ret = "rslt is not contained";
            }
        }
        else
        {
            // json is not object
            ret = "json is not object";
        }
    }
    else
    {
        // json format error
        ret = "json format error";
    }

    qDebug() << ret;
    qDebug() << "HttpResultParseStore end...";
    return ret;
}

*/
