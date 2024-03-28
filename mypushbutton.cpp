#include "mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QPropertyAnimation>
MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}
MyPushButton::MyPushButton( QString normalPath,QString pushPath)
{
    this->normalPath = normalPath;
    this->pushPath = pushPath;
    //加载图片
    QPixmap pix;

    //判断图片是否加载成功
    bool set = pix.load(normalPath);
    if(!set)
    {
        qDebug()<<QString::fromStdWString(L"图片加载失败");
    }
    else
    {
        qDebug()<<QString::fromStdWString(L"图片加载成功");
    }

    //设置按钮尺寸
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(this->width(),this->height()));

}

void MyPushButton::jumpUp()
{

    //1、为准备进行动画动作的对象
    //2、动作对象变更的属性
    //3、对象的父对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);


    //设置事件间隔,动作时间
    animation->setDuration(200);

    //设置开始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}

void MyPushButton::jumpDown()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);


    //设置事件间隔,动作时间
    animation->setDuration(200);

    //设置开始位置
    animation->setStartValue(QRect(this->x(),this->y()-10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}


//重写鼠标事件
void MyPushButton::mousePressEvent(QMouseEvent *ev)
{
    if(this->pushPath != "")
    {
        QPixmap pix;
        bool load = pix.load(this->pushPath);
        if(!load)
        {
            qDebug()<<QString::fromStdWString(L"图片加载失败");
            return QPushButton::mousePressEvent(ev);
        }
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        this->setStyleSheet("QPushButton{border:0px;}");
    }
    return QPushButton::mousePressEvent(ev);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *ev)
{
    if(this->normalPath!="")
    {
        QPixmap pix;
        bool load = pix.load(this->normalPath);
        if(!load)
        {
            qDebug()<<QString::fromStdWString(L"图片加载失败");
            return QPushButton::mouseReleaseEvent(ev);
        }
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        this->setStyleSheet("QPushButton{border:0px;}");
    }
    return QPushButton::mouseReleaseEvent(ev);

}

