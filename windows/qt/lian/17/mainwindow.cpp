#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCursor>
#include <QMouseEvent>
#include <QPoint>
#include <QApplication>
#include <QPixmap>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 将鼠标的样式保存在变量中
    QCursor cursor(Qt::OpenHandCursor);
    // 将变量中的鼠标样式设置到窗口中
    this->setCursor(cursor);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        QCursor leftCursor;
        leftCursor.setShape(Qt::ClosedHandCursor);
        // 配合 mouseReleaseEvent（） 短暂设置鼠标的样式 并不会覆盖之前设置的样式
        QApplication::setOverrideCursor(leftCursor);
        // 记录当前鼠标相当于主窗口位置的偏移量 (当前鼠标的位置 - 窗口左上角的位置)
        offset = event->globalPos() - pos();
    }else if(event->button() == Qt::RightButton){
        QCursor rightCursor(QPixmap(":/OIP1.jpg"));
        QApplication::setOverrideCursor(rightCursor);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
     // 恢复之前设置鼠标的样式
     QApplication::restoreOverrideCursor();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        // 如果当前窗口的状态是全屏的 那么就设置 为不是全屏的状态
        if(windowState() == Qt::WindowFullScreen){
            this->setWindowState(Qt::WindowNoState);
        }
    }
    else if(event->button() == Qt::RightButton){
        // 如果当前窗口的状态不是全屏的 那么就设置 为全屏的状态
        if(windowState() == Qt::WindowNoState){
            this->setWindowState(Qt::WindowFullScreen);
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        QPoint windows = event->globalPos() - offset;
        this->move(windows);
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    // 滚轮向上滚动，那么就将textEdit里面的内容放大
    if(event->delta() > 0){
        this->ui->textEdit->zoomIn();
    }else{
        // 滚轮向下滚动，那么就将textEdit里面的内容缩小
        this->ui->textEdit->zoomOut();
    }
}

