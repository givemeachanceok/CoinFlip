#include "selectwindows.h"
#include<QIcon>
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include"mypushbutton.h"
SelectWindows::SelectWindows(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(450,600);
    this->setWindowTitle(QString::fromStdWString(L"选择关卡"));
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);

    QMenu *startMenu = new QMenu(QString::fromStdWString(L"开始"));
    menuBar->addMenu(startMenu);

    QAction * quitAction = new QAction(QString::fromStdWString(L"退出"));
    startMenu->addAction(quitAction);

    MyPushButton *mptn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    mptn->setParent(this);
    mptn->move(this->width()-mptn->width()-10,this->height()- mptn->height()-10);


    connect(quitAction,&QAction::triggered,[=]()
    {
        this->close();
    });

    //按下back按钮返回发送按下信号
    connect(mptn,&QPushButton::clicked,[=]()
    {
        QTimer::singleShot(500,this,[=](){
            this->hide();
            emit this->chooseBackButton();
        });
    });

    double height = this->height()/7;
    double width = this->width()/5;
    double boundary = width/2;
    for( int i = 0; i < 5; i++ )
    {
        for( int j = 0; j < 4; j++ )
        {
            //创建关卡按钮
            MyPushButton *chooseBtn = new MyPushButton(":/res/LevelIcon.png");

            //将按钮设置到窗口上
            chooseBtn->setParent(this);

            //按钮移动到合适位置上
            chooseBtn->move(width *j+boundary,height*(i+1));

            QLabel *label = new QLabel;

            //将标签设置到窗口上
            label->setParent(this);

            //将标签移动到按钮上
            label->move(width *j+boundary,height*(i+1));

            //设置标签大小
            label->setFixedSize(chooseBtn->width(),chooseBtn->height());

            //设置文字
            label->setText(QString::number(j+1+i*4));

            //设置标签文字对齐方式
            label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

            //鼠标事件穿透
            label->setAttribute(Qt::WA_TransparentForMouseEvents,true);

            //为每个按钮设置信号槽
            connect(chooseBtn,&QPushButton::clicked,[=]()
            {
                if(ps!=NULL)
                {
                    delete this->ps;
                    this->ps = NULL;
                }
                ps = new PlayScene(j+1+i*4);
                chooseBtn->jumpUp();
                QTimer::singleShot(500,this,[=]()
                {
                    this->hide();
                    ps->show();
                });

                //监听游戏场景back信号
                connect(ps,&PlayScene::PressBackButton,[=]()
                {
                    this->show();
                    delete this->ps;
                    this->ps = NULL;
                });
            });
        }
    }

}

//重写画图事件
void SelectWindows::paintEvent(QPaintEvent *event)
{
    QString path(QString::fromStdWString(L":/res/OtherSceneBg.png"));
    QPixmap pix;
    pix.load(path);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

