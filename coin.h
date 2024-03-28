#ifndef COIN_H
#define COIN_H
#include<QTimer>
#include <QPushButton>

class Coin : public QPushButton
{
    Q_OBJECT
public:
    explicit Coin(QWidget *parent = nullptr);
    Coin(QString path);
    int getPox_y() const;
    void setPox_y(int value);

    int getPos_x() const;
    void setPos_x(int value);

    bool getFlag() const;
    void setFlag(bool value);

    void changeFlag();
    void mousePressEvent(QMouseEvent *e);
signals:

public:
    QTimer *timer1;
    QTimer *timer2;
    int min = 1;
    int max = 8;
    bool isAnimation = false;
    bool isWin = false;
private:
    int pos_x;
    int pox_y;

    //true为金币，false为银币
    bool flag;

};


#endif // COIN_H
