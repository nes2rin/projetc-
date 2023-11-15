#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"

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
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_tableemploye_clicked(const QModelIndex &index);

    void on_modifier_clicked();
    employe getEmployeeData(int employeeId);




    void on_pushButton_clicked();


    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();



    void on_triId_8_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    int selected;
     QStringList files;
     employe e;

};
#endif // MAINWINDOW_H
