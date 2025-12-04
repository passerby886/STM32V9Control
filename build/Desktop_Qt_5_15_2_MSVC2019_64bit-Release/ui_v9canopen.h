/********************************************************************************
** Form generated from reading UI file 'v9canopen.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_V9CANOPEN_H
#define UI_V9CANOPEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "databutton.h"

QT_BEGIN_NAMESPACE

class Ui_V9CANopen
{
public:
    DataButton *pushButton_beep;
    DataButton *pushButton_temp;
    DataButton *pushButton_hum;
    QPushButton *pushButton_open;
    DataButton *pushButton_relay;
    DataButton *pushButton_led1;
    DataButton *pushButton_vr;
    QLabel *label_server;
    DataButton *pushButton_cpu;
    DataButton *pushButton_cur;
    DataButton *pushButton_led2;
    DataButton *pushButton_vol;
    QComboBox *comboBox_can;
    DataButton *pushButton_pw;
    QPushButton *pushButton_refresh;

    void setupUi(QWidget *V9CANopen)
    {
        if (V9CANopen->objectName().isEmpty())
            V9CANopen->setObjectName(QString::fromUtf8("V9CANopen"));
        V9CANopen->resize(750, 700);
        pushButton_beep = new DataButton(V9CANopen);
        pushButton_beep->setObjectName(QString::fromUtf8("pushButton_beep"));
        pushButton_beep->setGeometry(QRect(520, 160, 200, 100));
        pushButton_temp = new DataButton(V9CANopen);
        pushButton_temp->setObjectName(QString::fromUtf8("pushButton_temp"));
        pushButton_temp->setGeometry(QRect(280, 290, 200, 100));
        pushButton_hum = new DataButton(V9CANopen);
        pushButton_hum->setObjectName(QString::fromUtf8("pushButton_hum"));
        pushButton_hum->setGeometry(QRect(520, 290, 200, 100));
        pushButton_open = new QPushButton(V9CANopen);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));
        pushButton_open->setGeometry(QRect(500, 50, 100, 40));
        pushButton_relay = new DataButton(V9CANopen);
        pushButton_relay->setObjectName(QString::fromUtf8("pushButton_relay"));
        pushButton_relay->setGeometry(QRect(40, 290, 200, 100));
        pushButton_led1 = new DataButton(V9CANopen);
        pushButton_led1->setObjectName(QString::fromUtf8("pushButton_led1"));
        pushButton_led1->setGeometry(QRect(40, 160, 200, 100));
        pushButton_vr = new DataButton(V9CANopen);
        pushButton_vr->setObjectName(QString::fromUtf8("pushButton_vr"));
        pushButton_vr->setGeometry(QRect(280, 420, 200, 100));
        label_server = new QLabel(V9CANopen);
        label_server->setObjectName(QString::fromUtf8("label_server"));
        label_server->setGeometry(QRect(40, 50, 101, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(14);
        font.setBold(true);
        label_server->setFont(font);
        pushButton_cpu = new DataButton(V9CANopen);
        pushButton_cpu->setObjectName(QString::fromUtf8("pushButton_cpu"));
        pushButton_cpu->setGeometry(QRect(40, 420, 200, 100));
        pushButton_cur = new DataButton(V9CANopen);
        pushButton_cur->setObjectName(QString::fromUtf8("pushButton_cur"));
        pushButton_cur->setGeometry(QRect(40, 550, 200, 100));
        pushButton_led2 = new DataButton(V9CANopen);
        pushButton_led2->setObjectName(QString::fromUtf8("pushButton_led2"));
        pushButton_led2->setGeometry(QRect(280, 160, 200, 100));
        pushButton_vol = new DataButton(V9CANopen);
        pushButton_vol->setObjectName(QString::fromUtf8("pushButton_vol"));
        pushButton_vol->setGeometry(QRect(520, 420, 200, 100));
        comboBox_can = new QComboBox(V9CANopen);
        comboBox_can->setObjectName(QString::fromUtf8("comboBox_can"));
        comboBox_can->setGeometry(QRect(150, 50, 321, 40));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        comboBox_can->setFont(font1);
        comboBox_can->setEditable(true);
        pushButton_pw = new DataButton(V9CANopen);
        pushButton_pw->setObjectName(QString::fromUtf8("pushButton_pw"));
        pushButton_pw->setGeometry(QRect(280, 550, 200, 100));
        pushButton_refresh = new QPushButton(V9CANopen);
        pushButton_refresh->setObjectName(QString::fromUtf8("pushButton_refresh"));
        pushButton_refresh->setGeometry(QRect(620, 50, 100, 40));

        retranslateUi(V9CANopen);

        QMetaObject::connectSlotsByName(V9CANopen);
    } // setupUi

    void retranslateUi(QWidget *V9CANopen)
    {
        V9CANopen->setWindowTitle(QCoreApplication::translate("V9CANopen", "Widget", nullptr));
        pushButton_beep->setText(QString());
        pushButton_temp->setText(QString());
        pushButton_hum->setText(QString());
        pushButton_open->setText(QCoreApplication::translate("V9CANopen", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        pushButton_relay->setText(QString());
        pushButton_led1->setText(QString());
        pushButton_vr->setText(QString());
        label_server->setText(QCoreApplication::translate("V9CANopen", "CAN\350\256\276\345\244\207", nullptr));
        pushButton_cpu->setText(QString());
        pushButton_cur->setText(QString());
        pushButton_led2->setText(QString());
        pushButton_vol->setText(QString());
        pushButton_pw->setText(QString());
        pushButton_refresh->setText(QCoreApplication::translate("V9CANopen", "\345\210\267\346\226\260\350\256\276\345\244\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class V9CANopen: public Ui_V9CANopen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_V9CANOPEN_H
