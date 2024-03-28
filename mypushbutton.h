#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton( QString normalPath,QString pushPath = "");
    void jumpUp();
    void jumpDown();
signals:

private:
    QString normalPath;
    QString pushPath;
protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
};

#endif // MYPUSHBUTTON_H
