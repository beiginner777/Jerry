#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer> // 定时器
#include <QProgressDialog> // 进度对话框的头文件
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    _progressDialog = new QProgressDialog(tr("正在复制"),tr("取消复制"),0,5000,this);
    _progressDialog->setWindowTitle(tr("复制对话框"));
    _progressDialog->setWindowModality(Qt::ApplicationModal); // 设置对话框的模态属性
    _timer = new QTimer(this);
    // 当定时器发出超时信号之后，触发槽函数
    connect(_timer,&QTimer::timeout,this,&MainWindow::responsetimer);
    // 点击取消复制 或者 直接关闭窗口 之后 会发出canceled信号 并且去触发槽函数
    connect(_progressDialog,&QProgressDialog::canceled,this,&cancleResponse);
    _timer->start(1); // 每 1 毫秒触发一次 超时信号
}

void MainWindow::responsetimer()
{
    _count++;
    if(_count > 5000){
        qDebug() << tr("复制完成") << endl;
        _timer->stop();
        delete _timer;
        _timer = nullptr;
        delete _progressDialog;
        _progressDialog = nullptr;
        _count = 0;
        return;
    }
    _progressDialog->setValue(_count);
}


void MainWindow::cancleResponse()
{
    qDebug() << tr("取消复制") << endl;
    _timer->stop();
    delete _timer;
    _timer = nullptr;
    delete _progressDialog;
    _progressDialog = nullptr;
    _count = 0;
    return;
}
