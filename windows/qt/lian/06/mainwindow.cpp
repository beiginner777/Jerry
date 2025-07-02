#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QDir>
#include <QColorDialog> // 颜色对话框的头文件
#include <QFileDialog> // 文件对话框
#include <QInputDialog> // 输入对话框
#include <QStringList> // 容器
#include <QMessageBox> // 消息对话框

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
    QColorDialog* _colorDialog = new QColorDialog(this);
    if(_colorDialog->exec() == QColorDialog::Accepted){
        QColor color = _colorDialog->currentColor();// 获取在对话框中选定的颜色
        qDebug() << color << endl;
    }else{
        qDebug() << "click exit btn" << endl;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString title = tr("文件对话框"); // 设置对话框的标题
    QString path = QDir::currentPath(); // 获取当前文件所在的文件夹
    QString capture = tr("文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)");// 筛选文件
    // new 之后会自动显示
    QFileDialog* _fileDialog = new QFileDialog(this,title,path,capture);
    QString filename = _fileDialog->getOpenFileName();
    qDebug() << "filename is " << filename << endl;
}

// 浮点数 同理
void MainWindow::on_pushButton_3_clicked()
{
    bool ok = false;
    // 创建整形对话框
    auto int_num = QInputDialog::getInt(this,tr("整形输入对话框"),tr("请输入整形数字"),5,0,10,1,&ok);
    if(ok) qDebug() << int_num << endl;
    else qDebug() << "illegal" << endl;
}

void MainWindow::on_pushButton_4_clicked()
{
    QStringList item;
    item << tr("first") << tr("second") << tr("third"); // 向容器中写入数据
    auto sel = QInputDialog::getItem(this,tr("条目对话框"),tr("请选择"),item,1,false);// 1是默认选择哪个
    qDebug() << sel << endl;
}



void MainWindow::on_pushButton_5_clicked()
{
    auto ret = QMessageBox::question(this,tr("提示对话框"),tr("你是人吗"));
    if(ret == QMessageBox::Yes){
        qDebug() << "我是人" << endl;
    }else {
        qDebug() << "我不是人" << endl;
    }
}
