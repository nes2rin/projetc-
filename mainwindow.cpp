#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "employemodel.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>



#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>



#include <QDialog>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>

#include "smtp.h"

#include <QPdfWriter>
#include <QPainter>

#include <QtCharts>
#include <QChartView>
#include <QBarSet>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    employe E;
    employemodel *model = new employemodel;
    model->refresh(); // load data from the database

    ui->tableemploye->setModel(model);
    ui->tableemploye->resizeColumnsToContents();
    ui->tableemploye->verticalHeader()->setDefaultSectionSize(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    QString nom  = ui->nom->text();
    QString prenom=ui->prenom->text();
    QString email=ui->email->text();
    QString mdp=ui->mdp->text();
    QString adresse=ui->adresse->text();
    QString poste=ui->poste->currentText();
    int num= ui->num->text().toInt();
    double salaire= ui->salaire->text().toDouble();
qDebug() << num;
qDebug() << salaire;



    QSqlQuery query;
  employe e(nom,prenom,email,mdp,adresse,poste,salaire,num);
  bool test=e.ajouter();
    if (test)
    {
        employemodel *model = new employemodel;
        model->refresh(); // load data from the database
        ui->tableemploye->setModel(model);
        ui->tableemploye->resizeColumnsToContents();
        ui->tableemploye->verticalHeader()->setDefaultSectionSize(50);

        ui->nom->setText("");
        ui->prenom->setText("");
        ui->email->setText("");
        ui->mdp->setText("");
        ui->adresse->setText("");
        ui->poste->setCurrentIndex(-1);
        ui->salaire->setText("");
        ui->num->setText("");

       QMessageBox::information(nullptr, QObject::tr("CORRECT !"),
                   QObject::tr("Create successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else

       QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                   QObject::tr("create  failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_supprimer_clicked()
{
    employe s(selected);
    bool test =s.supprimer();
    if (test)
    {

      //s.afficher();
        employemodel *model = new employemodel;
        model->refresh(); // load data from the database
        ui->tableemploye->setModel(model);
        ui->tableemploye->resizeColumnsToContents();
        ui->tableemploye->verticalHeader()->setDefaultSectionSize(50);

        ui->nom->setText("");
        ui->prenom->setText("");
        ui->email->setText("");
        ui->mdp->setText("");
        ui->adresse->setText("");
        ui->poste->setCurrentIndex(-1);
        ui->salaire->setText("");
        ui->num->setText("");

       QMessageBox::information(nullptr, QObject::tr("CORRECT !"),
                   QObject::tr("delete sucessful \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else

       QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                   QObject::tr("delete failed \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_tableemploye_clicked(const QModelIndex &index)
{
    selected = ui->tableemploye->model()->data(index).toInt();
    employe e = getEmployeeData(selected);

    ui->nom->setText(e.getNom());
    ui->prenom->setText(e.getPrenom());
    ui->email->setText(e.getEmail());
    ui->mdp->setText(e.getMdp());
    ui->adresse->setText(e.getAdresse());
    if(e.getPoste() == "Admin")
    ui->poste->setCurrentIndex(0);
    else
    ui->poste->setCurrentIndex(1);
    ui->salaire->setText(QString::number(e.getSalaire()));
    ui->num->setText(QString::number(e.getNum()));

}
employe MainWindow::getEmployeeData(int employeeId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE id = :id");
    query.bindValue(":id", employeeId);
    query.exec();

    employe employee;

    if (query.next()) {
        employee.setNom(query.value(1).toString());
        employee.setPrenom(query.value(2).toString());
        employee.setEmail(query.value(3).toString());
        employee.setMdp(query.value(4).toString());
        employee.setPoste(query.value(5).toString());
        employee.setAdresse(query.value(6).toString());
        employee.setSalaire(query.value(7).toDouble());
        employee.setNum(query.value(8).toInt());
    }

    return employee;
}

void MainWindow::on_modifier_clicked()
{
    QString nom  = ui->nom->text();
    QString prenom=ui->prenom->text();
    QString email=ui->email->text();
    QString mdp=ui->mdp->text();
    QString adresse=ui->adresse->text();
    QString poste=ui->poste->currentText();
    int num= (int) ui->num->text().toInt();
    float salaire= (float) ui->salaire->text().toFloat();



    QSqlQuery query;
  employe e(selected,nom,prenom,email,mdp,adresse,poste,salaire,num);
  bool test=e.modifier();
    if (test)
    {
       QMessageBox::information(nullptr, QObject::tr("CORRECT !"),
                   QObject::tr("Create successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
       employemodel *model = new employemodel;
       model->refresh(); // load data from the database
       ui->tableemploye->setModel(model);
       ui->tableemploye->resizeColumnsToContents();
       ui->tableemploye->verticalHeader()->setDefaultSectionSize(50);
       ui->nom->setText("");
       ui->prenom->setText("");
       ui->email->setText("");
       ui->mdp->setText("");
       ui->adresse->setText("");
       ui->poste->setCurrentIndex(-1);
       ui->salaire->setText("");
       ui->num->setText("");

    }
    else

       QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                   QObject::tr("create  failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}



////mailing
void MainWindow::on_pushButton_clicked()
{
    smtp* ssmtp = new smtp("hamed.nisrine@esprit.tn", "ekdy fscy civv wwcp", "smtp.gmail.com", 465);

                  connect(ssmtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

                  QString email=ui->rcpt_2->text();

                  QString b=ui->subject_2->text();

                  QString ob=ui->msg_2->toPlainText();

                   if(email!="" && b!="" && ob!="" )
                      {


                                        ssmtp->sendMail("hamed.nisrine@esprit.tn", email , b,ob);
                                        QMessageBox::information(nullptr, QObject::tr("EMAIL"),
                                        QObject::tr("Email sent successfully.\n"
                                        "click Cancel to exit"),QMessageBox::Cancel);

                      }
                   else
                      {
                              QMessageBox::critical(nullptr, QObject::tr("EMAIL"),
                              QObject::tr("something is empty.\n"
                              "click Cancel to exit."),QMessageBox::Cancel);

                      }
}


void MainWindow::on_pushButton_5_clicked()
{
    employe e;
     ui->tableemploye->setModel(e.recherche_employe(ui->recherche->text()));
}

void MainWindow::on_pushButton_6_clicked()
{
    QPdfWriter pdf("C:/Users/hamed/Desktop/projetc++/Liste_Employe.pdf");

       QPainter painter(&pdf);
       int i = 4100;
       const QImage image("C:/Users/ASUS/Desktop/logo.png");
                   const QPoint imageCoordinates(155,0);
                   int width1 = 1600;
                   int height1 = 1600;
                   QImage img=image.scaled(width1,height1);
                   painter.drawImage(imageCoordinates, img );


              QColor dateColor(0x4a5bcf);
              painter.setPen(dateColor);

              painter.setFont(QFont("Montserrat SemiBold", 11));
              QDate cd = QDate::currentDate();
              painter.drawText(8400,250,cd.toString("Tunis"));
              painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

              QColor titleColor(0x341763);
              painter.setPen(titleColor);
              painter.setFont(QFont("Montserrat SemiBold", 25));

              painter.drawText(3000,2700,"Liste des Employe");

              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 15));
              painter.drawRect(100,3300,9400,500);

              painter.setFont(QFont("Montserrat SemiBold", 10));

              painter.drawText(500,3600,"Nom");
              painter.drawText(2000,3600,"Prenom");
              painter.drawText(3300,3600,"Email");
              painter.drawText(4500,3600,"Mdp");
              painter.drawText(7500,3600,"Adresse");
              painter.drawText(9500,3600,"poste");
              painter.drawText(11500,3600,"salaire");
              painter.drawText(13500,3600,"Numero");
              painter.setFont(QFont("Montserrat", 10));
              painter.drawRect(100,3300,9400,9000);

              QSqlQuery query;
              query.prepare("select * from employe");
              query.exec();
              int y=4300;
              while (query.next())
              {
                  painter.drawLine(100,y,9490,y);
                  y+=500;
                  painter.drawText(500,i,query.value(1).toString());
                  painter.drawText(2000,i,query.value(2).toString());
                  painter.drawText(3300,i,query.value(3).toString());
                  painter.drawText(4500,i,query.value(4).toString());
                  painter.drawText(7500,i,query.value(5).toString());

                 i = i + 500;
              }
              QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}




void MainWindow::on_triId_8_clicked()
{
  ui->tableemploye->setModel(e.triID());
}

void MainWindow::on_pushButton_4_clicked()
{

    employe e;
        QBarSet *set0 = new QBarSet("");

        *set0  << e.statistiquesemploye("Admin")<< e.statistiquesemploye("Responsable RH");


        QColor color(0x6568F3);
        set0->setColor(color);

        QBarSeries *series = new QBarSeries();
        series->append(set0);




        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setBackgroundVisible(false);

        QColor bgColor(0xF4DCD3);
                       chart->setBackgroundBrush(QBrush(QColor(bgColor)));

                       chart->setBackgroundVisible(true);

        QStringList categories;
        categories  << "Admin"<< "RH";
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        QChartView *chartView = new QChartView(chart);

        chartView->setMinimumWidth(500);
        chartView->setMinimumHeight(300);
        chartView->setParent(ui->statE);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chartView->show();

}
