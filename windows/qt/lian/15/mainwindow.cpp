#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <QGraphicsSceneDragDropEvent>
#include <QString>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 将主窗口设置为可接受拖拽事件
    this->setAcceptDrops(true);
    // 将textedit设置为不可接收事件，因为textedit有一个默认的处理事件
    ui->textEdit->setAcceptDrops(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 拖拽动作进入主窗口的时候 触发的事件
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    // 判断发生事件中的数据 是否是 主机上url路径下的文件
    if(event->mimeData()->hasUrls()){
        // 在控制台打印文件路径
        qDebug() << "url pass is " << event->mimeData()->urls()[0] << endl;
        // 表示接收这个QDragEnterEvent事件 那么在 拖拽事件离开主窗口的时候 就对这个事件可以进行处理
        event->acceptProposedAction();
    }else{
        // 清除该标志表示事件接收者不想处理此事件。
        // 不被接收的事件可能会被传递给父级控件
        // event->setAccepted(false);
        event->ignore();
    }
}
// 拖拽动作离开主窗口的时候 触发的事件
void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData* data = event->mimeData();
    if(data->hasUrls()){
        // 因为可能包含多个url路径（选中多个文件或者链接同时进行拖拽事件）因此这个函数的返回值设置为 链表 类型
        QUrl url = data->urls()[0];
        // 将url路径转换为QString
        QString filename = url.toLocalFile();
        // 判断拖拽的数据对象是一个目录 还是 文件
        QFileInfo info(filename);
        if(info.isDir()){
            qDebug() << filename << " is a directory !" << endl;
            return;
        }
        if(filename.isEmpty()){
            qDebug() << "filename is nullptr !" << endl;
            return;
        }
        QTextCodec* codec = QTextCodec::codecForName("UTF-8");
        QFile file(filename);
        // 以只读的方式打开文件
        if(!file.open(QIODevice::ReadOnly)){
             qDebug() << "open " << filename << " failed !" << endl;
             return;
        }
        QTextCodec::setCodecForLocale(codec);
        // 相当于将文件中的的内容全部放在stream对象中管理
        QTextStream stream(&file);
        ui->textEdit->setText(stream.readAll());
    }else{
        // 清除该标志表示事件接收者不想处理此事件。
        // 不被接收的事件可能会被传递给父级控件
        // event->setAccepted(false);
        event->ignore();
    }
    
}

