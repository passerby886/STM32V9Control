/********************************************************************************
** Form generated from reading UI file 'fiocanopen.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIOCANOPEN_H
#define UI_FIOCANOPEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "databutton.h"

QT_BEGIN_NAMESPACE

class Ui_FIOCANopen
{
public:
    DataButton *pushButton_in3;
    DataButton *pushButton_relay1;
    DataButton *pushButton_relay2;
    QPushButton *pushButton_open;
    DataButton *pushButton_in4;
    DataButton *pushButton_in1;
    DataButton *pushButton_relay4;
    QLabel *label_server;
    DataButton *pushButton_relay3;
    DataButton *pushButton_in2;
    QComboBox *comboBox_can;
    QPushButton *pushButton_refresh;

    void setupUi(QWidget *FIOCANopen)
    {
        if (FIOCANopen->objectName().isEmpty())
            FIOCANopen->setObjectName(QString::fromUtf8("FIOCANopen"));
        FIOCANopen->resize(750, 700);
        pushButton_in3 = new DataButton(FIOCANopen);
        pushButton_in3->setObjectName(QString::fromUtf8("pushButton_in3"));
        pushButton_in3->setGeometry(QRect(520, 140, 200, 100));
        pushButton_relay1 = new DataButton(FIOCANopen);
        pushButton_relay1->setObjectName(QString::fromUtf8("pushButton_relay1"));
        pushButton_relay1->setGeometry(QRect(280, 280, 200, 100));
        pushButton_relay2 = new DataButton(FIOCANopen);
        pushButton_relay2->setObjectName(QString::fromUtf8("pushButton_relay2"));
        pushButton_relay2->setGeometry(QRect(520, 280, 200, 100));
        pushButton_open = new QPushButton(FIOCANopen);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));
        pushButton_open->setGeometry(QRect(500, 50, 100, 40));
        pushButton_in4 = new DataButton(FIOCANopen);
        pushButton_in4->setObjectName(QString::fromUtf8("pushButton_in4"));
        pushButton_in4->setGeometry(QRect(40, 280, 200, 100));
        pushButton_in1 = new DataButton(FIOCANopen);
        pushButton_in1->setObjectName(QString::fromUtf8("pushButton_in1"));
        pushButton_in1->setGeometry(QRect(40, 140, 200, 100));
        pushButton_relay4 = new DataButton(FIOCANopen);
        pushButton_relay4->setObjectName(QString::fromUtf8("pushButton_relay4"));
        pushButton_relay4->setGeometry(QRect(280, 420, 200, 100));
        label_server = new QLabel(FIOCANopen);
        label_server->setObjectName(QString::fromUtf8("label_server"));
        label_server->setGeometry(QRect(40, 50, 101, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(14);
        font.setBold(true);
        label_server->setFont(font);
        pushButton_relay3 = new DataButton(FIOCANopen);
        pushButton_relay3->setObjectName(QString::fromUtf8("pushButton_relay3"));
        pushButton_relay3->setGeometry(QRect(40, 420, 200, 100));
        pushButton_in2 = new DataButton(FIOCANopen);
        pushButton_in2->setObjectName(QString::fromUtf8("pushButton_in2"));
        pushButton_in2->setGeometry(QRect(280, 140, 200, 100));
        comboBox_can = new QComboBox(FIOCANopen);
        comboBox_can->setObjectName(QString::fromUtf8("comboBox_can"));
        comboBox_can->setGeometry(QRect(150, 50, 321, 40));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        comboBox_can->setFont(font1);
        comboBox_can->setEditable(false);
        pushButton_refresh = new QPushButton(FIOCANopen);
        pushButton_refresh->setObjectName(QString::fromUtf8("pushButton_refresh"));
        pushButton_refresh->setGeometry(QRect(620, 50, 100, 40));

        retranslateUi(FIOCANopen);

        QMetaObject::connectSlotsByName(FIOCANopen);
    } // setupUi

    void retranslateUi(QWidget *FIOCANopen)
    {
        FIOCANopen->setWindowTitle(QCoreApplication::translate("FIOCANopen", "Widget", nullptr));
        pushButton_in3->setText(QString());
        pushButton_relay1->setText(QString());
        pushButton_relay2->setText(QString());
        pushButton_open->setText(QCoreApplication::translate("FIOCANopen", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        pushButton_in4->setText(QString());
        pushButton_in1->setText(QString());
        pushButton_relay4->setText(QString());
        label_server->setText(QCoreApplication::translate("FIOCANopen", "CAN\350\256\276\345\244\207", nullptr));
        pushButton_relay3->setText(QString());
        pushButton_in2->setText(QString());
        pushButton_refresh->setText(QCoreApplication::translate("FIOCANopen", "\345\210\267\346\226\260\350\256\276\345\244\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FIOCANopen: public Ui_FIOCANopen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIOCANOPEN_H
