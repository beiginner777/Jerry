#include "dialog.h"
#include "childdialog.h"
#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    childDialog _childdialg;
    // 捕捉exec()函数的返回值 如果是rejected 直接关闭窗口
    // 那么就直接 退出程序 不进入a.exec(),才不会造成程序异常
    if(_childdialg.exec() == QDialog::Rejected){
        return 0;
    }else{
        // 展示主界面
        w.show();
        a.exec();
    }
    //w.show();
    //return a.exec();
}
