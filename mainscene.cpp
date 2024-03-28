#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<QTimer>

#include"mypushbutton.h"
#include"selectwindows.h"
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //退出按钮实现
    connect(ui->action_quit,&QAction::triggered,[=]()
    {
        this->close();
    });
    ;

    //设置窗口标题图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置窗口固定大小
    this->setFixedSize(450,600);

    //创建开始按钮
    MyPushButton *mptn = new MyPushButton(":/res/MenuSceneStartButton.png",":/res/MenuSceneStartButton.png");

    //放置按钮
    mptn->setParent(this);

    //移动按钮到指定位置
    mptn->move(this->width()*0.5 - mptn->width()/2,this->height()*0.5+mptn->height());

    SelectWindows *sw = new SelectWindows();

    //按钮按下执行动作
    connect(mptn,&QPushButton::clicked,[=]()
    {
        mptn->jumpUp();
        //mptn->jumpDown();
        QTimer::singleShot(500,this,[=](){

            this->hide();
            sw->show();
        });

    });

    connect(sw,&SelectWindows::chooseBackButton,[=]()
    {
        this->show();
    });
}

void MainScene::paintEvent(QPaintEvent *event)
{
    //设置背景
    QPixmap pixmap(":/res/PlayLevelSceneBg.png");

    //创建画家对象
    QPainter painter(this);

    //画家画画
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

MainScene::~MainScene()
{
    delete ui;
}

