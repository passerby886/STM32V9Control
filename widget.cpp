#include "widget.h"
#include "v9mqtt.h"
#include "v9canopen.h"
#include "fiomodbus.h"
#include "fiomqtt.h"
#include "fiocanopen.h"

#include "ui_widget.h"
#include "ui_v9mqtt.h"
#include "ui_v9canopen.h"
#include "ui_fiomodbus.h"
#include "ui_fiomqtt.h"
#include "ui_fiocanopen.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->initUi();
    QList<QSerialPortInfo> serialPorts =  QSerialPortInfo::availablePorts() ;
    foreach (QSerialPortInfo port, serialPorts) {
        qDebug() << "串口名：" << port.portName() ; // 串口名称
        qDebug() << "串口描述：" << port.description() ; // 串口描述
        ui->comboBox->addItem(port.portName()+" #"+port.description(),QVariant(port.portName()));
    }

    // 定义1个定时器， 每隔2秒刷新一次
    timer =  new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Widget::timer_timeout_slot);
}

Widget::~Widget()
{
    delete ui;
}

//数组首地址、数组长度-2（不包含校验玛）
unsigned int make_crc(unsigned char *puchMsg,unsigned int usDataLen)
{
    unsigned char i;
    unsigned int  crc=0XFFFF;
    while(usDataLen--!=0)
    {
        crc=crc^(*puchMsg);
        for(i=0;i<8;i++){if((crc&0x0001)==1){crc=crc>>1;crc^=0XA001;}else{crc=crc>>1;}}
        puchMsg++;
    }
    return(crc);
}

// 成功读取返回 ： true
// 失败读取返回 ： false
bool Widget::cmdReadBytes(quint8 readData[],quint8 n)
{
    // 在 115200 的波特率下发送 100 字节需要约 6.944 毫秒。
    if (!serial->waitForReadyRead(3000))  return false;
    QByteArray data = serial->readAll();
    while (serial->waitForReadyRead(10))
        data += serial->readAll();

    for(qint32 i=0;i<data.size();i++)
    {
        readData[i] =  quint8(data.at(i)) ;// 数据入队
        //qDebug("%#x",quint8(data.at(i))) ;
    }
    quint16 recv_crc = (readData[n-1] << 8) | readData[n-2] ;
    quint16 calc_crc = make_crc(readData,n-2);// 计算出的crc
    // qDebug("recv_crc = %#x",recv_crc)  ;
    // qDebug("calc_crc = %#x",calc_crc)  ;
    if( recv_crc == calc_crc  )
    {
        return true;
    }
    else
    {
        static qint32 count  =0 ;
        qDebug("crc校验失败次数:%d",++count)  ;
        return false;
    }

}

// 返回真 ： 表示命令发送成功
// 返回假 ： 表示命令发送失败
bool Widget::cmdStatus(quint8 src_cmd[],quint8 n)
{
    quint8 dst_cmd[128];

    // 在 115200 的波特率下发送 100 字节需要约 6.944 毫秒。
    if (!serial->waitForReadyRead(1000))  return false;
    QByteArray data = serial->readAll();
    while (serial->waitForReadyRead(10))
        data += serial->readAll();

    for(qint32 i=0;i<data.size();i++)
    {
        dst_cmd[i] =  quint8(data.at(i)) ;// 数据入队
        //qDebug() << "->:" << quint8(data.at(i));
    }
    if( memcmp(src_cmd,dst_cmd,n) == 0 )
    {
        return true;
    }
    else
    {
        qDebug() << "cmdStatus memcpy failed";
        return false;
    }
}

void Widget::on_pushButton_open_clicked(bool checked)
{
    qDebug() << "checked=" << checked ;
    if(checked) // 为真
    {

        qDebug() << "portName="<< ui->comboBox->currentData().toString();
        serial = new QSerialPort(this);
        serial->setPortName(ui->comboBox->currentData().toString());

        // 打开串口
        if(serial->open((QIODevice::ReadWrite)) ) // 可读可写的方式打开串口
        {
            ui->pushButton_open->setText(tr("关闭串口"));
            ui->comboBox->setEnabled(false); // 下拉列表不可操作

            serial->setBaudRate(QSerialPort::Baud115200); // 设置串口的波特率
            serial->setParity(QSerialPort::NoParity); // 无校验
            serial->setDataBits(QSerialPort::Data8) ; // 设置数据位 8
            serial->setStopBits(QSerialPort::OneStop) ; // 1个停止位
            serial->setFlowControl(QSerialPort::NoFlowControl); // 无硬件流控
            serial->setReadBufferSize(1); // 接受缓存区为1 ， 收到1个直接就发送信号

            if(timer != nullptr)
            {
                timer->start(2000) ; // 2秒一次触发
            }

        }
        else
        {
            if(serial != nullptr)
            {
                serial->close();
                serial->deleteLater();
                serial = nullptr ;
            }
            ui->pushButton_open->setText(tr("打开串口"));
            ui->comboBox->setEnabled(true); // 下拉列表不可操作
            ui->pushButton_open->setChecked(false) ; // 按钮抬起
            QMessageBox::warning(this,tr("串口打开失败"),tr("串口被别的进程占用，关闭别的进程后再打开"));
            return ;
        }

    }
    else // 为假 关闭串口
    {
        if(serial != nullptr)
        {
            serial->close();
            serial->deleteLater();
            serial = nullptr ;
        }
        ui->pushButton_open->setText(tr("打开串口"));
        ui->comboBox->setEnabled(true); // 下拉列表不可操作

        if(timer != nullptr)
        {
            timer->stop() ; // 关闭定时器
        }
    }
}


void Widget::on_pushButton_refresh_clicked()
{
    ui->comboBox->clear();
    QList<QSerialPortInfo> serialPorts =  QSerialPortInfo::availablePorts() ;
    foreach (QSerialPortInfo port, serialPorts) {
        qDebug() << "串口名：" << port.portName() ; // 串口名称
        qDebug() << "串口描述：" << port.description() ; // 串口描述
        ui->comboBox->addItem(port.portName()+" #"+port.description(),QVariant(port.portName()));
    }
}


void Widget::on_pushButton_led1_clicked(bool checked)
{
    qDebug() << " led1 locking checked=" << checked;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    if(checked) // 真
    {
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<0) ; // led1 on
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if( cmdStatus(cmd,8) ) // 为真， 命令发送成功led1 on
            {
                qDebug() << "led1 on" ;
                ui->pushButton_led1->setPicture(":/images/led1on.png");
            }
            else
            {
                ui->pushButton_led1->setChecked(false) ; // 按钮 抬起
                qDebug() << "led1 cmd failed";
                return ;
            }

        }
    }
    else
    {
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<0)) ; // led1 off
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if(cmdStatus(cmd,8) ) // 为真， 命令发送成功led1 on
            {
                qDebug() << "led1 off" ;
                ui->pushButton_led1->setPicture(":/images/led1off.png");
            }
            else
            {
                ui->pushButton_led1->setChecked(true) ; // 按钮 按压
                return ;
            }

        }

    }
}

void Widget::on_pushButton_led2_clicked(bool checked)
{
    qDebug() << " led2 locking checked=" << checked;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    if(checked) // 真
    {
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<1) ; // led2 on
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if( cmdStatus(cmd,8) ) // 为真， 命令发送成功led1 on
            {
                qDebug() << "led2 on" ;
                ui->pushButton_led2->setPicture(":/images/led2on.png");
            }
            else
            {
                ui->pushButton_led2->setChecked(false) ; // 按钮 抬起
                qDebug() << "led2 cmd failed";
                return ;
            }

        }
    }
    else
    {
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<1)) ; // led2 off
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if(cmdStatus(cmd,8) ) // 为真， 命令发送成功led2s on
            {
                qDebug() << "led2 off" ;
                ui->pushButton_led2->setPicture(":/images/led2off.png");
            }
            else
            {
                ui->pushButton_led2->setChecked(true) ; // 按钮 按压
                return ;
            }

        }

    }
}

void Widget::on_pushButton_beep_clicked(bool checked)
{
    qDebug() << " beep locking checked=" << checked;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    if(checked) // 真
    {
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<2) ; // beep on
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if( cmdStatus(cmd,8) ) // 为真， 命令发送成功beep on
            {
                qDebug() << "beep on" ;
                ui->pushButton_beep->setPicture(":/images/beepon.png");
            }
            else
            {
                ui->pushButton_beep->setChecked(false) ; // 按钮 抬起
                qDebug() << "beep cmd failed";
                return ;
            }

        }
    }
    else
    {
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<2)) ; // beep off
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if(cmdStatus(cmd,8) ) // 为真， 命令发送成功beeps on
            {
                qDebug() << "beep off" ;
                ui->pushButton_beep->setPicture(":/images/beepoff.png");
            }
            else
            {
                ui->pushButton_beep->setChecked(true) ; // 按钮 按压
                return ;
            }

        }

    }
}




void Widget::on_pushButton_relay_clicked(bool checked)
{
    qDebug() << " relay locking checked=" << checked;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    if(checked) // 真
    {
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<3) ; // relay on
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if( cmdStatus(cmd,8) ) // 为真， 命令发送成功relay on
            {
                qDebug() << "relay on" ;
                ui->pushButton_relay->setPicture(":/images/relayon.png");
            }
            else
            {
                ui->pushButton_relay->setChecked(false) ; // 按钮 抬起
                qDebug() << "relay cmd failed";
                return ;
            }

        }
    }
    else
    {
        quint8 cmd[] = {0x01,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<3)) ; // relay off
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if(cmdStatus(cmd,8) ) // 为真， 命令发送成功relays on
            {
                qDebug() << "relay off" ;
                ui->pushButton_relay->setPicture(":/images/relayoff.png");
            }
            else
            {
                ui->pushButton_relay->setChecked(true) ; // 按钮 按压
                return ;
            }

        }

    }
}



void Widget::timer_timeout_slot()
{
    //qDebug() << "timer_timeout_slot()" ;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    // 01 03 00 01 00 07 55 C8
    quint8 cmd[] = {0x01,0x03,0x00,0x01,0x00,0x07,0x55,0xc8};
    quint8 readData[128]= {0};
    if(serial != nullptr)
    {
        serial->write((char *)cmd,sizeof(cmd)/sizeof(cmd[0]));
        if(cmdReadBytes(readData,19))  //  成功返回真
        {
            quint16 temp  = (readData[3] << 8) | readData[4] ; // 温度
            quint16 hum   = (readData[5] << 8) | readData[6] ; // 湿度
            quint16 vol   = (readData[7] << 8) | readData[8] ; // 系统电压
            quint16 cur   = (readData[9] << 8) | readData[10] ; // 系统电流
            quint16 pw    = (readData[11] << 8) | readData[12] ; // 系统功率
            quint16 vr    = (readData[13] << 8) | readData[14] ; //  电位器电压
            quint16 cpu   = (readData[15] << 8) | readData[16] ; // CPU温度
            ui->pushButton_temp->setValue(QString::asprintf("%.1f",temp/100.0) + "℃");
            ui->pushButton_hum->setValue(QString::asprintf("%.1f",hum/100.0) + "%");
            ui->pushButton_vol->setValue(QString::asprintf("%.2f",vol/100.0) + "V");
            ui->pushButton_cur->setValue(QString::asprintf("%.0f",cur/1.0) + "mA");
            ui->pushButton_pw->setValue(QString::asprintf("%.2f",pw/1000.0) + "W");
            ui->pushButton_vr->setValue(QString::asprintf("%.2f",vr/100.0) + "V");
            ui->pushButton_cpu->setValue(QString::asprintf("%.1f",cpu/100.0) + "℃");
        }
        else
        {
           qDebug() << "serial timer timeout " ;
        }
    }


}

void Widget::on_listWidget_clicked(const QModelIndex &index)
{
    qDebug() << "on_listWidget_clicked()=" << index.row();
    ui->tabWidget->setCurrentIndex(index.row()); // 选中子窗体
}

void Widget::initUi()
{

    // 绘制背景图片
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(QString::fromUtf8(":/images/back.png"));
    QImage pix = ImgAllbackground.scaled(this->size(),Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(pix));
    this->setPalette(PAllbackground);

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


    // 设置 label 的字体颜色为白色
    ui->label->setStyleSheet("color: white;");

    // 设置 listwidget 的样式表
    ui->listWidget->setStyleSheet("QListWidget { background: transparent;"
                                  "border: none; "
                                  "outline: none;"
                                  "font-size: 18px; "
                                  "color: white; "
                                  "font-weight: bold;"
                                  "padding-top: 30px;}"

                                  "QListWidget::item { min-height: 50px;"
                                  "border: none; }"

                                  "QListWidget::item:selected {min-height: 50px;"
                                  "background: #5354cb;"
                                  "border: none; "
                                  "border-radius: 10px; }"
                                  );


    ui->listWidget->setSpacing(5) ; // 设置元素的间距
    ui->listWidget->horizontalScrollBar()->hide();

    //  listwidget 添加内容
    QListWidgetItem * stm32v9modbus =  new QListWidgetItem(QIcon(":/images/device.png"),"STM32V9 | Modbus",ui->listWidget);
    ui->listWidget->addItem(stm32v9modbus);
    QListWidgetItem * stm32v9mqtt =  new QListWidgetItem(QIcon(":/images/device.png"),"STM32V9 | MQTT",ui->listWidget);
    ui->listWidget->addItem(stm32v9mqtt);
    QListWidgetItem * stm32v9canopen =  new QListWidgetItem(QIcon(":/images/device.png"),"STM32V9 | CANopen",ui->listWidget);
    ui->listWidget->addItem(stm32v9canopen);
    QListWidgetItem * fouriomodbus =  new QListWidgetItem(QIcon(":/images/device.png"),"4路IO | Modbus",ui->listWidget);
    ui->listWidget->addItem(fouriomodbus);
    QListWidgetItem * fouriomqtt =  new QListWidgetItem(QIcon(":/images/device.png"),"4路IO | MQTT",ui->listWidget);
    ui->listWidget->addItem(fouriomqtt);
    QListWidgetItem * fouriocanopen =  new QListWidgetItem(QIcon(":/images/device.png"),"4路IO | CANopen",ui->listWidget);
    ui->listWidget->addItem(fouriocanopen);

    ui->listWidget->setCurrentItem(stm32v9modbus);



    // 向 tabwidget 内添加子控件
    V9Mqtt * v9mqtt = new V9Mqtt(this);
    ui->tabWidget->addTab(v9mqtt,"V9Mqtt");
    V9CANopen * v9canopen = new V9CANopen(this);
    ui->tabWidget->addTab(v9canopen,"V9CANopen");

    FIOModbus * fiomodbus = new FIOModbus(this);
    ui->tabWidget->addTab(fiomodbus,"FIOModbus");
    FIOMqtt * fiomqtt = new FIOMqtt(this);
    ui->tabWidget->addTab(fiomqtt,"FIOMqtt");
    FIOCANopen * fiocanopen = new FIOCANopen(this);
    ui->tabWidget->addTab(fiocanopen,"FIOCANopen");

    // 设置 tabwidget 透明
    ui->tabWidget->setStyleSheet("QTabWidget::pane { background: transparent;border: none; }");
    ui->tabWidget->tabBar()->hide() ; // 隐藏标签项
    ui->tabWidget->setCurrentIndex(0);


    // 设置按键的样式表
    ui->pushButton_refresh->setStyleSheet(
        "QPushButton { border-radius: 5px;background-color: white; }" // 正常状态
        "QPushButton:pressed { background-color: #5354cb; }"          // 按压状态
        );

    ui->pushButton_open->setStyleSheet(
        "QPushButton { border-radius: 5px;background-color: white; }" // 正常状态
        "QPushButton:pressed { background-color: #5354cb; }"          // 按压状态
        "QPushButton:checked { background-color: #5354cb; }"          // 选中状态
        );
    ui->pushButton_open->setCheckable(true) ; // 两种状态

    ui->pushButton_led1->setCheckable(true) ; // 两种状态
    ui->pushButton_led2->setCheckable(true) ; // 两种状态
    ui->pushButton_beep->setCheckable(true) ; // 两种状态
    ui->pushButton_relay->setCheckable(true) ; // 两种状态


}




