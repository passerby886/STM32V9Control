/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "databutton.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QListWidget *listWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    DataButton *pushButton_led1;
    DataButton *pushButton_led2;
    DataButton *pushButton_beep;
    DataButton *pushButton_hum;
    DataButton *pushButton_relay;
    DataButton *pushButton_temp;
    DataButton *pushButton_vol;
    DataButton *pushButton_cpu;
    DataButton *pushButton_vr;
    DataButton *pushButton_cur;
    DataButton *pushButton_pw;
    QPushButton *pushButton_open;
    QPushButton *pushButton_refresh;
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1000, 700);
        Widget->setMinimumSize(QSize(1000, 700));
        Widget->setMaximumSize(QSize(1000, 700));
        listWidget = new QListWidget(Widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 250, 700));
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(250, 0, 750, 700));
        tabWidget->setMinimumSize(QSize(750, 700));
        tabWidget->setMaximumSize(QSize(750, 700));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        tabWidget->setFont(font);
        tabWidget->setTabBarAutoHide(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        pushButton_led1 = new DataButton(tab);
        pushButton_led1->setObjectName(QString::fromUtf8("pushButton_led1"));
        pushButton_led1->setGeometry(QRect(30, 120, 200, 100));
        pushButton_led1->setFont(font);
        pushButton_led2 = new DataButton(tab);
        pushButton_led2->setObjectName(QString::fromUtf8("pushButton_led2"));
        pushButton_led2->setGeometry(QRect(270, 120, 200, 100));
        pushButton_led2->setFont(font);
        pushButton_beep = new DataButton(tab);
        pushButton_beep->setObjectName(QString::fromUtf8("pushButton_beep"));
        pushButton_beep->setGeometry(QRect(510, 120, 200, 100));
        pushButton_beep->setFont(font);
        pushButton_hum = new DataButton(tab);
        pushButton_hum->setObjectName(QString::fromUtf8("pushButton_hum"));
        pushButton_hum->setGeometry(QRect(510, 270, 200, 100));
        pushButton_hum->setFont(font);
        pushButton_relay = new DataButton(tab);
        pushButton_relay->setObjectName(QString::fromUtf8("pushButton_relay"));
        pushButton_relay->setGeometry(QRect(30, 270, 200, 100));
        pushButton_relay->setFont(font);
        pushButton_temp = new DataButton(tab);
        pushButton_temp->setObjectName(QString::fromUtf8("pushButton_temp"));
        pushButton_temp->setGeometry(QRect(270, 270, 200, 100));
        pushButton_temp->setFont(font);
        pushButton_vol = new DataButton(tab);
        pushButton_vol->setObjectName(QString::fromUtf8("pushButton_vol"));
        pushButton_vol->setGeometry(QRect(510, 420, 200, 100));
        pushButton_vol->setFont(font);
        pushButton_cpu = new DataButton(tab);
        pushButton_cpu->setObjectName(QString::fromUtf8("pushButton_cpu"));
        pushButton_cpu->setGeometry(QRect(30, 420, 200, 100));
        pushButton_cpu->setFont(font);
        pushButton_vr = new DataButton(tab);
        pushButton_vr->setObjectName(QString::fromUtf8("pushButton_vr"));
        pushButton_vr->setGeometry(QRect(270, 420, 200, 100));
        pushButton_vr->setFont(font);
        pushButton_cur = new DataButton(tab);
        pushButton_cur->setObjectName(QString::fromUtf8("pushButton_cur"));
        pushButton_cur->setGeometry(QRect(30, 560, 200, 100));
        pushButton_cur->setFont(font);
        pushButton_pw = new DataButton(tab);
        pushButton_pw->setObjectName(QString::fromUtf8("pushButton_pw"));
        pushButton_pw->setGeometry(QRect(270, 560, 200, 100));
        pushButton_pw->setFont(font);
        pushButton_open = new QPushButton(tab);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));
        pushButton_open->setGeometry(QRect(500, 30, 100, 40));
        pushButton_refresh = new QPushButton(tab);
        pushButton_refresh->setObjectName(QString::fromUtf8("pushButton_refresh"));
        pushButton_refresh->setGeometry(QRect(620, 30, 100, 40));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(130, 30, 341, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font1.setPointSize(10);
        comboBox->setFont(font1);
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 30, 69, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font2.setPointSize(14);
        font2.setBold(true);
        label->setFont(font2);
        tabWidget->addTab(tab, QString());

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\347\211\251\350\201\224\347\275\221\350\256\276\345\244\207\347\256\241\347\220\206\345\271\263\345\217\260 2.0", nullptr));
        pushButton_led1->setText(QString());
        pushButton_led2->setText(QString());
        pushButton_beep->setText(QString());
        pushButton_hum->setText(QString());
        pushButton_relay->setText(QString());
        pushButton_temp->setText(QString());
        pushButton_vol->setText(QString());
        pushButton_cpu->setText(QString());
        pushButton_vr->setText(QString());
        pushButton_cur->setText(QString());
        pushButton_pw->setText(QString());
        pushButton_open->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        pushButton_refresh->setText(QCoreApplication::translate("Widget", "\345\210\267\346\226\260\344\270\262\345\217\243", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\345\217\267", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Widget", "Tab 1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
