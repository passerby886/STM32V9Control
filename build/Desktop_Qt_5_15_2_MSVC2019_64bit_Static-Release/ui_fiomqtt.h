/********************************************************************************
** Form generated from reading UI file 'fiomqtt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIOMQTT_H
#define UI_FIOMQTT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "databutton.h"

QT_BEGIN_NAMESPACE

class Ui_FIOMqtt
{
public:
    DataButton *pushButton_in3;
    DataButton *pushButton_relay1;
    DataButton *pushButton_relay2;
    DataButton *pushButton_in4;
    DataButton *pushButton_in1;
    DataButton *pushButton_relay4;
    DataButton *pushButton_relay3;
    DataButton *pushButton_in2;
    QComboBox *comboBox_server;
    QLabel *label_server;
    QComboBox *comboBox_download;
    QPushButton *pushButton_server;
    QComboBox *comboBox_upload;
    QLabel *label_upload;
    QLabel *label_download;

    void setupUi(QWidget *FIOMqtt)
    {
        if (FIOMqtt->objectName().isEmpty())
            FIOMqtt->setObjectName(QString::fromUtf8("FIOMqtt"));
        FIOMqtt->resize(750, 700);
        pushButton_in3 = new DataButton(FIOMqtt);
        pushButton_in3->setObjectName(QString::fromUtf8("pushButton_in3"));
        pushButton_in3->setGeometry(QRect(520, 190, 200, 100));
        pushButton_relay1 = new DataButton(FIOMqtt);
        pushButton_relay1->setObjectName(QString::fromUtf8("pushButton_relay1"));
        pushButton_relay1->setGeometry(QRect(280, 330, 200, 100));
        pushButton_relay2 = new DataButton(FIOMqtt);
        pushButton_relay2->setObjectName(QString::fromUtf8("pushButton_relay2"));
        pushButton_relay2->setGeometry(QRect(520, 330, 200, 100));
        pushButton_in4 = new DataButton(FIOMqtt);
        pushButton_in4->setObjectName(QString::fromUtf8("pushButton_in4"));
        pushButton_in4->setGeometry(QRect(40, 330, 200, 100));
        pushButton_in1 = new DataButton(FIOMqtt);
        pushButton_in1->setObjectName(QString::fromUtf8("pushButton_in1"));
        pushButton_in1->setGeometry(QRect(40, 190, 200, 100));
        pushButton_relay4 = new DataButton(FIOMqtt);
        pushButton_relay4->setObjectName(QString::fromUtf8("pushButton_relay4"));
        pushButton_relay4->setGeometry(QRect(280, 470, 200, 100));
        pushButton_relay3 = new DataButton(FIOMqtt);
        pushButton_relay3->setObjectName(QString::fromUtf8("pushButton_relay3"));
        pushButton_relay3->setGeometry(QRect(40, 470, 200, 100));
        pushButton_in2 = new DataButton(FIOMqtt);
        pushButton_in2->setObjectName(QString::fromUtf8("pushButton_in2"));
        pushButton_in2->setGeometry(QRect(280, 190, 200, 100));
        comboBox_server = new QComboBox(FIOMqtt);
        comboBox_server->addItem(QString());
        comboBox_server->setObjectName(QString::fromUtf8("comboBox_server"));
        comboBox_server->setGeometry(QRect(150, 20, 400, 30));
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        comboBox_server->setFont(font);
        comboBox_server->setEditable(true);
        label_server = new QLabel(FIOMqtt);
        label_server->setObjectName(QString::fromUtf8("label_server"));
        label_server->setGeometry(QRect(40, 20, 101, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(14);
        font1.setBold(true);
        label_server->setFont(font1);
        comboBox_download = new QComboBox(FIOMqtt);
        comboBox_download->addItem(QString());
        comboBox_download->setObjectName(QString::fromUtf8("comboBox_download"));
        comboBox_download->setGeometry(QRect(150, 120, 571, 30));
        comboBox_download->setFont(font);
        pushButton_server = new QPushButton(FIOMqtt);
        pushButton_server->setObjectName(QString::fromUtf8("pushButton_server"));
        pushButton_server->setGeometry(QRect(570, 20, 150, 30));
        comboBox_upload = new QComboBox(FIOMqtt);
        comboBox_upload->addItem(QString());
        comboBox_upload->setObjectName(QString::fromUtf8("comboBox_upload"));
        comboBox_upload->setGeometry(QRect(150, 70, 571, 30));
        comboBox_upload->setFont(font);
        label_upload = new QLabel(FIOMqtt);
        label_upload->setObjectName(QString::fromUtf8("label_upload"));
        label_upload->setGeometry(QRect(40, 70, 101, 30));
        label_upload->setFont(font1);
        label_download = new QLabel(FIOMqtt);
        label_download->setObjectName(QString::fromUtf8("label_download"));
        label_download->setGeometry(QRect(40, 120, 101, 30));
        label_download->setFont(font1);

        retranslateUi(FIOMqtt);

        QMetaObject::connectSlotsByName(FIOMqtt);
    } // setupUi

    void retranslateUi(QWidget *FIOMqtt)
    {
        FIOMqtt->setWindowTitle(QCoreApplication::translate("FIOMqtt", "Widget", nullptr));
        pushButton_in3->setText(QString());
        pushButton_relay1->setText(QString());
        pushButton_relay2->setText(QString());
        pushButton_in4->setText(QString());
        pushButton_in1->setText(QString());
        pushButton_relay4->setText(QString());
        pushButton_relay3->setText(QString());
        pushButton_in2->setText(QString());
        comboBox_server->setItemText(0, QCoreApplication::translate("FIOMqtt", "broker.emqx.io", nullptr));

        label_server->setText(QCoreApplication::translate("FIOMqtt", "\346\234\215\345\212\241\345\231\250", nullptr));
        comboBox_download->setItemText(0, QCoreApplication::translate("FIOMqtt", "FourIO/DownLoad/43151025325847310673FF30", nullptr));

        pushButton_server->setText(QCoreApplication::translate("FIOMqtt", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        comboBox_upload->setItemText(0, QCoreApplication::translate("FIOMqtt", "FourIO/UPLoad/43151025325847310673FF30", nullptr));

        label_upload->setText(QCoreApplication::translate("FIOMqtt", "\344\270\212\350\241\214\344\270\273\351\242\230", nullptr));
        label_download->setText(QCoreApplication::translate("FIOMqtt", "\344\270\213\350\241\214\344\270\273\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FIOMqtt: public Ui_FIOMqtt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIOMQTT_H
