#include "childdialog.h"
#include "ui_childdialog.h"
#include <QDebug>

childDialog::childDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::childDialog)
{
    ui->setupUi(this);
}

childDialog::~childDialog()
{
    delete ui;
}

void childDialog::on_enterMainBtn_clicked()
{
    qDebug() << "点击了进入主界面的按钮" << endl;
    accept(); // 这个槽函数 是发出了一个 Accepted 信号 作为子界面的 exec 的接受值 并且将子界面关闭
}
