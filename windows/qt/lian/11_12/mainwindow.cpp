#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiArea>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 在菜单栏上添加一个 编辑菜单
    QMenu* editmenu = ui->menubar->addMenu(tr("编辑(&E)"));
    // 在 编辑菜单 上面 添加一个动作
    QAction* openFile = editmenu->addAction(tr("打开文件(&O)"));
    connect(openFile,&QAction::triggered,this,&MainWindow::sendOpenFileMsg);

    editmenu->addSeparator();

    // 将动作添加到同一个动作组当中
    QActionGroup* actionGroup = new QActionGroup(editmenu);

    // 将三个动作加入动作组中
    QAction* action_L = actionGroup->addAction(tr("左对齐(&L)"));
    action_L->setCheckable(true);
    QAction* action_R = actionGroup->addAction(tr("右对齐(&R)"));
    action_R->setCheckable(true);
    QAction* action_C = actionGroup->addAction(tr("居中(&C)"));
    action_C->setCheckable(true);

    // 将三个动作加入菜单栏当中
    editmenu->addAction(action_L);
    editmenu->addAction(action_R);
    editmenu->addAction(action_C);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionshowDock_triggered()
{
    ui->dockWidget->show();
}

void MainWindow::on_actionNew_N_triggered()
{
    QTextEdit* textEdit_ = new QTextEdit(this);
    auto childWindow = ui->mdiArea->addSubWindow(textEdit_);
    childWindow->setWindowTitle(tr("新建文本文件"));
    childWindow->show();
}

// 在控制台输出一句 打开文件 的消息
void MainWindow::sendOpenFileMsg()
{
    qDebug() << "open file" << endl;
}
