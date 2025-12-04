#ifndef DATABUTTON_H
#define DATABUTTON_H
#include <QPushButton>
#include <QDebug>
#include <QPainter>

class DataButton : public QPushButton
{
    Q_OBJECT
public:
    explicit DataButton(QWidget *parent = nullptr );

    void setPicture(const QString &pic);
    void setXOffset(int xOffset);
    void setValue(const QString &value);

protected:
    void paintEvent(QPaintEvent * event) override ;

private:
    QString picture ; //显示的图片
    QString value; // 按钮要显示的值
    qint32  xoffset = 0 ;
};

#endif // DATABUTTON_H
