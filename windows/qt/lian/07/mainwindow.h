#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void responsetimer();
    void cancleResponse();
private:
    Ui::MainWindow *ui;
    int _count;
    QProgressDialog* _progressDialog;
    QTimer* _timer;
};
#endif // MAINWINDOW_H
