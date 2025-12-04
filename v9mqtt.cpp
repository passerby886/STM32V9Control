#include "v9mqtt.h"
#include "ui_v9mqtt.h"

V9Mqtt::V9Mqtt(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::V9Mqtt)
{
    ui->setupUi(this);
    this->initUi();
}

V9Mqtt::~V9Mqtt()
{
    delete ui;
}

void V9Mqtt::initUi()
{

    // 设置 label 的字体颜色为白色
    ui->label_server->setStyleSheet("color: white;");
    ui->label_upload->setStyleSheet("color: white;");
    ui->label_download->setStyleSheet("color: white;");


    ui->pushButton_led1->setPicture(QString::fromUtf8(":/images/led1off.png"));
    ui->pushButton_led2->setPicture(QString::fromUtf8(":/images/led2off.png"));
    ui->pushButton_beep->setPicture(QString::fromUtf8(":/images/beepoff.png"));
    ui->pushButton_relay->setPicture(QString::fromUtf8(":/images/relayoff.png"));

    ui->pushButton_temp->setPicture(QString::fromUtf8(":/images/temp.png"));
    ui->pushButton_temp->setValue("----");
    ui->pushButton_temp->setXOffset(12);

    ui->pushButton_hum->setPicture(QString::fromUtf8(":/images/hum.png"));
    ui->pushButton_hum->setValue("----");
    ui->pushButton_hum->setXOffset(20);

    ui->pushButton_cpu->setPicture(QString::fromUtf8(":/images/cpu.png"));
    ui->pushButton_cpu->setValue("----");
    ui->pushButton_cpu->setXOffset(12);


    ui->pushButton_vr->setPicture(QString::fromUtf8(":/images/vr.png"));
    ui->pushButton_vr->setValue("----");
    ui->pushButton_vr->setXOffset(12);


    ui->pushButton_vol->setPicture(QString::fromUtf8(":/images/vol.png"));
    ui->pushButton_vol->setValue("----");
    ui->pushButton_vol->setXOffset(12);

    ui->pushButton_cur->setPicture(QString::fromUtf8(":/images/cur.png"));
    ui->pushButton_cur->setValue("----");
    ui->pushButton_cur->setXOffset(0);

    ui->pushButton_pw->setPicture(QString::fromUtf8(":/images/pw.png"));
    ui->pushButton_pw->setValue("----");
    ui->pushButton_pw->setXOffset(12);


    ui->pushButton_server->setStyleSheet(
        "QPushButton { border-radius: 5px;background-color: white; }" // 正常状态
        "QPushButton:pressed { background-color: #5354cb; }"          // 按压状态
        "QPushButton:checked { background-color: #5354cb; }"          // 选中状态
        );
    ui->pushButton_server->setCheckable(true);
    ui->pushButton_led1->setCheckable(true);
    ui->pushButton_led2->setCheckable(true);
    ui->pushButton_beep->setCheckable(true);
    ui->pushButton_relay->setCheckable(true);
}



void V9Mqtt::stateChanged_slot(QMqttClient::ClientState state)
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

void V9Mqtt::messageReceived_slot(const QByteArray &message, const QMqttTopicName &topic )
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
        QJsonValue jsonTP =  jsonObject.value("TP"); // 获取温度的值
        QJsonValue jsonRH =  jsonObject.value("RH"); // 获取湿度的值
        QJsonValue jsonVL =  jsonObject.value("VO"); // 获取系统电压的值
        QJsonValue jsonCU =  jsonObject.value("CU"); // 获取系统电流的值
        QJsonValue jsonPW =  jsonObject.value("PW"); // 获取系统功率的值
        QJsonValue jsonVR =  jsonObject.value("VR"); // 获取电位器的电压
        QJsonValue jsonCPU =  jsonObject.value("CPU"); // 获取CPU温度的值

        if(!jsonTP.isNull())
        {
            ui->pushButton_temp->setValue(QString::asprintf("%.1f℃",jsonTP.toDouble()/100.0));
        }
        if(!jsonRH.isNull())
        {
            ui->pushButton_hum->setValue(QString::asprintf("%.1f%",jsonRH.toDouble()/100.0));
        }
        if(!jsonVL.isNull())
        {
            ui->pushButton_vol->setValue(QString::asprintf("%.2fV",jsonVL.toDouble()/100.0));
        }
        if(!jsonCU.isNull())
        {
            ui->pushButton_cur->setValue(QString::asprintf("%.0fmA",jsonCU.toDouble()));
        }
        if(!jsonPW.isNull())
        {
            ui->pushButton_pw->setValue(QString::asprintf("%.2fW",jsonPW.toDouble()/1000.0));
        }
        if(!jsonVR.isNull())
        {
            ui->pushButton_vr->setValue(QString::asprintf("%.2fV",jsonVR.toDouble()/100.0));
        }
        if(!jsonCPU.isNull())
        {
            ui->pushButton_cpu->setValue(QString::asprintf("%.1f℃",jsonCPU.toDouble()/100.0));
        }
    }

}

void V9Mqtt::on_pushButton_server_clicked(bool checked)
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
        connect(mqttclient, &QMqttClient::stateChanged, this, &V9Mqtt::stateChanged_slot);
        connect(mqttclient, &QMqttClient::messageReceived, this, &V9Mqtt::messageReceived_slot);

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



void V9Mqtt::on_pushButton_led1_clicked(bool checked)
{

    QJsonObject cmd_json;
    if(checked) // 为真 ， 订阅主题
    {
        cmd_json.insert("LED1",true);
        ui->pushButton_led1->setPicture(":/images/led1on.png");
    }
    else
    {
        cmd_json.insert("LED1",false);
        ui->pushButton_led1->setPicture(":/images/led1off.png");
    }
    QJsonDocument doc; // 定义1个json 字符串
    doc.setObject(cmd_json); // 初始化一个json字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//  把json字符串转换成 bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(),cmdArray);
    }

}


void V9Mqtt::on_pushButton_led2_clicked(bool checked)
{
    QJsonObject cmd_json;
    if(checked) // 为真 ， 订阅主题
    {
        cmd_json.insert("LED2",true);
        ui->pushButton_led2->setPicture(":/images/led2on.png");
    }
    else
    {
        cmd_json.insert("LED2",false);
        ui->pushButton_led2->setPicture(":/images/led2off.png");
    }
    QJsonDocument doc; // 定义1个json 字符串
    doc.setObject(cmd_json); // 初始化一个json字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//  把json字符串转换成 bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(),cmdArray);
    }

}


void V9Mqtt::on_pushButton_beep_clicked(bool checked)
{
    QJsonObject cmd_json;
    if(checked) // 为真 ， 订阅主题
    {
        cmd_json.insert("BEEP",true);
        ui->pushButton_beep->setPicture(":/images/beepon.png");
    }
    else
    {
        cmd_json.insert("BEEP",false);
        ui->pushButton_beep->setPicture(":/images/beepoff.png");
    }
    QJsonDocument doc; // 定义1个json 字符串
    doc.setObject(cmd_json); // 初始化一个json字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//  把json字符串转换成 bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(),cmdArray);
    }

}


void V9Mqtt::on_pushButton_relay_clicked(bool checked)
{
    QJsonObject cmd_json;
    if(checked) // 为真 ， 订阅主题
    {
        cmd_json.insert("RELAY",true);
        ui->pushButton_relay->setPicture(":/images/relayon.png");
    }
    else
    {
        cmd_json.insert("RELAY",false);
        ui->pushButton_relay->setPicture(":/images/relayoff.png");
    }
    QJsonDocument doc; // 定义1个json 字符串
    doc.setObject(cmd_json); // 初始化一个json字符串
    QByteArray cmdArray = doc.toJson(QJsonDocument::Compact);//  把json字符串转换成 bytearray
    if(mqttclient != nullptr)
    {
        mqttclient->publish(ui->comboBox_download->currentText(),cmdArray);
    }

}

