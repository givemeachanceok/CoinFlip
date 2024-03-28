#ifndef SELECTWINDOWS_H
#define SELECTWINDOWS_H
#include"playscene.h"
#include <QMainWindow>

class SelectWindows : public QMainWindow
{
    Q_OBJECT
public:
    explicit SelectWindows(QWidget *parent = nullptr);
    //创建关卡界面
    PlayScene *ps = NULL;

signals:
    void chooseBackButton();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // SELECTWINDOWS_H
