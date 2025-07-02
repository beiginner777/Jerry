#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog> // 对话框的头文件
#include <QDebug> // 日志输出的头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 因为设置在栈区了所以父窗口关闭才会关闭
    QDialog* _dialog = new QDialog(this);
    // 设置为模态对话框
    //_dialog->setModal(true);

    // 设置为模态对话框 但是是阻塞展示（不需要在使用show了）
    // 程序会停止在这个地方 需要关闭窗口 程序才能继续
    _dialog->exec();

    // 设置对话框的属性
    // _dialog->setWindowFlag();

    // 展示对话框
    //_dialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

