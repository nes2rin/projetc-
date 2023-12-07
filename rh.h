#ifndef RH_H
#define RH_H
#include <QDialog>
#include "employe.h"
#include "login.h"
#include "employemodel.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
namespace Ui {
class rh;
}

class rh : public QDialog
{
    Q_OBJECT

public:
    employe getEmployeeData(int employeeId);
    explicit rh(QWidget *parent = nullptr);
    ~rh();
private slots:

    void on_tableemploye1_clicked(const QModelIndex &index);

    void on_modifier1_clicked();

private:
    Ui::rh *ui;
    int selected;

};

#endif // RH_H
