#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "employe.h"
#include "mainwindow.h"
#include "rh.h"
#include <QMessageBox>
#include "employemodel.h"
namespace Ui {
class login;
}

class login : public QDialog
{

    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    int recherche(QString,QString);
    employe employee;


private slots:
    void on_log_clicked();

private:
    Ui::login *ui;
    int test;
};

#endif // LOGIN_H
