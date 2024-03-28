#include "coin.h"
#include <QPixmap>
#include <QDebug>
Coin::Coin(QWidget *parent) : QPushButton(parent)
{

}
Coin::Coin(QString path)
{
    QPixmap pix;
    bool res = pix.load(path);
    if(!res)
    {
        qDebug()<<QString::fromStdWString(L"图片加载失败");
    }

    this->setFixedSize(pix.width(),pix.height());

    this->setIcon(QIcon(pix));

    this->setIconSize(QSize(this->width(),this->height()));

    this->setStyleSheet("QPushButton{border:0px;}");

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //翻金币
    connect(this->timer1,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString path = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(path);
        this->setIcon(pix);
        this->setIconSize(QSize(this->width(),this->height()));
        if(this->min>this->max)
        {
            this->min = 1;
            this->timer1->stop();
            this->isAnimation = false;
        }
    });
    connect(this->timer2,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString path = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(path);
        this->setIcon(pix);
        this->setIconSize(QSize(this->width(),this->height()));
        if(this->min>this->max)
        {
            this->max = 8;
            this->timer2->stop();
            this->isAnimation = false;
        }
    });

}

int Coin::getPox_y() const
{
    return pox_y;
}

void Coin::setPox_y(int value)
{
    pox_y = value;
}

int Coin::getPos_x() const
{
    return pos_x;
}

void Coin::setPos_x(int value)
{
    pos_x = value;
}

bool Coin::getFlag() const
{
    return flag;
}

void Coin::setFlag(bool value)
{
    flag = value;
}

void Coin::changeFlag()
{
    if(this->getFlag()==true)
    {
        this->timer1->start(30);
        this->setFlag(false);
    }
    else
    {
        this->timer2->start(30);
        this->setFlag(true);
    }
    this->isAnimation = true;
}



void Coin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation||this->isWin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }

}
