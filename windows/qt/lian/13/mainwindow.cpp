#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextDocument>
#include <QTextFrame>
#include <QTextFrameFormat>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QTextEdit 对象内部就包含了一个 QTextDocument 对象
    // QTextDocument 是用来存储和管理实际文本数据的核心类。
    QTextDocument* doc = ui->textEdit->document();
    // 获取文本类的框架
    QTextFrame* textFrame = doc->rootFrame();
    // 新建一个文本类框架的样式
    QTextFrameFormat textFrameFormat;
    // 设置 ”当前行“的文本框的格式
    textFrameFormat.setBorderBrush(Qt::red);
    // 设置 ”当前行“的文本框的边界像素
    textFrameFormat.setBorder(3);
    // 设置文本框的背景颜色 为 浅灰色
    textFrameFormat.setBackground(Qt::white);
    // 将这个新的文本框样式 设置到 窗口当中
    textFrame->setFrameFormat(textFrameFormat);


}

MainWindow::~MainWindow()
{
    delete ui;
}

