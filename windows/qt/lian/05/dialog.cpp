#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include "childdialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    qDebug() << "在主界面中点击了退出按钮" << endl;
    accept(); // 发出应该是由 主窗口 接收，然后直接关闭主窗口
}


void Dialog::on_pushButton_clicked()
{
    // 将当前的主界面隐藏
    close();
    // 进入一个子界面
    childDialog _childdialog;
    if(_childdialog.exec() == QDialog::Accepted){
        this->show();
    }else{
        qDebug() << "在主界面中 直接将窗口 关闭了" << endl;
        return;
    }
}
