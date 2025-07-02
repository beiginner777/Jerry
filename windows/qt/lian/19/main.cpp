#include "mainwindow.h"

#include <QApplication>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QDir>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPixmap>
#include <QTableView>

// 创建列表模型
int main(int argc,char* argv[])
{
    QApplication a(argc,argv);

    QStandardItemModel* model = new QStandardItemModel;

    for(int i = 0;i < 5; ++i){
        QStandardItem* item = new QStandardItem(QString("item %1").arg(i));
        // 将模型中的各项设置为不可编辑的
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        model->appendRow(item);
    }

    QListView listview;
    listview.setModel(model);
    listview.show();

    return a.exec();
}



// 创建表格模型
//int main(int argc,char* argv[])
//{
//    QApplication a(argc,argv);

//    QStandardItemModel* model = new QStandardItemModel(3,2);

//    for(int i = 0;i < 3;i++){
//        for(int j = 0;j < 2;++j){
//            QStandardItem *item = new QStandardItem(QString("R%1C%2").arg(i).arg(j));
//            model->setItem(i, j, item);
//        }
//    }

//    QTableView tableview;
//    tableview.setModel(model);
//    tableview.show();

//    return a.exec();
//}



// 创建树形模型

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    // 创建树形模型
//    QStandardItemModel* model = new QStandardItemModel;
//    // 取出模型的根节点
//    QStandardItem* parent = model->invisibleRootItem();
//    // 创建子结点
//    QStandardItem* node1 = new QStandardItem;
//    node1->setText("item1");
//    // 构造函数设置大小
//    QPixmap map1= QPixmap(50,50);
//    // 填充颜色
//    map1.fill(Qt::blue);
//    // 最后将icon设置上去
//    node1->setIcon(QPixmap(map1));

//    // 将结点添加到模型
//    parent->appendRow(node1);

//    parent = node1;

//    // 创建子结点
//    QStandardItem* node2 = new QStandardItem;
//    node2->setText("item2");
//    // 构造函数设置大小
//    QPixmap map2= QPixmap(50,50);
//    // 填充颜色
//    map2.fill(Qt::red);
//    // 最后将icon设置上去
//    node2->setIcon(QPixmap(map2));

//    // 将结点添加到模型
//    parent->appendRow(node2);


//    QTreeView treeview;
//    treeview.setModel(model);
//    treeview.show();

//    return a.exec();
//}


// 显示本地的文件和目录

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
////    MainWindow w;
////    w.show();

//    QSplitter* splitter = new QSplitter;

//    QFileSystemModel是Qt给我们提供的处理本地文件系统的文件和目录。

//    // 设置当前模型监控的目录范围
//    QFileSystemModel* model = new QFileSystemModel(splitter);
//    model->setRootPath(QDir::currentPath());

//    // 创建树形视图
//    QTreeView* treeview = new QTreeView(splitter);
//    // 绑定模型‘
//    treeview->setModel(model);
//    // 设置模型显示的目录
//    treeview->setRootIndex(model->index(QDir::currentPath()));

//    // 创建列表视图
//    QListView* listview = new QListView(splitter);
//    // 绑定模型
//    listview->setModel(model);
//    // 设置模型显示的目录
//    listview->setRootIndex(model->index(QDir::currentPath()));

//    // 显示
//    splitter->resize(800,600);
//    splitter->show();

//    return a.exec();
//}
