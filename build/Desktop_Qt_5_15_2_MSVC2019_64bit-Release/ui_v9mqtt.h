/********************************************************************************
** Form generated from reading UI file 'v9mqtt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_V9MQTT_H
#define UI_V9MQTT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "databutton.h"

QT_BEGIN_NAMESPACE

class Ui_V9Mqtt
{
public:
    DataButton *pushButton_beep;
    DataButton *pushButton_temp;
    DataButton *pushButton_hum;
    QPushButton *pushButton_server;
    DataButton *pushButton_relay;
    DataButton *pushButton_led1;
    DataButton *pushButton_vr;
    QLabel *label_server;
    DataButton *pushButton_cpu;
    DataButton *pushButton_cur;
    DataButton *pushButton_led2;
    DataButton *pushButton_vol;
    QComboBox *comboBox_server;
    DataButton *pushButton_pw;
    QComboBox *comboBox_upload;
    QLabel *label_upload;
    QComboBox *comboBox_download;
    QLabel *label_download;

    void setupUi(QWidget *V9Mqtt)
    {
        if (V9Mqtt->objectName().isEmpty())
            V9Mqtt->setObjectName(QString::fromUtf8("V9Mqtt"));
        V9Mqtt->resize(750, 700);
        pushButton_beep = new DataButton(V9Mqtt);
        pushButton_beep->setObjectName(QString::fromUtf8("pushButton_beep"));
        pushButton_beep->setGeometry(QRect(520, 180, 200, 100));
        pushButton_temp = new DataButton(V9Mqtt);
        pushButton_temp->setObjectName(QString::fromUtf8("pushButton_temp"));
        pushButton_temp->setGeometry(QRect(280, 310, 200, 100));
        pushButton_hum = new DataButton(V9Mqtt);
        pushButton_hum->setObjectName(QString::fromUtf8("pushButton_hum"));
        pushButton_hum->setGeometry(QRect(520, 310, 200, 100));
        pushButton_server = new QPushButton(V9Mqtt);
        pushButton_server->setObjectName(QString::fromUtf8("pushButton_server"));
        pushButton_server->setGeometry(QRect(580, 20, 150, 30));
        pushButton_relay = new DataButton(V9Mqtt);
        pushButton_relay->setObjectName(QString::fromUtf8("pushButton_relay"));
        pushButton_relay->setGeometry(QRect(40, 310, 200, 100));
        pushButton_led1 = new DataButton(V9Mqtt);
        pushButton_led1->setObjectName(QString::fromUtf8("pushButton_led1"));
        pushButton_led1->setGeometry(QRect(40, 180, 200, 100));
        pushButton_vr = new DataButton(V9Mqtt);
        pushButton_vr->setObjectName(QString::fromUtf8("pushButton_vr"));
        pushButton_vr->setGeometry(QRect(280, 440, 200, 100));
        label_server = new QLabel(V9Mqtt);
        label_server->setObjectName(QString::fromUtf8("label_server"));
        label_server->setGeometry(QRect(50, 20, 101, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(14);
        font.setBold(true);
        label_server->setFont(font);
        pushButton_cpu = new DataButton(V9Mqtt);
        pushButton_cpu->setObjectName(QString::fromUtf8("pushButton_cpu"));
        pushButton_cpu->setGeometry(QRect(40, 440, 200, 100));
        pushButton_cur = new DataButton(V9Mqtt);
        pushButton_cur->setObjectName(QString::fromUtf8("pushButton_cur"));
        pushButton_cur->setGeometry(QRect(40, 570, 200, 100));
        pushButton_led2 = new DataButton(V9Mqtt);
        pushButton_led2->setObjectName(QString::fromUtf8("pushButton_led2"));
        pushButton_led2->setGeometry(QRect(280, 180, 200, 100));
        pushButton_vol = new DataButton(V9Mqtt);
        pushButton_vol->setObjectName(QString::fromUtf8("pushButton_vol"));
        pushButton_vol->setGeometry(QRect(520, 440, 200, 100));
        comboBox_server = new QComboBox(V9Mqtt);
        comboBox_server->addItem(QString());
        comboBox_server->setObjectName(QString::fromUtf8("comboBox_server"));
        comboBox_server->setGeometry(QRect(160, 20, 400, 30));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        comboBox_server->setFont(font1);
        comboBox_server->setEditable(true);
        pushButton_pw = new DataButton(V9Mqtt);
        pushButton_pw->setObjectName(QString::fromUtf8("pushButton_pw"));
        pushButton_pw->setGeometry(QRect(280, 570, 200, 100));
        comboBox_upload = new QComboBox(V9Mqtt);
        comboBox_upload->addItem(QString());
        comboBox_upload->setObjectName(QString::fromUtf8("comboBox_upload"));
        comboBox_upload->setGeometry(QRect(160, 70, 571, 30));
        comboBox_upload->setFont(font1);
        label_upload = new QLabel(V9Mqtt);
        label_upload->setObjectName(QString::fromUtf8("label_upload"));
        label_upload->setGeometry(QRect(50, 70, 101, 30));
        label_upload->setFont(font);
        comboBox_download = new QComboBox(V9Mqtt);
        comboBox_download->addItem(QString());
        comboBox_download->setObjectName(QString::fromUtf8("comboBox_download"));
        comboBox_download->setGeometry(QRect(160, 120, 571, 30));
        comboBox_download->setFont(font1);
        label_download = new QLabel(V9Mqtt);
        label_download->setObjectName(QString::fromUtf8("label_download"));
        label_download->setGeometry(QRect(50, 120, 101, 30));
        label_download->setFont(font);

        retranslateUi(V9Mqtt);

        QMetaObject::connectSlotsByName(V9Mqtt);
    } // setupUi

    void retranslateUi(QWidget *V9Mqtt)
    {
        V9Mqtt->setWindowTitle(QCoreApplication::translate("V9Mqtt", "Widget", nullptr));
        pushButton_beep->setText(QString());
        pushButton_temp->setText(QString());
        pushButton_hum->setText(QString());
        pushButton_server->setText(QCoreApplication::translate("V9Mqtt", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_relay->setText(QString());
        pushButton_led1->setText(QString());
        pushButton_vr->setText(QString());
        label_server->setText(QCoreApplication::translate("V9Mqtt", "\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_cpu->setText(QString());
        pushButton_cur->setText(QString());
        pushButton_led2->setText(QString());
        pushButton_vol->setText(QString());
        comboBox_server->setItemText(0, QCoreApplication::translate("V9Mqtt", "broker.emqx.io", nullptr));

        pushButton_pw->setText(QString());
        comboBox_upload->setItemText(0, QCoreApplication::translate("V9Mqtt", "STM32V9/UPLoad/5718402539345041066CFF36", nullptr));

        label_upload->setText(QCoreApplication::translate("V9Mqtt", "\344\270\212\350\241\214\344\270\273\351\242\230", nullptr));
        comboBox_download->setItemText(0, QCoreApplication::translate("V9Mqtt", "STM32V9/DownLoad/5718402539345041066CFF36", nullptr));

        label_download->setText(QCoreApplication::translate("V9Mqtt", "\344\270\213\350\241\214\344\270\273\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class V9Mqtt: public Ui_V9Mqtt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_V9MQTT_H
