#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp> // 正则表达式
#include <QRegExpValidator> // 文本校验器
#include <QValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp reg1("[1-9]{1}[1-9]{4,10}");
    QValidator* valid1 = new QRegExpValidator(reg1,ui->numedit);
    ui->numedit->setValidator(valid1);

    QRegExp reg2("[1-9a-zA-Z!?.,'*]{8,16}");
    QValidator* valid2 = new QRegExpValidator(reg2,ui->pwdedit);
    ui->pwdedit->setValidator(valid2);

    // 设置密码的显示形式
    ui->pwdedit->setEchoMode(QLineEdit::Password);

    QRegExp reg3("[1-9a-zA-Z]+@[1-9a-zA-Z]+.[a-zA-Z]{1-8}");
    QValidator* valid3 = new QRegExpValidator(reg3,ui->emailedit);
    ui->emailedit->setValidator(valid3);

    QRegExp reg4("[1-9]{1}[1-9]{10}");
    QValidator* valid4 = new QRegExpValidator(reg4,ui->telphoneedit);
    ui->telphoneedit->setValidator(valid4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

