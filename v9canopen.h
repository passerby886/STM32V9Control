#ifndef V9CANOPEN_H
#define V9CANOPEN_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "api/candle.h"
#include <QtConcurrent>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class V9CANopen;
}
QT_END_NAMESPACE


struct CanDevice
{
    candle_handle handle;
    uint32_t id;
    QString name;
    QString desc; // 驱动描述
};



class V9CANopen : public QWidget
{
    Q_OBJECT

public:
    V9CANopen(QWidget *parent = nullptr);
    ~V9CANopen();
    void initUi();
    void readMessage();

signals:
    void SigReceiveCanData(quint32 recv_id,quint8 dlc,QByteArray data);

private slots:

    void on_pushButton_refresh_clicked();

    void on_pushButton_open_clicked(bool checked);

    void on_pushButton_led1_clicked(bool checked);

    void on_pushButton_led2_clicked(bool checked);

    void on_pushButton_beep_clicked(bool checked);

    void on_pushButton_relay_clicked(bool checked);

    void timer_timeout_slot();

    void SlotReceiveCanData(quint32 recv_id,quint8 dlc, QByteArray data);

private:
    Ui::V9CANopen *ui;
    QList<CanDevice> devices; // 定义1个 CanDevice 链表
    QFuture<void> future;// 定义个函数模板类
    quint8 cmdConBit = 0 ;  // 硬件控制的位
    QTimer *timer;

};
#endif // V9CANopen_H
