#include "fiomodbus.h"
#include "ui_fiomodbus.h"

FIOModbus::FIOModbus(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FIOModbus)
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
    connect(timer,&QTimer::timeout,this,&FIOModbus::timer_timeout_slot);

}

FIOModbus::~FIOModbus()
{
    delete ui;
}


//数组首地址、数组长度-2（不包含校验玛）
 unsigned int FIOModbus::make_crc(unsigned char *puchMsg,unsigned int usDataLen)
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
bool FIOModbus::cmdReadBytes(quint8 readData[],quint8 n)
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
bool FIOModbus::cmdStatus(quint8 src_cmd[],quint8 n)
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



void FIOModbus::timer_timeout_slot()
{
    //qDebug() << "timer_timeout_slot()" ;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    // 02 03 00 01 00 01 D5 F9
    quint8 cmd[] = {0x02,0x03,0x00,0x01,0x00,0x01,0xD5,0xF9};
    quint8 readData[128]= {0};
    if(serial != nullptr)
    {
        serial->write((char *)cmd,sizeof(cmd)/sizeof(cmd[0]));
        if(cmdReadBytes(readData,7))  //  成功返回真
        {
            quint16 in1_4  = readData[4] ; // IN1-4
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
        else
        {
            qDebug() << "serial timer timeout " ;
        }
    }


}

void FIOModbus::initUi()
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


void FIOModbus::on_pushButton_open_clicked(bool checked)
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


void FIOModbus::on_pushButton_refresh_clicked()
{
    ui->comboBox->clear();
    QList<QSerialPortInfo> serialPorts =  QSerialPortInfo::availablePorts() ;
    foreach (QSerialPortInfo port, serialPorts) {
        qDebug() << "串口名：" << port.portName() ; // 串口名称
        qDebug() << "串口描述：" << port.description() ; // 串口描述
        ui->comboBox->addItem(port.portName()+" #"+port.description(),QVariant(port.portName()));
    }
}

void FIOModbus::on_pushButton_relay1_clicked(bool checked)
{
    qDebug() << " relay1 locking checked=" << checked;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    if(checked) // 真
    {
        // 02 06 00 00 00 00 89 F9
        quint8 cmd[] = {0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<0) ; // relay1 on
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if( cmdStatus(cmd,8) ) // 为真， 命令发送成功relay1 on
            {
                qDebug() << "relay1 on" ;
                ui->pushButton_relay1->setPicture(":/images/relay1on.png");
            }
            else
            {
                ui->pushButton_relay1->setChecked(false) ; // 按钮 抬起
                qDebug() << "relay1 cmd failed";
                return ;
            }

        }
    }
    else
    {
        // 02 06 00 00 00 00 89 F9
        quint8 cmd[] = {0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<0)) ; // relay1 off
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if(cmdStatus(cmd,8) ) // 为真， 命令发送成功
            {
                qDebug() << "relay1 off" ;
                ui->pushButton_relay1->setPicture(":/images/relay1off.png");
            }
            else
            {
                ui->pushButton_relay1->setChecked(true) ; // 按钮 按压
                return ;
            }

        }

    }
}


void FIOModbus::on_pushButton_relay2_clicked(bool checked)
{
    qDebug() << " relay2 locking checked=" << checked;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    if(checked) // 真
    {
        // 02 06 00 00 00 00 89 F9
        quint8 cmd[] = {0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<1) ; // relay2 on
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if( cmdStatus(cmd,8) ) // 为真， 命令发送成功
            {
                qDebug() << "relay2 on" ;
                ui->pushButton_relay2->setPicture(":/images/relay2on.png");
            }
            else
            {
                ui->pushButton_relay2->setChecked(false) ; // 按钮 抬起
                qDebug() << "relay2 cmd failed";
                return ;
            }

        }
    }
    else
    {
        // 02 06 00 00 00 00 89 F9
        quint8 cmd[] = {0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<1)) ; // relay2 off
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if(cmdStatus(cmd,8) ) // 为真， 命令发送成功
            {
                qDebug() << "relay2 off" ;
                ui->pushButton_relay2->setPicture(":/images/relay2off.png");
            }
            else
            {
                ui->pushButton_relay2->setChecked(true) ; // 按钮 按压
                return ;
            }

        }

    }
}

void FIOModbus::on_pushButton_relay3_clicked(bool checked)
{
    qDebug() << " relay3 locking checked=" << checked;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    if(checked) // 真
    {
        // 02 06 00 00 00 00 89 F9
        quint8 cmd[] = {0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<2) ; // relay3 on
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if( cmdStatus(cmd,8) ) // 为真， 命令发送成功relay3 on
            {
                qDebug() << "relay3 on" ;
                ui->pushButton_relay3->setPicture(":/images/relay3on.png");
            }
            else
            {
                ui->pushButton_relay3->setChecked(false) ; // 按钮 抬起
                qDebug() << "relay3 cmd failed";
                return ;
            }

        }
    }
    else
    {
        // 02 06 00 00 00 00 89 F9
        quint8 cmd[] = {0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<2)) ; // relay3 off
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if(cmdStatus(cmd,8) ) // 为真， 命令发送成功
            {
                qDebug() << "relay3 off" ;
                ui->pushButton_relay3->setPicture(":/images/relay3off.png");
            }
            else
            {
                ui->pushButton_relay3->setChecked(true) ; // 按钮 按压
                return ;
            }

        }

    }
}


void FIOModbus::on_pushButton_relay4_clicked(bool checked)
{
    qDebug() << " relay4 locking checked=" << checked;
    QMutexLocker locker(&mutex) ; // 上锁 ， 函数返回后，自动释放锁
    if(checked) // 真
    {
        // 02 06 00 00 00 00 89 F9
        quint8 cmd[] = {0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit | (1<<3) ; // relay4 on
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if( cmdStatus(cmd,8) ) // 为真， 命令发送成功relay4 on
            {
                qDebug() << "relay4 on" ;
                ui->pushButton_relay4->setPicture(":/images/relay4on.png");
            }
            else
            {
                ui->pushButton_relay4->setChecked(false) ; // 按钮 抬起
                qDebug() << "relay4 cmd failed";
                return ;
            }

        }
    }
    else
    {
        // 02 06 00 00 00 00 89 F9
        quint8 cmd[] = {0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00};
        cmdConBit = cmdConBit & (~(1<<3)) ; // relay4 off
        cmd[5] = cmdConBit ;
        quint16 crc = make_crc(cmd,6);
        cmd[6] =crc &0xff; // 得到低8位
        cmd[7] =crc >> 8 ; // 得到高8位
        if(serial != nullptr)
        {
            serial->write((char *)cmd,8);
            if(cmdStatus(cmd,8) ) // 为真， 命令发送成功
            {
                qDebug() << "relay4 off" ;
                ui->pushButton_relay4->setPicture(":/images/relay4off.png");
            }
            else
            {
                ui->pushButton_relay4->setChecked(true) ; // 按钮 按压
                return ;
            }

        }

    }
}


