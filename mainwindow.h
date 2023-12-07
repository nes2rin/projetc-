#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include "arduino.h"
#include "connect.h"
//vente

#include <vente.h>
#include <QDate>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QHBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <vector>
#include <QStringList>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "sms.h"
  /// materiel
#include "materiel.h"
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QDate>
#include <QTextStream>
#include <QTextDocument>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QHBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include "qrcode.h"

//PLante

#include "plante.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QBuffer>
#include <QDebug>
#include<QSqlError>

//plante
#include <QSqlTableModel>
#include "plante.h"
#include "chart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void stat();
     void statMateriel();
     void sendMail(QString ref,QString nom);
     void mailsent(QString status);
     void refreshTableView();

private slots:
    void on_ajouter_clicked();


    void on_modifier_3_clicked();


    void on_tableemploye_2_clicked(const QModelIndex &index);

    void on_supprimer_3_clicked();
    employe getEmployeeData(int employeeId);




    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_triId_9_clicked();

    void on_pushButton_13_clicked();

    void on_bu_clicked();
   ////vente

    void on_pushButton_ajout_clicked();

    void on_pb_supp_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_nom_4_selectionChanged();


     /// materiel



    void on_ajoutMaterielBtn_3_clicked();

    void on_afficherMaterielPageBtn_3_clicked();

    void on_afficherMaterielPageBtn_4_clicked();

    //void on_materielModifBtn_3_clicked();

    void on_ajoutMaterielBtn_4_clicked();

    void on_ajoutMaterielPageBtn_2_clicked();

    void on_materielTableView_2_clicked(const QModelIndex &index);

    void on_materielSuppBtn_2_clicked();

    void on_employesRechBar_2_textChanged(const QString &arg1);

    void on_triEmployesComboBox_2_currentIndexChanged(const QString &arg1);

    void on_materielModifBtn_4_clicked();

    void on_sendChatBtn_2_clicked();


    void on_push_ges_emp_clicked();

    ///plante
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_updateButton_clicked();
    void on_displayButton_clicked();
    void on_searchButton_clicked();
    void on_generatePDFButton_clicked();
    void on_pushButton_3_clicked();

    void on_push_ges_vente_clicked();

    void on_push_ges_mat_clicked();

    void on_push_back_2_clicked();

    void on_materielModifBtn_3_clicked();

    void on_calender_clicked();

    void on_push_ges_plante_clicked();

private:
    Ui::MainWindow *ui;
    int selected;
     QStringList files;
     employe e;
     Arduino A;
     QByteArray data;
     //vente

     vente v;
     QMediaPlayer *player;
     QVideoWidget *videoWidget;

      /// materiel
     materiel m;
     ///plante
    QSqlTableModel *modelp;
    QSqlDatabase db;
     QSqlQueryModel *modelpp;
     Chart *pieChart;
         Connect *dbConnection;

};
#endif // MAINWINDOW_H
