#ifndef FIOMQTT_H
#define FIOMQTT_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QtMqtt/QMqttClient>
#include <QJsonObject>
#include <QJsonDocument>


QT_BEGIN_NAMESPACE
namespace Ui {
class FIOMqtt;
}
QT_END_NAMESPACE



class FIOMqtt : public QWidget
{
    Q_OBJECT

public:
    FIOMqtt(QWidget *parent = nullptr);
    ~FIOMqtt();
    void initUi();


private slots:

    void on_pushButton_server_clicked(bool checked);

    void stateChanged_slot(QMqttClient::ClientState state);

    void messageReceived_slot(const QByteArray &message, const QMqttTopicName &topic);

    void on_pushButton_relay1_clicked(bool checked);

    void on_pushButton_relay2_clicked(bool checked);

    void on_pushButton_relay3_clicked(bool checked);

    void on_pushButton_relay4_clicked(bool checked);


private:
    Ui::FIOMqtt *ui;
    QMqttClient *mqttclient = nullptr; // 定义1个mqtt客户端

};
#endif // FIOMQTT_H
