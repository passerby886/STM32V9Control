#include "databutton.h"

DataButton::DataButton(QWidget *parent ):QPushButton(parent)
{
    value = "";
    xoffset = 30 ;

}

void DataButton::setPicture(const QString &pic)
{
    this->picture = pic ;
    update();
}

void DataButton::setXOffset(int xoff)
{
    this->xoffset = xoff;
    update();
}

void DataButton::setValue(const QString &val)
{
    this->value = val;
    update();
}


void DataButton::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QString pic = picture ;
    if(!pic.isEmpty())
    {
        painter.drawPixmap(this->rect(),QPixmap(pic).scaled(this->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    painter.setPen(Qt::white);
    QFont font =  painter.font();
    font.setPixelSize(24);
    font.setBold(true);
    painter.setFont(font); // 设置字体的大小

    // 获取按钮的中心点
    QPoint centerPoint =   this->rect().center() ;
    centerPoint.setX(centerPoint.x() + xoffset); //x方向的偏移量
    centerPoint.setY(centerPoint.y() + 28); //y方向的偏移量
    painter.drawText(centerPoint,value);


}

