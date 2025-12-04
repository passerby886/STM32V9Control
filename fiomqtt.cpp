#include "fiomqtt.h"
#include "ui_fiomqtt.h"

FIOMqtt::FIOMqtt(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FIOMqtt)
{
    ui->setupUi(this);
    this->initUi();
}

FIOMqtt::~FIOMqtt()
{
    delete ui;
}

void FIOMqtt::initUi()
{

    // 设置 label 的字体颜色为白色
    ui->label_server->setStyleSheet("color: white;");
    ui->label_upload->setStyleSheet("color: white;");
    ui->label_download->setStyleSheet("color: white;");


    ui->pushButton_in1->setPicture(QString::fromUtf8(":/images/io1off.png"));
    ui->pushButton_in2->setPicture(QString::fromUtf8(":/images/io2off.png"));
    ui->pushButton_in3->setPicture(QString::fromUtf8(":/images/io3off.png"));
    ui->pushButton_in4->setPicture(QString::fromUtf8(":/images/io4off.png"));

    ui->pushButton_relay1->setPicture(QString::fromUtf8(":/images/relay1off.png"));
    ui->pushButton_relay2->setPicture(QString::fromUtf8(":/images/relay2off.png"));
    ui->pushButton_relay3->setPicture(QString::fromUtf8(":/images/relay3off.png"));
    ui->pushButton_relay4->setPicture(QString::fromUtf8(":/images/relay4off.png"));



    ui->pushButton_server->setStyleSheet(
        "QPushButton { border-radius: 5px;background-color: white; }" // 正常状态
        "QPushButton:pressed { background-color: #5354cb; }"          // 按压状态
        "QPushButton:checked { background-color: #5354cb; }"          // 选中状态
        );

    ui->pushButton_server->setCheckable(true);
    ui->pushButton_relay1->setCheckable(true);
    ui->pushButton_relay2->setCheckable(true);
    ui->pushButton_relay3->setCheckable(true);
    ui->pushButton_relay4->setCheckable(true);
}


void FIOMqtt::stateChanged_slot(QMqttClient::ClientState state)
{
    qDebug() << "ClientState:" << state;
    if(state ==  QMqttClient::Connecting ) // 正在连接
    {
        qDebug() << "mqttclient connectting mqttserver...";
        ui->comboBox_server->setEnabled(false); // 不可操作
        ui->comboBox_download->setEnabled(false); // 不可操作
        ui->comboBox_upload->setEnabled(false); // 不可操作
    }
    else if(state ==  QMqttClient::Connected ) // 已经连接
    {
        qDebug() << "mqttclient connected mqttserver";
        ui->pushButton_server->setText(tr("断开连接"));

        // 订阅主题
        QMqttSubscription *sub =  mqttclient->subscribe(ui->comboBox_upload->currentText());
        if(sub) // 不为0， 就成功了
        {
            qDebug() << "mqttclient subscribe sucessed";
        }
        else
        {
            qDebug() << "mqttclient subscribe failed";
        }


    }
    else if(state ==  QMqttClient::Disconnected ) // 断开连接
    {
        qDebug() << "mqttclient disconnected mqttserver";
        ui->pushButton_server->setText(tr("连接服务器"));
        ui->comboBox_server->setEnabled(true); // 可操作
        ui->comboBox_download->setEnabled(true); // 可操作
        ui->comboBox_upload->setEnabled(true); // 可操作

        // 取消订阅主题
        mqttclient->unsubscribe(ui->comboBox_upload->currentText());
        qDebug() << "mqttclient unsubscribe sucessed";

        if(mqttclient != nullptr)
        {
            mqttclient->deleteLater();
            mqttclient = nullptr;
        }
    }

}

void FIOMqtt::messageReceived_slot(const QByteArray &message, const QMqttTopicName &topic )
{
    // 判断主题消息
    if(topic.name() == ui->comboBox_upload->currentText()) // 主题匹配
    {
        qDebug() << "topic.name()="  << topic.name();
        qDebug() << "message="  << message;
    }
    // 把message 转换成 json字符串
    QJsonDocument jsonDocument = QJsonDocument::fromJson(message) ;
    if(!jsonDocument.isNull()) // 判断不为空
    {
        QJsonObject jsonObject =  jsonDocument.object() ; // 解析一个json对象， 一个json对象就是一个json字符串
        QJsonValue jsonIN1_4 =  jsonObject.value("IN1-4"); // 获取温度的值

        if(!jsonIN1_4.isNull())
        {
            quint8 in1_4  = jsonIN1_4.toInt();; // IN1-4
            if(in1_4 & (0x1<<0)) // IN1
            {
                ui->pushButton_in1->setPicture(QString::fromUtf8(":/images/io1on.png"));
            }
            else
            {
                ui->pushButton_in1->setPicture(QString::fromUtf8(":/images/io1off.png"));
            }

            if(in1_4 & (0x1<<1)) // IN2
            {
                ui->pushButton_in2->setPicture(QString::fromUtf8(":/images/io2on.png"));
            }
            else
            {
                ui->pushButton_in2->setPicture(QString::fromUtf8(":/images/io2off.png"));
            }


            if(in1_4 & (0x1<<2)) // IN3
            {
                ui->pushButton_in3->setPicture(QString::fromUtf8(":/images/io3on.png"));
            }
            else
            {
                ui->pushButton_in3->setPicture(QString::fromUtf8(":/images/io3off.png"));
            }


            if(in1_4 & (0x1<<3)) // IN4
            {
                ui->pushButton_in4->setPicture(QString::fromUtf8(":/images/io4on.png"));
            }
            else
            {
                ui->pushButton_in4->setPicture(QString::fromUtf8(":/images/io4off.png"));
            }

        }

    }

}

void FIOMqtt::on_pushButton_server_clicked(bool checked)
{
    qDebug() << "mqtt checked=" << checked;
    if(checked) // true  连接服务器
    {
        // 创建1个mqtt 对象
        mqttclient = new QMqttClient(this);
        // 设置服务器信息
        mqttclient->setHostname(ui->comboBox_server->currentText());
        mqttclient->setPort(1883);// 设置端口号

        // 设置心跳包
        mqttclient->setAutoKeepAlive(true); // 自动保持连接

        // 设置信号处理函数
        connect(mqttclient, &QMqttClient::stateChanged, this, &FIOMqtt::stateChanged_slot);
        connect(mqttclient, &QMqttClient::messageReceived, this, &FIOMqtt::messageReceived_slot);

        // 连接服务器
        mqttclient->connectToHost();

    }
    else  // 断开连接
    {
        if(mqttclient != nullptr)
        {
            mqttclient->disconnectFromHost() ; // 断开连接
        }

    }
}



void FIOMqtt::on_pushButton_relay1_clicked(bool checked)
{

    QJsonObject cmd_json;
    if(checked) // 为真 ， 订阅主题
    {
        cmd_json.insert("RELAY1",true);
        ui->pushButton_relay1->setPicture(":/images/relay1on.png");
    }
    else
    {
        cmd_json.insert("RELAY1",false);
        ui->pushButton_relay1->setPicture(":/images/relay1off.png");
    }
    QJsonDocument doc; // 定义1个json 字符串
    doc.setObject(cmd_json); // 初始化一个json字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//  把json字符串转换成 bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(),cmdArray);
    }

}


void FIOMqtt::on_pushButton_relay2_clicked(bool checked)
{
    QJsonObject cmd_json;
    if(checked) // 为真 ， 订阅主题
    {
        cmd_json.insert("RELAY2",true);
        ui->pushButton_relay2->setPicture(":/images/relay2on.png");
    }
    else
    {
        cmd_json.insert("RELAY2",false);
        ui->pushButton_relay2->setPicture(":/images/relay2off.png");
    }
    QJsonDocument doc; // 定义1个json 字符串
    doc.setObject(cmd_json); // 初始化一个json字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//  把json字符串转换成 bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(),cmdArray);
    }

}


void FIOMqtt::on_pushButton_relay3_clicked(bool checked)
{
    QJsonObject cmd_json;
    if(checked) // 为真 ， 订阅主题
    {
        cmd_json.insert("RELAY3",true);
        ui->pushButton_relay3->setPicture(":/images/relay3on.png");
    }
    else
    {
        cmd_json.insert("RELAY3",false);
        ui->pushButton_relay3->setPicture(":/images/relay3off.png");
    }
    QJsonDocument doc; // 定义1个json 字符串
    doc.setObject(cmd_json); // 初始化一个json字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//  把json字符串转换成 bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(),cmdArray);
    }

}


void FIOMqtt::on_pushButton_relay4_clicked(bool checked)
{
    QJsonObject cmd_json;
    if(checked) // 为真 ， 订阅主题
    {
        cmd_json.insert("RELAY4",true);
        ui->pushButton_relay4->setPicture(":/images/relay4on.png");
    }
    else
    {
        cmd_json.insert("RELAY4",false);
        ui->pushButton_relay4->setPicture(":/images/relay4off.png");
    }
    QJsonDocument doc; // 定义1个json 字符串
    doc.setObject(cmd_json); // 初始化一个json字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//  把json字符串转换成 bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(),cmdArray);
    }

}



