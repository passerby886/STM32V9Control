#include "fiocanopen.h"
#include "ui_fiocanopen.h"

FIOCANopen::FIOCANopen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FIOCANopen)
{
    ui->setupUi(this);
    this->initUi();

    candle_list_handle clist;
    uint8_t num_interfaces;
    candle_handle dev;
    if (candle_list_scan(&clist)) {
        if (candle_list_length(clist, &num_interfaces)) {
            for (uint8_t i=0; i<num_interfaces; i++) {
                if (candle_dev_get(clist, i, &dev)) {
                    CanDevice device;
                    device.id = i;
                    device.handle = dev;
                    device.name = "candle" + QString::number(device.id & 0xFF);
                    device.desc = QString::fromStdWString(candle_dev_get_path(dev));
                    ui->comboBox_can->addItem(device.name);
                    devices.append(device);
                }
            }
        }
        candle_list_free(clist);
    }

    // 设置信号处理函数
    connect(this,&FIOCANopen::SigReceiveCanData,this,&FIOCANopen::SlotReceiveCanData);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&FIOCANopen::timer_timeout_slot);
}

FIOCANopen::~FIOCANopen()
{
    delete ui;
}

void FIOCANopen::initUi()
{

    // 设置 label 的字体颜色为白色
    ui->label_server->setStyleSheet("color: white;");


    ui->pushButton_in1->setPicture(QString::fromUtf8(":/images/io1off.png"));
    ui->pushButton_in2->setPicture(QString::fromUtf8(":/images/io2off.png"));
    ui->pushButton_in3->setPicture(QString::fromUtf8(":/images/io3off.png"));
    ui->pushButton_in4->setPicture(QString::fromUtf8(":/images/io4off.png"));

    ui->pushButton_relay1->setPicture(QString::fromUtf8(":/images/relay1off.png"));
    ui->pushButton_relay2->setPicture(QString::fromUtf8(":/images/relay2off.png"));
    ui->pushButton_relay3->setPicture(QString::fromUtf8(":/images/relay3off.png"));
    ui->pushButton_relay4->setPicture(QString::fromUtf8(":/images/relay4off.png"));



    ui->pushButton_open->setStyleSheet(
        "QPushButton { border-radius: 5px;background-color: white; }" // 正常状态
        "QPushButton:pressed { background-color: #5354cb; }"          // 按压状态
        "QPushButton:checked { background-color: #5354cb; }"          // 选中状态
        );
    ui->pushButton_refresh->setStyleSheet(
        "QPushButton { border-radius: 5px;background-color: white; }" // 正常状态
        "QPushButton:pressed { background-color: #5354cb; }"          // 按压状态
        "QPushButton:checked { background-color: #5354cb; }"          // 选中状态
        );

    ui->pushButton_open->setCheckable(true);
    ui->pushButton_relay1->setCheckable(true);
    ui->pushButton_relay2->setCheckable(true);
    ui->pushButton_relay3->setCheckable(true);
    ui->pushButton_relay4->setCheckable(true);
}




void FIOCANopen::on_pushButton_refresh_clicked()
{
    ui->comboBox_can->clear();
    candle_list_handle clist;
    uint8_t num_interfaces;
    candle_handle dev;
    if (candle_list_scan(&clist)) {
        if (candle_list_length(clist, &num_interfaces)) {
            for (uint8_t i=0; i<num_interfaces; i++) {
                if (candle_dev_get(clist, i, &dev)) {
                    CanDevice device;
                    device.id = i;
                    device.handle = dev;
                    device.name = "candle" + QString::number(device.id & 0xFF);
                    device.desc = QString::fromStdWString(candle_dev_get_path(dev));
                    ui->comboBox_can->addItem(device.name);
                    devices.append(device);
                }
            }
        }
        candle_list_free(clist);
    }
}



void FIOCANopen::readMessage()
{
    while(ui->pushButton_open->isChecked())
    {
        candle_frame_t frame;
        CanDevice device = devices[ui->comboBox_can->currentIndex()];

        if (candle_frame_read(device.handle, &frame, 1000)) {
            auto tt = candle_frame_type(&frame);
            //qDebug() << "tt="  << tt;
            if (tt==CANDLE_FRAMETYPE_RECEIVE) {
                uint32_t id = candle_frame_id(&frame); // recv id
                uint8_t dlc = candle_frame_dlc(&frame);
                uint8_t *data = candle_frame_data(&frame);
                QByteArray byteArr((char *)data,dlc);
                emit SigReceiveCanData(id,dlc,byteArr);
                // qDebug("msgid:%#x",id);
                // qDebug("dlc  :%#x",dlc);
                // qDebug()<<"data:" << byteArr;
            }

        }

        QThread::msleep(100);
        //qDebug() << "task is running";
    }
}


void FIOCANopen::SlotReceiveCanData(quint32 recv_id,quint8 dlc, QByteArray recv_data)
{
    //qDebug() << "SlotReceiveCanData:recvData:" << recv_data;
    quint8 * recvData = (quint8*)recv_data.data();
    // for(int i=0;i<dlc;i++)
    // {
    //     qDebug("->:0x%x ",recvData[i]) ;
    // }
    if( (recv_id == 0x582) && (dlc == 8) )
    {
        if( (recvData[0] == 0x4f) && (recvData[1] == 0x00)
            && (recvData[2] == 0x20) && (recvData[3] == 0x02) ) // 解析 数字IO
        {
            quint8 in1_4  =  recvData[4] ; // IN1-4
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


void FIOCANopen::timer_timeout_slot()
{
    //qDebug() << "timer_timeout_slot";
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    frame.data[0] = 0x4f;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x02;
    frame.data[4] = 0x00;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 8;
    frame.can_id = 0x602; // send id
    // 获取温度的值
    candle_frame_send(device.handle, 0, &frame);

}

void FIOCANopen::on_pushButton_open_clicked(bool checked)
{
    qDebug() << "checked=" << checked;
    if(checked) // 为真 打开设备
    {
        CanDevice device = devices[ui->comboBox_can->currentIndex()];
        if (!candle_dev_open(device.handle)) {
            // TODO what?
            qDebug()<<"error 1";
            return;
        }

        // 读取can的属性信息
        candle_capability_t caps;
        if (!candle_channel_get_capabilities(device.handle, 0, &caps)) {
            qDebug()<<"error 2";
            return;
        }
        else
        {
            qDebug()<<"scan attribute:" << caps.fclk_can << caps.brp_min << caps.brp_max << caps.brp_inc << caps.feature;
        }
        //  500000, 875  ， 设置波特率 500K
        candle_bittiming_t timing;
        timing.brp = 6;
        timing.phase_seg1 = 12;
        timing.phase_seg2 = 2;
        timing.sjw = 1;
        timing.prop_seg = 1;
        if(!candle_channel_set_timing(device.handle, 0, &timing))
        {
            qDebug()<<"error 3";
            return;
        }

        uint32_t t_dev;
        candle_dev_get_timestamp_us(device.handle, &t_dev);

        uint32_t flags = 0;
        // flags |= CANDLE_MODE_LISTEN_ONLY;
        // flags |= CANDLE_MODE_ONE_SHOT;
        // flags |= CANDLE_MODE_TRIPLE_SAMPLE;
        if(candle_channel_start(device.handle, 0, flags) )
        {
            qDebug() <<device.name << "open scuessed" ;
        }
        else
        {
            qDebug() <<device.name << "open failed" ;
        }

        // 设置信号处理函数 SigReceiveCanData


        // 开启1个线程 , 保存函数
        future =  QtConcurrent::run(this,&FIOCANopen::readMessage);

        // 启动定时器
        if(timer != nullptr)
        {
            timer->start(2000);
        }

    }
    else // 为假 关闭设备
    {
        CanDevice device = devices[ui->comboBox_can->currentIndex()];
        future.cancel(); // 取消线程， 关闭线程
        future.waitForFinished();
        if (future.isCanceled())
        {
            qDebug() << "The task has been successfully canceled.";
        }
        else
        {
            qDebug() << "The task was not canceled or has not finished yet.";
        }
        qDebug()<<"stop :" << candle_channel_stop(device.handle, 0);
        qDebug()<<"close :" <<candle_dev_close(device.handle);
    }
}


void FIOCANopen::on_pushButton_relay1_clicked(bool checked)
{
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked) // 为真
    {
        cmdConBit = cmdConBit | (1<<0) ; // relay1 on
        ui->pushButton_relay1->setPicture(":/images/relay1on.png");
    }
    else
    {
        cmdConBit = cmdConBit & (~(1<<0)) ; // relay1 off
        ui->pushButton_relay1->setPicture(":/images/relay1off.png");
    }

    frame.data[0] = 0x2f;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x01;
    frame.data[4] = cmdConBit;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 8;
    frame.can_id = 0x602; // send id

    qDebug()<<"send :" << candle_frame_send(device.handle, 0, &frame);
}

void FIOCANopen::on_pushButton_relay2_clicked(bool checked)
{
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked) // 为真
    {
        cmdConBit = cmdConBit | (1<<1) ; // relay2 on
        ui->pushButton_relay2->setPicture(":/images/relay2on.png");
    }
    else
    {
        cmdConBit = cmdConBit & (~(1<<1)) ; // relay2 off
        ui->pushButton_relay2->setPicture(":/images/relay2off.png");
    }

    frame.data[0] = 0x2f;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x01;
    frame.data[4] = cmdConBit;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 8;
    frame.can_id = 0x602; // send id

    qDebug()<<"send :" << candle_frame_send(device.handle, 0, &frame);
}

void FIOCANopen::on_pushButton_relay3_clicked(bool checked)
{
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked) // 为真
    {
        cmdConBit = cmdConBit | (1<<2) ; // relay3 on
        ui->pushButton_relay3->setPicture(":/images/relay3on.png");
    }
    else
    {
        cmdConBit = cmdConBit & (~(1<<2)) ; // relay3 off
        ui->pushButton_relay3->setPicture(":/images/relay3off.png");
    }

    frame.data[0] = 0x2f;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x01;
    frame.data[4] = cmdConBit;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 8;
    frame.can_id = 0x602; // send id

    qDebug()<<"send :" << candle_frame_send(device.handle, 0, &frame);
}


void FIOCANopen::on_pushButton_relay4_clicked(bool checked)
{
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked) // 为真
    {
        cmdConBit = cmdConBit | (1<<3) ; // relay4 on
        ui->pushButton_relay4->setPicture(":/images/relay4on.png");
    }
    else
    {
        cmdConBit = cmdConBit & (~(1<<3)) ; // relay4 off
        ui->pushButton_relay4->setPicture(":/images/relay4off.png");
    }

    frame.data[0] = 0x2f;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x01;
    frame.data[4] = cmdConBit;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 8;
    frame.can_id = 0x602; // send id

    qDebug()<<"send :" << candle_frame_send(device.handle, 0, &frame);
}




