#ifndef WIDGET_H
#define WIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QScrollBar>
#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initUi();
    bool cmdReadBytes(quint8 readData[],quint8 n);
    bool cmdStatus(quint8 src_cmd[],quint8 n);

private slots:
    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_open_clicked(bool checked);

    void on_pushButton_refresh_clicked();

    void on_pushButton_led1_clicked(bool checked);

    void timer_timeout_slot();

    void on_pushButton_led2_clicked(bool checked);

    void on_pushButton_beep_clicked(bool checked);

    void on_pushButton_relay_clicked(bool checked);

private:
    Ui::Widget *ui;
    QSerialPort *serial = nullptr ; // 串口指针
    quint8 cmdConBit = 0 ;  // 硬件控制的位
    QTimer *timer=nullptr;
    QMutex mutex; // 创建1把互斥锁
};
#endif // WIDGET_H
