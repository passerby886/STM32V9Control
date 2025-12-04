#ifndef FIOMODBUS_H
#define FIOMODBUS_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMutex>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui {
class FIOModbus;
}
QT_END_NAMESPACE




class FIOModbus : public QWidget
{
    Q_OBJECT

public:
    FIOModbus(QWidget *parent = nullptr);
    ~FIOModbus();
    void initUi();
    unsigned int make_crc(unsigned char *puchMsg,unsigned int usDataLen);
    bool cmdReadBytes(quint8 readData[],quint8 n);
    bool cmdStatus(quint8 src_cmd[],quint8 n);

private slots:
    void timer_timeout_slot();

    void on_pushButton_open_clicked(bool checked);

    void on_pushButton_refresh_clicked();

    void on_pushButton_relay1_clicked(bool checked);

    void on_pushButton_relay2_clicked(bool checked);

    void on_pushButton_relay3_clicked(bool checked);

    void on_pushButton_relay4_clicked(bool checked);

private:
    Ui::FIOModbus *ui;
    QSerialPort *serial = nullptr ; // 串口指针
    quint8 cmdConBit = 0 ;  // 硬件控制的位
    QTimer *timer=nullptr;
    QMutex mutex; // 创建1把互斥锁

};
#endif // FIOMODBUS_H
