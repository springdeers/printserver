#include "myserver.h"
#include <QPalette>
#include <QColor>

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void MyServer::newConnection()
{
    MyClient *client = new MyClient(this);
    client->socket = server->nextPendingConnection();
    connect(client->socket,SIGNAL(disconnected()),this,SLOT(closedConnection()));
    client->sendMsg("Connected!\n");
    qDebug() << client->socket << "Connected!";
    mutex.lock();
    clientsList.insert((client->socket), client);
    mutex.unlock();
    connect(client->socket,SIGNAL(readyRead()),this,SLOT(ReceiveDataProcess()));
}

void MyServer::closedConnection()
{
    qDebug() << sender() << "Closed connection!";
    qDebug() << clientsList;
    mutex.lock();
    clientsList.remove((QTcpSocket*)sender());
    mutex.unlock();
    sender()->deleteLater();
    qDebug() << clientsList;
}

void MyServer::runServer(QHostAddress address, int port)
{
    if(!server->listen(address,port))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started";
    }
}

void MyServer::ReceiveDataProcess()
{
    mutex.lock();
    QString sendstr;

    QString recvstr = clientsList[(QTcpSocket*)sender()]->recvMsg();
    MyClient* tempSocket = clientsList[(QTcpSocket*)sender()];


    int data_top,data_bottom;
    QString framehead= "$";
    QString frametail= "\r\n";

    data_top=recvstr.indexOf(framehead,0);
    data_bottom=recvstr.indexOf(frametail,0);

    QString net_data=recvstr.mid((data_top),(data_bottom-3));//去掉"*AA\r\n"字段
    qDebug() << "receive net data: " << net_data;


    // receive initsess
    if(net_data.startsWith("$initsess")){
         sendstr = InitAck_cmd_send();
         tempSocket->sendMsg(sendstr);

    }else
     // receive auth
    if (net_data.startsWith("$auth")) {
        sendstr = AuthAck_cmd_send();
        tempSocket->sendMsg(sendstr);
    }else
    // receive print
    if (net_data.startsWith("$print")) {
        PrintDataProcess(tempSocket,recvstr);

    }else
    // receive ping
    if(net_data.startsWith("$ping")){
        sendstr = pong_cmd_send();
        tempSocket->sendMsg(sendstr);
    }

    mutex.unlock();
}

void MyServer::PrintDataProcess(MyClient* clientSocket, QString recvstr)
{
    QString sendstr;
    // json 解析
    score_info_st score_info;
    QString errmsg;
    JsonParse jsonparse;
    bool success = jsonparse.Json_Parse(recvstr,score_info,errmsg);
    if(success)
    {
        paiban(score_info);
        qDebug() << "******************************";
        qDebug() << score_info.score_class;
        qDebug() << score_info.suggestion;
        qDebug() << "******************************";
    }

    sendstr = PrintAck_cmd_send(score_info);
    clientSocket->sendMsg(sendstr);
}

void MyServer::paiban(score_info_st score_info)
{
    QFont font_title(QFont("隶书", 30));
    QFont font_name(QFont("隶书", 20));
    QFont font_grade(QFont("隶书", 20));
    QFont font_items(QFont("楷体", 12));
    QFont font_addition(QFont("隶书", 20));
    QFont font_encourage(QFont("隶书", 20));

    //生成固定内容
//    QString current_date =QDateTime::currentDateTime().toString("yyyy年MM月dd日");
//    QString p_name =  QString("%1同学，恭喜您于%2完成了公共安全体验，成绩如下：").arg(score_info.name).arg(current_date);
////    QString p_score = QString("学分点：%1分   绩点： %2分  总分：%3分").arg(score_info.credit_point).arg(score_info.grade_point).arg(score_info.finalscore);
//    QString p_score = QString("总分：%1分").arg(score_info.finalscore);
//    QString p_items = QString("您此次未参与学习体验的项目有：");

    QString current_date =QDateTime::currentDateTime().toString("yyyy年MM月dd日");
    QString p_name =  QString("%1同学：").arg(score_info.name);
    QString p_score = QString("    恭喜您于%1完成了公共安全体验，总分：%2分,成绩%3，%4").arg(current_date).arg(score_info.finalscore).arg(score_info.score_class).arg(score_info.suggestion);
    QString p_items = QString("    您此次未体验的项目有：");

    for(int i=0; i<score_info.remain_list.count()-1; i++)
    {
        p_items.append(score_info.remain_list.at(i));
        p_items.append("、");
    }
    p_items.append(score_info.remain_list.at(score_info.remain_list.count()-1));
    p_items.append(QString("！"));
    p_items.append(QString("欢迎您下次再来！"));
    QString p_addition = QString("您的成绩优异，荣获公共安全明星奖！");
    QString p_encourage = QString("特发此证，以兹鼓励！");

    //开始排版
    QTextEdit* edit = new QTextEdit;
    QTextDocument* doc = edit->document();
    QTextCursor cursor = edit->textCursor();
    QTextFrame *root_frame = doc->rootFrame();
    QTextFrameFormat root_frame_format = root_frame->frameFormat();//创建框架格式
    root_frame_format.setMargin(250);
    root_frame->setFrameFormat(root_frame_format); //给框架使用格式

    QTextBlockFormat textBlockFormat;
    textBlockFormat.setTopMargin(15);//设置段前行距：15
    textBlockFormat.setBottomMargin(15);//设置段后行距：15
    textBlockFormat.setLeftMargin(20);//设置段左行距：20
    textBlockFormat.setRightMargin(20);//设置段右行距：20
    textBlockFormat.setLineHeight(100,QTextBlockFormat::ProportionalHeight);//设置行间距，单倍行距

    // 显示标题段落
    {
        // 字体格式
        QTextCharFormat char_format;
        char_format.setFont(font_title);
        //段落格式

        textBlockFormat.setAlignment(Qt::AlignHCenter);//对其方式：居中对其
        cursor.setBlockFormat(textBlockFormat);
        // 插入内容
        cursor.insertText("成绩单",char_format);
    }

    // 显示姓名段落
    {
        cursor.insertBlock();
        // 字体格式
        QTextCharFormat char_format;
        char_format.setFont(font_name);
        // 段落格式
        textBlockFormat.setAlignment(Qt::AlignLeft);//对其方式：两端对齐
        cursor.setBlockFormat(textBlockFormat);
        // 插入内容
        cursor.insertText(p_name,char_format);
    }

    // 显示成绩段落
    {
        cursor.insertBlock();
        // 字体格式
        QTextCharFormat char_format;
        char_format.setFont(font_grade);
        // 段落格式
        textBlockFormat.setAlignment(Qt::AlignLeft);//对其方式：居中对齐
        cursor.setBlockFormat(textBlockFormat);
        // 插入内容
        cursor.insertText(p_score,char_format);
    }

    // 显示未体验项目段落
    {
        cursor.insertBlock();
        // 字体格式
        QTextCharFormat char_format;
        char_format.setFont(font_items);

        // 段落格式
        textBlockFormat.setAlignment(Qt::AlignJustify);//对其方式：两端对齐
        cursor.setBlockFormat(textBlockFormat);
        // 插入内容
        cursor.insertText(p_items,char_format);
    }

    // 若成绩大于90分，则显示附加段落段落
    {
       int score = score_info.finalscore.toDouble();
       if(score >= 70)
       {
           cursor.insertBlock();
           // 字体格式
           QTextCharFormat char_format;
           char_format.setFont(font_addition);
           QColor color("red");
           char_format.setForeground(color);

           // 段落格式
           textBlockFormat.setAlignment(Qt::AlignRight);//对其方式：右对齐
           cursor.setBlockFormat(textBlockFormat);
           // 插入内容
           cursor.insertText(p_addition,char_format);
       }
    }

    // 显示鼓励段落
    {
        cursor.insertBlock();
        // 字体格式
        QTextCharFormat char_format;
        char_format.setFont(font_encourage);
        // 段落格式
        textBlockFormat.setAlignment(Qt::AlignRight);//对其方式：右对齐
        cursor.setBlockFormat(textBlockFormat);
        // 插入内容
        cursor.insertText(p_encourage,char_format);
    }


    // 打印
    QPrinterInfo printer_info_array[4];
    QList<QPrinterInfo> printer_info_list = QPrinterInfo::availablePrinters();


    int printer_info_list_size = printer_info_list.size();
    for(int i=0;i<printer_info_list_size;i++)
    {
        if(printer_info_list.at(i).printerName() == PRINTER_NAME_ONE)
        {
            printer_info_array[PRINTER_ONE] = printer_info_list.at(i);
        }
        else if(printer_info_list.at(i).printerName() == PRINTER_NAME_TWO)
        {
            printer_info_array[PRINTER_TWO] = printer_info_list.at(i);
        }
        else if(printer_info_list.at(i).printerName() == PRINTER_NAME_THREE)
        {
            printer_info_array[PRINTER_THREE] = printer_info_list.at(i);
        }
        else if(printer_info_list.at(i).printerName() == PRINTER_NAME_FOUR)
        {
            printer_info_array[PRINTER_FOUR] = printer_info_list.at(i);
        }
    }


    int comid = score_info.comid.toInt();
    switch (comid) {
    case COM1:
            do_the_print(printer_info_array[PRINTER_ONE],edit,score_info.name);
        break;
    case COM2:
            do_the_print(printer_info_array[PRINTER_TWO],edit,score_info.name);
        break;
    case COM3:
            do_the_print(printer_info_array[PRINTER_THREE],edit,score_info.name);
        break;
    case COM4:
            do_the_print(printer_info_array[PRINTER_FOUR],edit,score_info.name);
        break;
    default:
            do_the_print(printer_info_array[PRINTER_X],edit,score_info.name);
        break;
    }
}




void MyServer::do_the_print(QPrinterInfo info, QTextEdit *edit, QString name)
{
    QPrinter p(info);
    qDebug() << p.printerName();
    p.setOrientation(QPrinter::Landscape);   //设置为横向
    p.setPaperSize(QPrinter::B5);            //设置纸张为B5
    QTextDocument *td = edit->document();

    QString current_date =QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString path = QString("E:\\ScorePrint\\%1 - %2.pdf").arg(current_date).arg(name);
    p.setOutputFileName(path);
    td->print(&p);
}


QString MyServer::InitAck_cmd_send()
{
    QJsonObject obj;

    obj.insert("role", "printsvr");
    obj.insert("rslt", "ok");
    obj.insert("error", "");
    obj.insert("seqno", getseqno());

    QJsonDocument document;
    document.setObject(obj);
    QString json(document.toJson(QJsonDocument::Compact));
    json="$initack,printsvr,backcard,"+json;

    QString check_data = make_checkSum(json);//计算校验核
    json=json+check_data;
    QByteArray json_out = json.toUtf8();

    return json_out;
}

QString MyServer::pong_cmd_send()
{
    QJsonObject obj;

    obj.insert("from", "printsvr");
    obj.insert("to", "backcard");

    QJsonDocument document;
    document.setObject(obj);
    QString json(document.toJson(QJsonDocument::Compact));
    json="$pong,"+json;

    QString check_data = make_checkSum(json);//计算校验核
    json=json+check_data;
    QByteArray json_out = json.toUtf8();

    return json_out;
}

QString MyServer::AuthAck_cmd_send()
{
    QJsonObject obj;

    obj.insert("rslt", "ok");
    obj.insert("error", "");
    obj.insert("seqno", getseqno());

    QJsonDocument document;
    document.setObject(obj);
    QString json(document.toJson(QJsonDocument::Compact));
    json="$authack,printsvr,backcard,"+json;

    QString check_data = make_checkSum(json);//计算校验核
    json=json+check_data;
    QByteArray json_out = json.toUtf8();

    return json_out;
}

QString MyServer::PrintAck_cmd_send(score_info_st score_info)
{
    QJsonObject obj;

    obj.insert("cardid", score_info.cardid);
    obj.insert("comid", score_info.comid);
    obj.insert("name", score_info.name);
    obj.insert("rslt", "ok");
    obj.insert("error", "");
    obj.insert("seqno", getseqno());

    QJsonDocument document;
    document.setObject(obj);
    QString json(document.toJson(QJsonDocument::Compact));
    json="$printack,printsvr,backcard,"+json;

    QString check_data = make_checkSum(json);//计算校验核
    json=json+check_data;
    QByteArray json_out = json.toUtf8();

    return json_out;
}

QString MyServer::make_checkSum(QString & str)
{
//    char high_byte,low_byte,check_resust;
    unsigned char checkSum_data[2];
    QString mask_str;

//    qDebug("Do string checksum.");
//    qDebug()<<str;
   //"$BDBSI,02,03,2,4,3*62"  the str has delate \r\n
    QByteArray data = str.toUtf8();
    unsigned char mask = data[1];//the data[0]=$
    int datalen=data.length();
    for (int i = 2; i <datalen; i++) {
        mask ^= data[i];
    }
    LongHToAscii(&mask,checkSum_data,1);
    mask_str.clear();
    mask_str+=checkSum_data[0];
    mask_str+=checkSum_data[1];
    mask_str="*"+mask_str+"\r\n";
    return mask_str;
}

unsigned char MyServer::LongHToAscii(unsigned char* SrcBuff,unsigned char* DataBuff,unsigned int Len)
{
   unsigned int		i;

   for (i=0; i<Len; i++)
   {
       if (((SrcBuff[i]>>4)>=0) && ((SrcBuff[i]>>4)<=9))
       {
           DataBuff[i*2] = (SrcBuff[i]>>4) + 48;
       }
       else if (((SrcBuff[i]>>4)>=10) && ((SrcBuff[i]>>4)<=15))
       {
           DataBuff[i*2] = (SrcBuff[i]>>4) + 55;
       }
       else
       {
           return 0;
       }
       if (((SrcBuff[i]&0xF)>=0) && ((SrcBuff[i]&0xF)<=9))
       {
           DataBuff[i*2+1] = (SrcBuff[i]&0xF) + 48;
       }
       else if (((SrcBuff[i]&0xF)>=10) && ((SrcBuff[i]&0xF)<=15))
       {
           DataBuff[i*2+1] = (SrcBuff[i]&0xF) + 55;
       }
       else
       {
           return 0;
       }
   }
   return 1;
}

int MyServer::getseqno()
{
    if(this->seqno>=65535)
    {
        this->seqno = 1;
    }else
    {
        this->seqno++;
    }
    return this->seqno;
}
