#include "mainwindow.h"
#include "ui_mainwindow.h"
#define OFFSET 20
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ******************************************** 设置了 按钮才能移动
    this->setFocusPolicy(Qt::StrongFocus);

    timer_ = new QTimer(this);

    connect(timer_,&QTimer::timeout,this,&MainWindow::timeOutSlot);

    // 启动并且设置每隔一秒触发一次超时信号
    timer_->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;

    if(timer_){
        delete timer_;
        timer_ = nullptr;
    }
}

// 重写键盘输入事件
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //返回按下的所有修饰键: ctrl shift alt等待
    if(event->modifiers() == Qt::CTRL)
    {
    // CTRL + M 扩大窗口
        if(event->key() == Qt::Key_M && windowState() != Qt::WindowFullScreen){
            this->setWindowState(Qt::WindowFullScreen);
            return;
        }
        return;
    }

    // ESC键 缩小窗口
    if(event->key() == Qt::Key_Escape){
        if(windowState() == Qt::WindowFullScreen){
            this->setWindowState(Qt::WindowNoState);
            return;
        }
        return;
    }

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    // 上键
    if(event->key() == Qt::Key_Up){
        // 如果是一直按着 那么就一直移动
        if(event->isAutoRepeat()){
            auto t = ui->pushButton->pos();
            t.setY(t.y() - OFFSET);
            ui->pushButton->move(t);
        }else{
            up = true;
        }
    }


    // 下键
    if(event->key() == Qt::Key_Down){
        // 如果是一直按着 那么就一直移动
        if(event->isAutoRepeat()){
            auto t = ui->pushButton->pos();
            t.setY(t.y() + OFFSET);
            ui->pushButton->move(t);
        }else{
            down = true;
        }
    }


    // 左键
    if(event->key() == Qt::Key_Left){
        // 如果是一直按着 那么就一直移动
        if(event->isAutoRepeat()){
            auto t = ui->pushButton->pos();
            t.setX(t.x() - OFFSET);
            ui->pushButton->move(t);
        }else{
            left = true;
        }
    }



    // 右键
    if(event->key() == Qt::Key_Right){
        // 如果是一直按着 那么就一直移动
        if(event->isAutoRepeat()){
            auto t = ui->pushButton->pos();
            t.setX(t.x() + OFFSET);
            ui->pushButton->move(t);
        }else{
            right = true;
        }
    }

    auto t = ui->pushButton->pos();

    if(up){
        t.setY(t.y() - OFFSET);
    }else if(down){
        t.setY(t.y() + OFFSET);
    }else if(left){
        t.setX(t.x() - OFFSET);
    }else if(right){
        t.setX(t.x() + OFFSET);
    }

    ui->pushButton->move(t);
}

void MainWindow::timeOutSlot()
{
    QTime cur = QTime::currentTime();
    QString time = cur.toString();
    if(cur.second() % 2 == 0){
        time[5] = ' ';
    }
    // qDebug() << "current time is " << time;
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->display(time);
}


