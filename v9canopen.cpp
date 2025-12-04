#include "v9canopen.h"
#include "ui_v9canopen.h"

V9CANopen::V9CANopen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::V9CANopen)
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
    connect(this,&V9CANopen::SigReceiveCanData,this,&V9CANopen::SlotReceiveCanData);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&V9CANopen::timer_timeout_slot);

}

V9CANopen::~V9CANopen()
{
    delete ui;
}

void V9CANopen::initUi()
{

    // 设置 label 的字体颜色为白色
    ui->label_server->setStyleSheet("color: white;");


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
    ui->pushButton_led1->setCheckable(true);
    ui->pushButton_led2->setCheckable(true);
    ui->pushButton_beep->setCheckable(true);
    ui->pushButton_relay->setCheckable(true);
}


void V9CANopen::on_pushButton_refresh_clicked()
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



void V9CANopen::readMessage()
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


void V9CANopen::SlotReceiveCanData(quint32 recv_id,quint8 dlc, QByteArray recv_data)
{
    //qDebug() << "SlotReceiveCanData:recvData:" << recv_data;
    quint8 * recvData = (quint8*)recv_data.data();
    // for(int i=0;i<dlc;i++)
    // {
    //     qDebug("->:0x%x ",recvData[i]) ;
    // }
    if( (recv_id == 0x581) && (dlc == 8) )
    {
        if( (recvData[0] == 0x4b) && (recvData[1] == 0x00)
            && (recvData[2] == 0x20) && (recvData[3] == 0x02) ) // 解析温度值
        {
            quint16 temp  = (recvData[5] << 8) | recvData[4] ; // 温度
            ui->pushButton_temp->setValue(QString::asprintf("%.1f",temp/100.0) + "℃");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00)
            && (recvData[2] == 0x20) && (recvData[3] == 0x03) ) // 解析湿度值
        {
            quint16 hum  = (recvData[5] << 8) | recvData[4] ; // 湿度
            ui->pushButton_hum->setValue(QString::asprintf("%.1f",hum/100.0) + "%");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00)
                 && (recvData[2] == 0x20) && (recvData[3] == 0x04) ) // 解析系统电压值
        {
            quint16 vol  = (recvData[5] << 8) | recvData[4] ; // 系统电压
            ui->pushButton_vol->setValue(QString::asprintf("%.2f",vol/100.0) + "V");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00)
                 && (recvData[2] == 0x20) && (recvData[3] == 0x05) ) // 解析系统电流值
        {
            quint16 cur  = (recvData[5] << 8) | recvData[4] ; // 系统电流
            ui->pushButton_cur->setValue(QString::asprintf("%.0f",cur/1.0) + "mA");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00)
                 && (recvData[2] == 0x20) && (recvData[3] == 0x06) ) // 解析系统功率值
        {
            quint16 pw  = (recvData[5] << 8) | recvData[4] ; // 系统功率
            ui->pushButton_pw->setValue(QString::asprintf("%.2f",pw/1000.0) + "W");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00)
                 && (recvData[2] == 0x20) && (recvData[3] == 0x07) ) // 解析电位器值
        {
            quint16 vr  = (recvData[5] << 8) | recvData[4] ; // 电位器
            ui->pushButton_vr->setValue(QString::asprintf("%.2f",vr/100.0) + "V");
        }
        else if( (recvData[0] == 0x4b) && (recvData[1] == 0x00)
                 && (recvData[2] == 0x20) && (recvData[3] == 0x08) ) // 解析CPU值
        {
            quint16 cpu  = (recvData[5] << 8) | recvData[4] ; // CPU
            ui->pushButton_cpu->setValue(QString::asprintf("%.1f",cpu/100.0) + "℃");
        }
    }
}


void V9CANopen::timer_timeout_slot()
{
    //qDebug() << "timer_timeout_slot";
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    frame.data[0] = 0x4b;
    frame.data[1] = 0x00;
    frame.data[2] = 0x20;
    frame.data[3] = 0x02;
    frame.data[4] = 0x00;
    frame.data[5] = 0x00;
    frame.data[6] = 0x00;
    frame.data[7] = 0x00;
    frame.can_dlc = 8;
    frame.can_id = 0x601; // send id
    // 获取温度的值
    candle_frame_send(device.handle, 0, &frame);

    // 获取湿度的值
    frame.data[3] = 0x03;
    candle_frame_send(device.handle, 0, &frame);

    // 获取系统电压的值
    frame.data[3] = 0x04;
    candle_frame_send(device.handle, 0, &frame);

    // 获取系统电流的值
    frame.data[3] = 0x05;
    candle_frame_send(device.handle, 0, &frame);

    // 获取系统功率的值
    frame.data[3] = 0x06;
    candle_frame_send(device.handle, 0, &frame);

    // 获取电位器的值
    frame.data[3] = 0x07;
    candle_frame_send(device.handle, 0, &frame);

    // 获取CPU的值
    frame.data[3] = 0x08;
    candle_frame_send(device.handle, 0, &frame);

}

void V9CANopen::on_pushButton_open_clicked(bool checked)
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
        future =  QtConcurrent::run(this,&V9CANopen::readMessage);

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


void V9CANopen::on_pushButton_led1_clicked(bool checked)
{
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked) // 为真
    {
        cmdConBit = cmdConBit | (1<<0) ; // led1 on
        ui->pushButton_led1->setPicture(":/images/led1on.png");
    }
    else
    {
        cmdConBit = cmdConBit & (~(1<<0)) ; // led1 off
        ui->pushButton_led1->setPicture(":/images/led1off.png");
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
    frame.can_id = 0x601; // send id

    qDebug()<<"send :" << candle_frame_send(device.handle, 0, &frame);
}

void V9CANopen::on_pushButton_led2_clicked(bool checked)
{
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked) // 为真
    {
        cmdConBit = cmdConBit | (1<<1) ; // led1 on
        ui->pushButton_led2->setPicture(":/images/led2on.png");
    }
    else
    {
        cmdConBit = cmdConBit & (~(1<<1)) ; // led2 off
        ui->pushButton_led2->setPicture(":/images/led2off.png");
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
    frame.can_id = 0x601; // send id

    qDebug()<<"send :" << candle_frame_send(device.handle, 0, &frame);
}

void V9CANopen::on_pushButton_beep_clicked(bool checked)
{
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked) // 为真
    {
        cmdConBit = cmdConBit | (1<<2) ; // beep on
        ui->pushButton_beep->setPicture(":/images/beepon.png");
    }
    else
    {
        cmdConBit = cmdConBit & (~(1<<2)) ; // beep off
        ui->pushButton_beep->setPicture(":/images/beepoff.png");
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
    frame.can_id = 0x601; // send id

    qDebug()<<"send :" << candle_frame_send(device.handle, 0, &frame);
}


void V9CANopen::on_pushButton_relay_clicked(bool checked)
{
    CanDevice device = devices[ui->comboBox_can->currentIndex()];
    candle_frame_t frame;
    if(checked) // 为真
    {
        cmdConBit = cmdConBit | (1<<3) ; // relay on
        ui->pushButton_relay->setPicture(":/images/relayon.png");
    }
    else
    {
        cmdConBit = cmdConBit & (~(1<<3)) ; // relay off
        ui->pushButton_relay->setPicture(":/images/relayoff.png");
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
    frame.can_id = 0x601; // send id

    qDebug()<<"send :" << candle_frame_send(device.handle, 0, &frame);
}


