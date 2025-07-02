#ifndef CHILDDIALOG_H
#define CHILDDIALOG_H

#include <QDialog>

namespace Ui {
class childDialog;
}

class childDialog : public QDialog
{
    Q_OBJECT

public:
    explicit childDialog(QWidget *parent = nullptr);
    ~childDialog();

private slots:
    void on_enterMainBtn_clicked();

private:
    Ui::childDialog *ui;
};

#endif // CHILDDIALOG_H
