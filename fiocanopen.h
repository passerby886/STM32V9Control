#ifndef FIOCANOPEN_H
#define FIOCANOPEN_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include "api/candle.h"
#include <QtConcurrent>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class FIOCANopen;
}
QT_END_NAMESPACE


class FIOCANopen : public QWidget
{
    Q_OBJECT

    struct CanDevice
    {
        candle_handle handle;
        uint32_t id;
        QString name;
        QString desc; // 驱动描述
    };
public:
    FIOCANopen(QWidget *parent = nullptr);
    ~FIOCANopen();
    void initUi();
    void readMessage();


signals:
    void SigReceiveCanData(quint32 recv_id,quint8 dlc,QByteArray data);

private slots:

    void on_pushButton_refresh_clicked();

    void on_pushButton_open_clicked(bool checked);

    void on_pushButton_relay1_clicked(bool checked);

    void on_pushButton_relay2_clicked(bool checked);

    void on_pushButton_relay3_clicked(bool checked);

    void on_pushButton_relay4_clicked(bool checked);

    void timer_timeout_slot();

    void SlotReceiveCanData(quint32 recv_id,quint8 dlc, QByteArray data);


private:
    Ui::FIOCANopen *ui;
    QList<CanDevice> devices; // 定义1个 CanDevice 链表
    QFuture<void> future;// 定义个函数模板类
    quint8 cmdConBit = 0 ;  // 硬件控制的位
    QTimer *timer;

};
#endif // FIOCANOPEN_H
