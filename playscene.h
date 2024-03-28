#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"coin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);
signals:
    void PressBackButton();

public:
    int gameArray[4][4];
    Coin* coinArray[4][4];
protected:
    void paintEvent(QPaintEvent *event);

};

#endif // PLAYSCENE_H
