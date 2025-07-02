#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWizard> // 向导对话框的头文件
#include <QLabel>
#include <QVBoxLayout> // 垂直布局
#include <QRadioButton> // 单个按钮
#include <QButtonGroup> // 按钮组
#include <QPushButton>
#include <QDebug>
// #define QRadioButton QPushButton

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
    QWizard* _wizard = new QWizard(this);

    _wizard->resize(600,500);

    // 向导对话框的标题
    _wizard->setWindowTitle("全城热恋");

    // 创建向导页
    auto page1 = new QWizardPage(this);
    page1->setTitle("婚恋介绍引导程序");

    // 创建一个布局
    QLabel* _label1 = new QLabel(this);
    _label1->setText("该程序为您介绍对象");
    QVBoxLayout* _layout1 = new QVBoxLayout(this);
    _layout1->addWidget(_label1);

    // 将布局添加到向导页上
    page1->setLayout(_layout1);

    // 创建一个按钮组
    QButtonGroup* _group = new QButtonGroup(this);

    // 创建按钮
    QRadioButton* _btn1 = new QRadioButton(this);
    _btn1->setText("白富美");
    _group->addButton(_btn1);
    QRadioButton* _btn2 = new QRadioButton(this);
    _btn2->setText("萝莉");
    _group->addButton(_btn2);
    QRadioButton* _btn3 = new QRadioButton(this);
    _btn3->setText("御姐");
    _group->addButton(_btn3);
    QRadioButton* _btn4 = new QRadioButton(this);
    _btn4->setText("小家碧玉");
    _group->addButton(_btn4);
    QRadioButton* _btn5 = new QRadioButton(this);
    _btn5->setText("女强人");
    _group->addButton(_btn5);
    QRadioButton* _btn6 = new QRadioButton(this);
    _btn6->setText("全都要");
    _group->addButton(_btn6);
    // 将所有按钮添加到布局中
    QVBoxLayout* _layout2 = new QVBoxLayout(this);
    for(int i = 0;i < _group->buttons().size(); ++i)
    {
        _layout2->addWidget(_group->buttons()[i]);
    }

    // 将布局设置为向导页上
    QWizardPage* page2 = new QWizardPage(this);
    page2->setTitle("请选择您的心动对象");
    page2->setLayout(_layout2);

    QVBoxLayout* _layout3 = new QVBoxLayout(this);
    QLabel* label3 = new QLabel(this);
    label3->setText("感谢您的参与");
    _layout3->addWidget(label3);

    QWizardPage* page3 = new QWizardPage(this);
    page3->setTitle("您的缘分即将到来");
    page3->setLayout(_layout3);


    _wizard->setPage(0,page1);
    _wizard->setPage(1,page2);
    _wizard->setPage(2,page3);

    if(_wizard->exec() != QWizard::Accepted)
    {
        qDebug() << "close window " << endl;
    }
}
