#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void statMateriel();
    void sendMail(QString ref,QString nom);
    void mailsent(QString status);

private slots:


    void on_ajoutMaterielPageBtn_clicked();

    void on_afficherMaterielPageBtn_clicked();

    void on_materielModifBtn_clicked();

    void on_ajoutMaterielBtn_clicked();

    void on_materielTableView_clicked(const QModelIndex &index);

    void on_ajoutMaterielBtn_2_clicked();

    void on_materielSuppBtn_clicked();

    void on_employesRechBar_textChanged(const QString &arg1);

    void on_triEmployesComboBox_currentIndexChanged(const QString &arg1);

    void on_materielModifBtn_2_clicked();

    void on_sendChatBtn_clicked();

    void on_afficherMaterielPageBtn_2_clicked();

private:
    Ui::MainWindow *ui;
    materiel m;
};
#endif // MAINWINDOW_H
