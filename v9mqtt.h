#ifndef V9MQTT_H
#define V9MQTT_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QScrollBar>
#include <QtMqtt/QMqttClient>
#include <QJsonObject>
#include <QJsonDocument>



QT_BEGIN_NAMESPACE
namespace Ui {
class V9Mqtt;
}
QT_END_NAMESPACE

class V9Mqtt : public QWidget
{
    Q_OBJECT

public:
    V9Mqtt(QWidget *parent = nullptr);
    ~V9Mqtt();
    void initUi();

private slots:

    void on_pushButton_server_clicked(bool checked);

    void stateChanged_slot(QMqttClient::ClientState state);

    void messageReceived_slot(const QByteArray &message, const QMqttTopicName &topic);

    void on_pushButton_led1_clicked(bool checked);

    void on_pushButton_led2_clicked(bool checked);

    void on_pushButton_beep_clicked(bool checked);

    void on_pushButton_relay_clicked(bool checked);

private:
    Ui::V9Mqtt *ui;
    QMqttClient *mqttclient = nullptr; // 定义1个mqtt客户端
};
#endif // V9MQTT_H
