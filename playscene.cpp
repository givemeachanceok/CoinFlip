#include<QMenuBar>
#include<QMenu>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QFont>
#include<QDebug>
#include<QPropertyAnimation>
#include"dataconfig.h"

#include"mypushbutton.h"
#include "playscene.h"
PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{
}

PlayScene::PlayScene(int index)
{
    //设置窗口标题
    this->setFixedSize(450,600);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle(QString::fromStdWString(L"关卡")+index);
    //设置菜单栏
    QMenuBar *menueBar = new QMenuBar(this);
    this->setMenuBar(menueBar);

    QMenu *startMenu = new QMenu(this);
    startMenu->setTitle(QString::fromStdWString(L"开始"));
    menueBar->addMenu(startMenu);

    QAction *quitAction = new QAction(this);
    quitAction->setText(QString::fromStdWString(L"退出"));
    startMenu->addAction(quitAction);

    //菜单退出动作信号槽
    connect(quitAction,&QAction::triggered,[=]()
    {
        this->close();
    });

    //设置返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width()-10,this->height()- backBtn->height()-10);

    //设置返回按钮信号槽
    connect(backBtn,&QPushButton::clicked,[=]()
    {
        QTimer::singleShot(500,this,[=]()
        {
            this->hide();
            emit this->PressBackButton();
        });
    });


    //设置左下角标签
    QLabel *label = new QLabel(this);

    //设置字体
    QFont font;
    font.setFamily(QString::fromStdWString(L"Ink Free"));
    font.setPointSize(20);

    //完善标签
    label->setFont(font);
    label->setText("Level:" + QString::number(index));
    label->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    label->move(10,this->height() - label->height()-10);

    dataConfig config;

    //胜利标签
    QLabel *labelWin = new QLabel(this);
    QPixmap pixWin;
    pixWin.load(":/res/LevelCompletedDialogBg.png");

    labelWin->setFixedSize(pixWin.width(),pixWin.height());
    labelWin->setPixmap(pixWin);
    labelWin->setGeometry(0,0,pixWin.width(),pixWin.height());
    labelWin->move(this->width()*0.5-labelWin->width()*0.5,-labelWin->height());
    //labelWin->move(this->width()*0.5-labelWin->width()*0.5,this->height()*0.4-labelWin->height()*0.5);

    for(int i = 0;i<4;i++)
    {
        for(int j = 0; j < 4; j++)
        {
            gameArray[i][j] = config.mData[index][i][j];
            //设置硬币背景
            QLabel *label1 = new QLabel(this);
            label1->setGeometry(0,0,50,50);
            label1->setPixmap(QPixmap(":/res/BoardNode.png"));
            label1->move(125 + i*50,200+j*50);
            label1->setAttribute(Qt::WA_TransparentForMouseEvents,true);

            //设置硬币
            Coin *coin;
            if(config.mData[index][i][j]==1)
            {
                coin = new Coin(":/res/Coin0001.png");
                coin->setFlag(true);
            }
            else
            {
                coin = new Coin(":/res/Coin0008.png");
                coin->setFlag(false);
            }
            //设置硬币坐标
            coin->setPos_x(i);
            coin->setPox_y(j);
            coin->setParent(this);
            coin->move(125 + i*50,200+j*50);


            //硬币存入数组
            this->coinArray[i][j] = coin;

            //监听硬币按钮
            connect(coin,&QPushButton::clicked,[=]()
            {
                this->coinArray[i][j]->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;

                //延时翻转其他硬币
                QTimer::singleShot(300,this,[=]()
                {
                    if(i-1>=0)
                    {
                        this->coinArray[i-1][j]->changeFlag();
                        gameArray[i - 1][j] = gameArray[i - 1][j] == 0 ? 1 : 0;
                    }
                    if(i+1<=3)
                    {
                        this->coinArray[i+1][j]->changeFlag();
                        gameArray[i + 1][j] = gameArray[i + 1][j] == 0 ? 1 : 0;
                    }
                    if(j-1>=0)
                    {
                        this->coinArray[i][j-1]->changeFlag();
                        gameArray[i][j - 1] = gameArray[i][j - 1] == 0 ? 1 : 0;
                    }
                    if(j+1<=3)
                    {
                        this->coinArray[i][j+1]->changeFlag();
                        gameArray[i][j + 1] = gameArray[i][j + 1] == 0 ? 1 : 0;
                    }
                    //判断是否胜利
                    this->coinArray[i][j]->isWin = true;
                    for(int x = 0;x<4;x++)
                    {
                        for(int y=0;y<4;y++)
                        {
                            if(!coinArray[x][y]->getFlag())
                            {
                                this->coinArray[i][j]->isWin = false;
                            }
                        }
                    }
                    if(this->coinArray[i][j]->isWin == true)
                    {
                        //胜利图标移动
                        qDebug()<<QString::fromStdWString(L"胜利");
                        QPropertyAnimation * animation1 =  new QPropertyAnimation(labelWin,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(labelWin->x(),labelWin->y(),labelWin->width(),labelWin->height()));
                        animation1->setEndValue(QRect(labelWin->x(),labelWin->y()+205,labelWin->width(),labelWin->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();
                        for(int x = 0;x<4;x++)
                        {
                            for(int y=0;y<4;y++)
                            {
                                coinArray[x][y]->isWin = true;
                            }
                        }
                    }
                    else
                    {
                        for(int x = 0;x<4;x++)
                        {
                            for(int y=0;y<4;y++)
                            {
                                coinArray[x][y]->isWin = false;
                            }
                        }
                    }
                });
            });
        }
    }



}
void PlayScene::paintEvent(QPaintEvent *event)
{
    QPixmap pix(":/res/PlayLevelSceneBg.png");

    QPainter *painter = new QPainter(this);

    painter->drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter->drawPixmap( 10,30,pix.width(),pix.height(),pix);
    delete painter;
}
