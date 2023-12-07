
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "employemodel.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include "mainwindow2.h"



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
#include "smtpp.h"

#include <QPdfWriter>
#include <QPainter>

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
//vente
#include "vente.h"
#include <QMessageBox>
#include <QStandardPaths>
#include "pdf.h"
#include <QSqlRecord>
//materiel

#include "materiel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    employe E;
    employemodel *model = new employemodel;
    model->refresh(); // load data from the database

    ui->tableemploye_2->setModel(model);
    ui->tableemploye_2->resizeColumnsToContents();
    ui->tableemploye_2->verticalHeader()->setDefaultSectionSize(50);
    //vente

    ui->le_nom_2->setPlaceholderText("enter nom");
    ui->le_date->setPlaceholderText("enter date");
    ui->le_code->setPlaceholderText("enter code");
    ui->le_marche->setPlaceholderText("enter marche ");
    ui->le_prix->setPlaceholderText("enter prix");
    ui->le_poids->setPlaceholderText("enter poids");
    ui->le_quantite->setPlaceholderText("enter quantite");
    ui->tab_ventes->setModel(v.afficher());
    ui->comboBox->addItem("Par défaut");
    ui->comboBox->addItem("Nom");
    ui->comboBox->addItem("Type");
    ui->comboBox->addItem("Quantité");
    ui->le_type->addItem("Details");
    ui->le_type->addItem("Gros");
    //// matriel

    //ui->materielBtn_2->setStyleSheet("qproperty-icon:url(:/icons-green/icons-green/home.svg); color: #4A7C59; border-top-left-radius: 15px; border-bottom-left-radius: 15px; background: #FAF3DD;");
    ui->mainContentSTackWidget_2->setCurrentIndex(0);
    ui->etatComboBox_3->addItem("Fonctionnelle");ui->etatComboBox_3->addItem("Non Fonctionnelle");
    ui->etatComboBox_4->addItem("Fonctionnelle");ui->etatComboBox_4->addItem("Non Fonctionnelle");
    ui->alertAjout_11->hide();ui->alertAjout_12->hide();ui->alertAjout_13->hide();ui->alertAjout_14->hide();
    ui->alertAjout_15->hide();
    ui->idMatLE_2->hide();
    ui->alertAjout_16->hide();ui->alertAjout_17->hide();ui->alertAjout_18->hide();ui->alertAjout_19->hide();
    ui->alertAjout_20->hide();
    ui->triEmployesComboBox_2->addItem("par défaut");
    ui->triEmployesComboBox_2->addItem("Age");
    ui->triEmployesComboBox_2->addItem("Capacité");
    ui->triEmployesComboBox_2->addItem("Prix");

    //plante

    // Create a QSqlTableModel and set the table name
    modelp = new QSqlTableModel(this);
    modelp->setTable("plante");

    // Set the model for the table view
    ui->tableView->setModel(modelp);

    // Load data from the database
    modelp->select();

    // Create a query model
    modelpp = new QSqlQueryModel(this);
    ui->tableView_s->setModel(modelpp);

    pieChart = new Chart();

    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_pushButton_3_clicked);

    int ret=A.connect_arduino(); // lancer la connexion à arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_bu_clicked())); // permet de lancer
        //le slot update_label suite à la reception du signal readyRead (reception des données).
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(on_nom_4_selectionChanged())); // permet de lancer
        //le slot update_label suite à la reception du signal readyRead (reception des données).

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    QString nom  = ui->nom->text();
    QString prenom=ui->prenom->text();
    QString email=ui->email_2->text();
    QString mdp=ui->mdp_2->text();
    QString adresse=ui->adresse_2->text();
    QString poste=ui->poste_2->currentText();
    int num= ui->num_2->text().toInt();
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
        ui->tableemploye_2->setModel(model);
        ui->tableemploye_2->resizeColumnsToContents();
        ui->tableemploye_2->verticalHeader()->setDefaultSectionSize(50);

        ui->nom->setText("");
        ui->prenom->setText("");
        ui->email_2->setText("");
        ui->mdp_2->setText("");
        ui->adresse_2->setText("");
        ui->poste_2->setCurrentIndex(-1);
        ui->salaire->setText("");
        ui->num_2->setText("");

       QMessageBox::information(nullptr, QObject::tr("CORRECT !"),
                   QObject::tr("Create successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else

       QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                   QObject::tr("create  failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_supprimer_3_clicked()
{
    employe s(selected);
    bool test =s.supprimer();
    if (test)
    {

      //s.afficher();
        employemodel *model = new employemodel;
        model->refresh(); // load data from the database
        ui->tableemploye_2->setModel(model);
        ui->tableemploye_2->resizeColumnsToContents();
        ui->tableemploye_2->verticalHeader()->setDefaultSectionSize(50);

        ui->nom->setText("");
        ui->prenom->setText("");
        ui->email_2->setText("");
        ui->mdp_2->setText("");
        ui->adresse_2->setText("");
        ui->poste_2->setCurrentIndex(-1);
        ui->salaire->setText("");
        ui->num_2->setText("");

       QMessageBox::information(nullptr, QObject::tr("CORRECT !"),
                   QObject::tr("delete sucessful \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else

       QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                   QObject::tr("delete failed \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_tableemploye_2_clicked(const QModelIndex &index)
{
    selected = ui->tableemploye_2->model()->data(index).toInt();
    employe e = getEmployeeData(selected);

    ui->nom->setText(e.getNom());
    ui->prenom->setText(e.getPrenom());
    ui->email_2->setText(e.getEmail());
    ui->mdp_2->setText(e.getMdp());
    ui->adresse_2->setText(e.getAdresse());
    if(e.getPoste() == "Admin")
    ui->poste_2->setCurrentIndex(0);
    else
    ui->poste_2->setCurrentIndex(1);
    ui->salaire->setText(QString::number(e.getSalaire()));
    ui->num_2->setText(QString::number(e.getNum()));

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
void MainWindow::on_modifier_3_clicked()
{
    QString nom  = ui->nom->text();
    QString prenom=ui->prenom->text();
    QString email=ui->email_2->text();
    QString mdp=ui->mdp_2->text();
    QString adresse=ui->adresse_2->text();
    QString poste=ui->poste_2->currentText();
    int num= (int) ui->num_2->text().toInt();
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
       ui->tableemploye_2->setModel(model);
       ui->tableemploye_2->resizeColumnsToContents();
       ui->tableemploye_2->verticalHeader()->setDefaultSectionSize(50);
       ui->nom->setText("");
       ui->prenom->setText("");
       ui->email_2->setText("");
       ui->mdp_2->setText("");
       ui->adresse_2->setText("");
       ui->poste_2->setCurrentIndex(-1);
       ui->salaire->setText("");
       ui->num_2->setText("");

    }
    else

       QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                   QObject::tr("create  failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

////mailing
void MainWindow::on_pushButton_12_clicked()
{
    smtp* ssmtp = new smtp("hamed.nisrine@esprit.tn", "ekdy fscy civv wwcp", "smtp.gmail.com", 465);

                  connect(ssmtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

                  QString email=ui->rcpt_3->text();

                  QString b=ui->subject_3->text();

                  QString ob=ui->msg_3->toPlainText();

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
void MainWindow::on_pushButton_10_clicked()
{
    employe e;
     ui->tableemploye_2->setModel(e.recherche_employe(ui->recherche_2->text()));
}

void MainWindow::on_pushButton_11_clicked()
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




void MainWindow::on_triId_9_clicked()
{
    ui->tableemploye_2->setModel(e.triID());
}

void MainWindow::on_pushButton_13_clicked()
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
        chartView->setParent(ui->statE_2);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chartView->show();
}

void MainWindow::on_bu_clicked()
{
    data= A.read_from_arduino();
         qDebug() <<data;
       employe e;
        if (data== "1" || data == "1\r\n") {
            e.incrementNbEmp();
         qDebug() << "Successfully incremented nb_Emp";
            }
}
//vente

void MainWindow::on_pushButton_ajout_clicked()
{
    int nom = ui->le_nom_2->text().toInt();
    QString type = ui->le_type->currentText();

    QString date = ui->le_date->text();
    QString code = ui->le_code->text();

    QString marche = ui->le_marche->text();
    QString prix = ui->le_prix->text();
    QString poids = ui->le_poids->text();
    QString quantite = ui->le_quantite->text();
     vente v (nom,type,date,code,marche,prix,poids,quantite);
    bool test =v.ajouter();
    if (test)
    {
        ui->tab_ventes->setModel(v.afficher());
        stat();
        sms s;
         const QString msg = "Vous avez ajouté une vente sous le nom : "+QString::number(nom);

        const QString recipient_phone_number = "+21654485058";

       s.sendSMS(recipient_phone_number, msg);
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectué\n" "click cancel to exit."),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("ajout non effectué\n" "click cancel to exit."),QMessageBox::Cancel);
    }


}

void MainWindow::on_pb_supp_clicked()
{
    vente v1;
    v1.setnom(ui->le_nom_supp->text().toInt());
    bool test = v1.supprimer(v1.getnom());
    if (test)
    {
        ui->tab_ventes->setModel(v1.afficher());
        stat();
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("suppression effectué\n" "click cancel to exit."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("suppression non effectué\n" "click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->tab_ventes->setModel(v.tri(arg1));
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
   ui->tab_ventes->setModel(v.rechercher(arg1));
}

void MainWindow::on_pushButton_2_clicked()
{
    QString strStream;
       QTextStream out(&strStream);
       QDate currentDate = QDate::currentDate();
       QString date = currentDate.toString("dd-MM-yyyy");


       const int rowCount = ui->tab_ventes->model()->rowCount();
       const int columnCount = ui->tab_ventes->model()->columnCount();

       out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           <<  QString("<title>%1</title>\n").arg("col1")
           <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis "+date+"</h3>"
           "<h1 style='text-align: center;'>Liste des ventes</h1>\n"
           "<br>\n"
           "<br>\n"
               "<div align='center'>"
           "<table border=1 cellspacing=0 cellpadding=2>\n";

       // headers
       out << "<thead><tr bgcolor=#f0f0f0>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->tab_ventes->isColumnHidden(column))
               out << QString("<th>%3</th>").arg(ui->tab_ventes->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->tab_ventes->isColumnHidden(column)) {
                   QString data = ui->tab_ventes->model()->data(ui->tab_ventes->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%3</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
               "</div>"
           "</body>\n"
           "</html>\n";

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);

       QPrinter printer;

           document->print(&printer);


       delete document;
}
void MainWindow::stat()
{
    QLayout* layoutTest = ui->statContainer->layout();

    if (layoutTest) {
        delete layoutTest;
    }
    QChart *chart = new QChart();
    chart->setTitle("% Type");
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    QVector<int> stat = v.stat();
    int nbr1 = stat.front(),nbr2 = stat.back();
    int somme = nbr1 + nbr2;
    float prcD = (float(nbr1) / somme)*100, prcG = (float(nbr2) / somme)*100;
    QPieSeries * seriesQuantity = new QPieSeries();
    seriesQuantity->append("Details %"+QString::number(prcD), stat.front());
    seriesQuantity->append("Gros %"+QString::number(prcG), stat.back());
    chart->addSeries(seriesQuantity);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->statContainer->setLayout(layout);
}


void MainWindow::on_pushButton_6_clicked()
{

    QString nomProduit = ui->lineEdit_2->text();
    QString codePromo = ui->lineEdit_3->text();
    float prixInitial=0,prixRemise=0;
    QSqlQuery query;
    query.prepare("SELECT prix_vente FROM vente WHERE nom = :nom AND code_promo = :code");
    query.bindValue(":nom",nomProduit);
    query.bindValue(":code",codePromo);
    if(query.exec() && query.next()){
        prixInitial = query.value("prix_vente").toFloat();
        ui->label_6->setText(QString::number(prixInitial));
        prixRemise = prixInitial*0.8;
        ui->label_7->setText(QString::number(prixRemise));
    } else {
        QMessageBox::critical(nullptr,QObject::tr("Données incorrecte"),QObject::tr("vente ou code promo introuvable\n" "click cancel to exit."),QMessageBox::Cancel);
    }

}




void MainWindow::on_nom_4_selectionChanged()
{
    data = A.read_from_arduino();
    int d = data.toInt();
    qDebug() << d;

    // Assuming GA_A is an instance of your class handling Arduino communication

    QString nom = ui->nom_4->text();
    QSqlQuery query;

    if (d == 1  ) {


        query.prepare("SELECT humide FROM vente WHERE nom = :nom");
        query.bindValue(":nom", nom);
        query.exec();

        if (query.next()) {
           int humide = query.value(0).toInt();

            query.prepare("UPDATE vente SET humide = 0 WHERE nom = :nom");
            query.bindValue(":nom", nom);
            query.exec();

            QMessageBox::information(this, "moteur", "ON", QMessageBox::Cancel);
        }
    }
    else {

        query.prepare("SELECT humide FROM vente WHERE nom = :nom");
        query.bindValue(":nom", nom);
        query.exec();

        if (query.next()) {
            int humide = query.value(0).toInt();

            query.prepare("UPDATE vente SET humide = 1 WHERE nom = :nom");
            query.bindValue(":nom", nom);
            query.exec();

            // Uncomment the line below if you want to show a message
             QMessageBox::information(this, "moteur", "OFF", QMessageBox::Cancel);
        }
    }
}
//materiel
void MainWindow::on_ajoutMaterielPageBtn_2_clicked()
{
    ui->mainContentSTackWidget_2->setCurrentIndex(0);
    ui->alertAjout_11->hide();ui->alertAjout_12->hide();ui->alertAjout_13->hide();ui->alertAjout_14->hide();
    ui->alertAjout_15->hide();
    ui->alertAjout_16->hide();ui->alertAjout_17->hide();ui->alertAjout_18->hide();ui->alertAjout_19->hide();
    ui->alertAjout_20->hide();
}
void MainWindow::on_afficherMaterielPageBtn_3_clicked()
{
    ui->mainContentSTackWidget_2->setCurrentIndex(1);
    ui->materielTableView_2->setModel(m.afficherMateriel());
    statMateriel();
    ui->alertAjout_11->hide();ui->alertAjout_12->hide();ui->alertAjout_13->hide();ui->alertAjout_14->hide();
    ui->alertAjout_15->hide();
    ui->alertAjout_16->hide();ui->alertAjout_17->hide();ui->alertAjout_18->hide();ui->alertAjout_19->hide();
    ui->alertAjout_20->hide();
}
void MainWindow::on_materielModifBtn_3_clicked()
{
    ui->mainContentSTackWidget_2->setCurrentIndex(3);
}
void MainWindow::on_afficherMaterielPageBtn_4_clicked()
{
    ui->mainContentSTackWidget_2->setCurrentIndex(2);
}

void MainWindow::on_ajoutMaterielBtn_3_clicked()
{
    if(ui->prixLineEdit_3->text() =="" || ui->nomLE_3->text() == "" || ui->ageLE_3->text() =="" || ui->prixLineEdit_3->text() == "" || ui->capLineEdit_3->text() =="")
    {
        ui->alertAjout_11->hide();ui->alertAjout_12->hide();ui->alertAjout_13->hide();ui->alertAjout_14->hide();
        ui->alertAjout_15->hide();
    }
    else{
        QString mat = ui->matLineEdit_3->text();
        QString nom = ui->nomLE_3->text();
        QString etat = ui->etatComboBox_3->currentText();
        int age = ui->ageLE_3->text().toInt();
        float prix = ui->prixLineEdit_3->text().toFloat();
        float cap = ui->capLineEdit_3->text().toFloat();
        materiel mtrl(0,age,nom,mat,etat,cap,prix);
        if(mtrl.ajouterMateriel())
        {
            ui->materielTableView_2->setModel(m.afficherMateriel());
            ui->alertAjout_11->hide();ui->alertAjout_12->hide();ui->alertAjout_13->hide();ui->alertAjout_14->hide();
            ui->alertAjout_15->hide();
            ui->mainContentSTackWidget_2->setCurrentIndex(1);
            statMateriel();
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                                  QObject::tr("Echec d'opération. \n"
                                              "Click me to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_materielTableView_2_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString qrCodeData;
    QModelIndex sibling = index.sibling(row,0);
    QString id = ui->materielTableView_2->model()->data(sibling).toString();

                QSqlQuery qry;
                qry.prepare("SELECT * FROM materiel WHERE id=:id" );
                qry.bindValue(":id",id);
                if(qry.exec())
                {
                    while(qry.next())
                    {
                        ui->idMatLE_2->setText(qry.value(0).toString());
                        ui->matLineEdit_3->setText(qry.value(1).toString());
                        ui->nomLE_3->setText(qry.value(2).toString());
                        ui->prixLineEdit_3->setText(qry.value(6).toString());
                        ui->etatComboBox_3->setCurrentText(qry.value(3).toString());
                        ui->ageLE_3->setText(qry.value(4).toString());
                        ui->capLineEdit_3->setText(qry.value(5).toString());
                         qrCodeData ="ID : "+qry.value(0).toString()+" | Matricul : "+qry.value(1).toString()+" | Nom : "+qry.value(2).toString()+" | Prix : "+qry.value(6).toString()+" | Etat : "+qry.value(3).toString()+" | Capacité : "+qry.value(5).toString();
                    }
                }
                //QR CODE
                using namespace qrcodegen;
                // Create the QR Code object
                  QrCode qr = QrCode::encodeText( qrCodeData.toUtf8().data(), QrCode::Ecc::MEDIUM );
                  qint32 sz = qr.getSize();
                  QImage im(sz,sz, QImage::Format_RGB32);
                  QRgb black = qRgb(  0,  0,  0);
                  QRgb white = qRgb(255,255,255);
               for (int y = 0; y < sz; y++)
                    for (int x = 0; x < sz; x++)
                         im.setPixel(x,y,qr.getModule(x, y) ? black : white );
               ui->qrCodeLabel_2->setPixmap( QPixmap::fromImage(im.scaled(150,150,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

void MainWindow::on_ajoutMaterielBtn_4_clicked()
{
    if(ui->prixLineEdit_4->text() =="" || ui->nomLE_4->text() == "" || ui->ageLE_4->text() =="" || ui->prixLineEdit_4->text() == "" || ui->capLineEdit_4->text() =="")
    {
        ui->alertAjout_16->hide();ui->alertAjout_17->hide();ui->alertAjout_18->hide();ui->alertAjout_19->hide();
        ui->alertAjout_20->hide();
    }
    else{
        int id = ui->idMatLE_2->text().toInt();
        QString mat = ui->matLineEdit_4->text();
        QString nom = ui->nomLE_4->text();
        QString etat = ui->etatComboBox_4->currentText();
        int age = ui->ageLE_4->text().toInt();
        float prix = ui->prixLineEdit_4->text().toFloat();
        float cap = ui->capLineEdit_4->text().toFloat();
        materiel mtrl(id,age,nom,mat,etat,cap,prix);
        if(mtrl.modifierMateriel())
        {
            ui->materielTableView_2->setModel(m.afficherMateriel());
            ui->alertAjout_16->hide();ui->alertAjout_17->hide();ui->alertAjout_18->hide();ui->alertAjout_19->hide();
            ui->alertAjout_20->hide();
            ui->mainContentSTackWidget_2->setCurrentIndex(1);
            statMateriel();
            if(etat == "Non Fonctionnelle")
                sendMail(QString::number(id),nom);
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                                  QObject::tr("Echec d'opération. \n"
                                              "Click me to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_materielSuppBtn_2_clicked()
{
    QModelIndex indexItem = ui->materielTableView_2->currentIndex();
    int row = indexItem.row();
    QModelIndex sibling = indexItem.sibling(row,0);
    int id = ui->materielTableView_2->model()->data(sibling).toInt();
    qDebug() << id;
    if(m.supprimerMateriel(id))
    {
       ui->materielTableView_2->setModel(m.afficherMateriel());
       statMateriel();
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec d'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_employesRechBar_2_textChanged(const QString &arg1)
{
  ui->materielTableView_2->setModel(m.rechercherMateriel(arg1));
}

void MainWindow::on_triEmployesComboBox_2_currentIndexChanged(const QString &arg1)
{
    ui->materielTableView_2->setModel(m.triMateriel(arg1));
}
void MainWindow::statMateriel()
{
    QLayout* layoutTest = ui->materielStatContainer_2->layout();

    if (layoutTest) {
        delete layoutTest;
    }
    QChart *chart = new QChart();
    chart->setTitle("% Etat");
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    QVector<int> stat = m.statMateriel();
    int nbrF = stat.front(),nbrNF = stat.back();
    int somme = nbrF + nbrNF;
    float prcF = (float(nbrF) / somme)*100, prcNF = (float(nbrNF) / somme)*100;
    QPieSeries * seriesQuantity = new QPieSeries();
    seriesQuantity->append("Fonctionnelle %"+QString::number(prcF), stat.front());
    seriesQuantity->append("Non Fonctionnelle %"+QString::number(prcNF), stat.back());
    chart->addSeries(seriesQuantity);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->materielStatContainer_2->setLayout(layout);
}

void MainWindow::on_materielModifBtn_4_clicked()
{
    QString strStream;
       QTextStream out(&strStream);
       QDate currentDate = QDate::currentDate();
       QString date = currentDate.toString("dd-MM-yyyy");


       const int rowCount = ui->materielTableView_2->model()->rowCount();
       const int columnCount = ui->materielTableView_2->model()->columnCount();

       out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           <<  QString("<title>%1</title>\n").arg("col1")
           <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis "+date+"</h3>"
           "<h1 style='text-align: center;'>Liste des materiels</h1>\n"
           "<br>\n"
           "<br>\n"
               "<div align='center'>"
           "<table border=1>\n";

       // headers
       out << "<thead><tr bgcolor=#f0f0f0>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->materielTableView_2->isColumnHidden(column))
               out << QString("<th>%2</th>").arg(ui->materielTableView_2->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->materielTableView_2->isColumnHidden(column)) {
                   QString data = ui->materielTableView_2->model()->data(ui->materielTableView_2->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%2</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
               "</div>"
           "</body>\n"
           "</html>\n";

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);

       QPrinter printer;

           document->print(&printer);


       delete document;
}

void MainWindow::sendMail(QString id,QString nom)
{
    Smtpp* smtp = new Smtpp("mohamed.ouerfelli@esprit.tn","testtest123A", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailsent(QString)));
        smtp->sendMail("mohamed.ouerfelli@esprit.tn", "mohamedouerfelli3@gmail.com" , "ALERTE MATERIEL","Matériel Non Fonctionnelle ID : '"+id+"', Nom : '"+nom+"' ,Veuillez vérifier son état.");
}
void   MainWindow::mailsent(QString status)
{

    if(status == "Message sent")
    {
        QMessageBox::information(nullptr,QObject::tr("MAIL Sent!"),
                              QObject::tr("Done ! \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_sendChatBtn_2_clicked()
{
    QString text,space="";
    float rassemblance=0;
    int tr=0;
    QString msg=ui->inputChatbot_2->text();
    ui->chatBot_2->appendPlainText(space);
    ui->chatBot_2->appendPlainText(msg);
    QSqlQuery qry,query;
     if(msg[0]!="#")
     {
        qry.prepare("select * from chatbot" );
        qry.exec();
        while(qry.next() && tr==0)
        {
            QString quest = qry.value(0).toString();
                int eq = 0,dif = 0;
                for(int i=0 ; i < msg.size(); i++)
                {
                       if(quest[i] == msg[i])
                           eq++;
                       else
                           dif++;
                }
                rassemblance = (eq / static_cast<float>(msg.size()))*100;
                if(rassemblance > 80)
                {
                    ui->chatBot_2->appendPlainText( "\n"+qry.value(1).toString());
                    tr=1;
                }
         }
        if(tr == 0)
        {

                ui->chatBot_2->appendPlainText( "Voulez vous ajouter un nouveau mot ? Écrivez votre réponse avec un # au début.");
                ui->labelCache_2->setText(msg);

        }
     }
     else if (msg[0]=="#"){
         QString msg1=msg.mid(1,msg.length()-1);
         query.prepare("insert into chatbot (quest,rep)""values(:quest,:rep)");
         query.bindValue(":quest", ui->labelCache_2->text());
         query.bindValue(":rep", msg1);
         query.exec();
         ui->chatBot_2->appendPlainText( "\n Merci ! Pour cette information");

     }
}


void MainWindow::on_push_ges_emp_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//plante

void MainWindow::on_addButton_clicked()
{
    // Get the max id from the database
    QSqlQuery maxIdQuery("SELECT MAX(id) FROM plante");
    maxIdQuery.next();

    int maxId = maxIdQuery.value(0).toInt();

    // Assuming you have a QLineEdit widget named IDLineEdit
    int id = ui->IDLineEdit->text().toInt();

    // Create a new Plante object with the entered data
    Plante plante(id, ui->nameLineEdit->text(), ui->characteristicsLineEdit->text(),
                  ui->quantitySpinBox->value());

    // Insert the new plante into the database
    plante.insert();

    // Refresh the model to display the updated data
    modelp->select();
}

void MainWindow::on_updateButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Update Plante"), tr("Please select a plant from the list."));
        return;
    }

    int id = ui->IDLineEdit->text().toInt();
    QString name = ui->nameLineEdit->text();
    QString characteristics = ui->characteristicsLineEdit->text();
    int quantity = ui->quantitySpinBox->value();

    Plante plante(id, name, characteristics, quantity);

    if (plante.update()) {
        QMessageBox::information(this, tr("Update Plant"), tr("Plant updated successfully."));
        refreshTableView();
    } else {
        QMessageBox::critical(this, tr("Update Plant"), tr("Failed to update plant."));
    }
}

void MainWindow::on_deleteButton_clicked()
{
    // Get the currently selected row(s)
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    // Delete the selected row(s) from the database
    foreach (const QModelIndex &index, selectedRows) {
        // Get the ID from the selected row
        int id = modelp->data(modelp->index(index.row(), 0)).toInt();

        // Create a QSqlQuery to delete the row with the specified ID
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM \"PLANTE\" WHERE \"ID\" = :id");
        deleteQuery.bindValue(":id", id);

        if (!deleteQuery.exec()) {
            qDebug() << "Error executing delete query:" << deleteQuery.lastError().text();
            // Handle the error as needed
        }
    }

    // Refresh the model to reflect the changes in the database
    modelp->select();
}



void MainWindow::refreshTableView()
{
    modelp->select();
}

void MainWindow::on_displayButton_clicked()
{
    // Retrieve the selected plant from the table view
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Display Plant"), tr("Please select a plant from the list."));
        return;
    }

    int id = index.sibling(index.row(), 0).data().toInt();

    // Create a QSqlQuery object to execute the SQL statement
    QSqlQuery query;

    // Prepare the SQL statement
    query.prepare("SELECT * FROM plante WHERE ID = ?");
    query.addBindValue(id);

    // Execute the SQL statement
    if (query.exec() && query.next()) {
        // Retrieve the plant information from the query result
        QString name = query.value(1).toString();
        QString characteristics = query.value(2).toString();
        int quantity = query.value(3).toInt();

        // Display the plant information
        QString message = "Plant ID: " + QString::number(id) + "\n";
        message += "Name: " + name + "\n";
        message += "Characteristics: " + characteristics + "\n";
        message += "Quantity: " + QString::number(quantity);

        QMessageBox::information(this, tr("Plant Information"), message);
    } else {
        QMessageBox::critical(this, tr("Display Plant"), tr("Failed to retrieve plant information."));
    }
}
void MainWindow::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text();

    // Execute the search query
    QSqlQuery query(db);
    query.prepare("SELECT * FROM PLANTE WHERE NAME LIKE ?");
    query.addBindValue("%" + searchTerm + "%");
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", query.lastError().text());
        return;
    }

    // Set the query model to display the search results
    modelpp->setQuery(query);
}
void MainWindow::on_generatePDFButton_clicked() {
    // Fetch data from the database (Replace with your database query)
    QSqlQuery query;
    query.exec("SELECT * FROM plante");

    QString data;
    while (query.next()) {
        QSqlRecord record = query.record();
        // Append data to the string in the desired format
        // Adjust this part according to your database schema
        data += record.value("name").toString() + "\t" +
                record.value("characteristics").toString() + "\n";
    }

    if (PDF::convertToPDF(data)) {
        qDebug() << "PDF generated successfully";
    } else {
        qDebug() << "Error generating PDF";
    }
}
void MainWindow::on_pushButton_3_clicked()
{
    // Fetch data from the database
    QVector<QPair<QString, int>> data = dbConnection->getData();

    // Pass the data to the chart
    pieChart->updateChart(data);
    pieChart->show();
}
//menu

void MainWindow::on_push_ges_vente_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_push_ges_mat_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_push_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_calender_clicked()
{
    MainWindow2 *w2 = new MainWindow2();
    w2->show();

}

void MainWindow::on_push_ges_plante_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
=======
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->materielBtn->setStyleSheet("qproperty-icon:url(:/icons-green/icons-green/home.svg); color: #4A7C59; border-top-left-radius: 15px; border-bottom-left-radius: 15px; background: #FAF3DD;");
    ui->mainContentSTackWidget->setCurrentIndex(0);
    ui->etatComboBox->addItem("Fonctionnelle");ui->etatComboBox->addItem("Non Fonctionnelle");
    ui->etatComboBox_2->addItem("Fonctionnelle");ui->etatComboBox_2->addItem("Non Fonctionnelle");
    ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
    ui->alertAjout_5->hide();
    ui->idMatLE->hide();
    ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
    ui->alertAjout_10->hide();
    ui->triEmployesComboBox->addItem("par défaut");
    ui->triEmployesComboBox->addItem("Age");
    ui->triEmployesComboBox->addItem("Capacité");
    ui->triEmployesComboBox->addItem("Prix");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajoutMaterielPageBtn_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(0);
    ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
    ui->alertAjout_5->hide();
    ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
    ui->alertAjout_10->hide();
}

void MainWindow::on_afficherMaterielPageBtn_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(1);
    ui->materielTableView->setModel(m.afficherMateriel());
    statMateriel();
    ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
    ui->alertAjout_5->hide();
    ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
    ui->alertAjout_10->hide();
}

void MainWindow::on_materielModifBtn_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(2);
}

void MainWindow::on_ajoutMaterielBtn_clicked()
{
    if(ui->prixLineEdit->text() =="" || ui->nomLE->text() == "" || ui->ageLE->text() =="" || ui->prixLineEdit->text() == "" || ui->capLineEdit->text() =="")
    {
        ui->alertAjout->show();ui->alertAjout_2->show();ui->alertAjout_3->show();ui->alertAjout_4->show();
        ui->alertAjout_5->show();
    }
    else{
        QString mat = ui->matLineEdit->text();
        QString nom = ui->nomLE->text();
        QString etat = ui->etatComboBox->currentText();
        int age = ui->ageLE->text().toInt();
        float prix = ui->prixLineEdit->text().toFloat();
        float cap = ui->capLineEdit->text().toFloat();
        materiel mtrl(0,age,nom,mat,etat,cap,prix);
        if(mtrl.ajouterMateriel())
        {
            ui->materielTableView->setModel(m.afficherMateriel());
            ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
            ui->alertAjout_5->hide();
            ui->mainContentSTackWidget->setCurrentIndex(1);
            statMateriel();
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                                  QObject::tr("Echec d'opération. \n"
                                              "Click me to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_materielTableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString qrCodeData;
    QModelIndex sibling = index.sibling(row,0);
    QString id = ui->materielTableView->model()->data(sibling).toString();

                QSqlQuery qry;
                qry.prepare("SELECT * FROM materiel WHERE id=:id" );
                qry.bindValue(":id",id);
                if(qry.exec())
                {
                    while(qry.next())
                    {
                        ui->idMatLE->setText(qry.value(0).toString());
                        ui->matLineEdit_2->setText(qry.value(1).toString());
                        ui->nomLE_2->setText(qry.value(2).toString());
                        ui->prixLineEdit_2->setText(qry.value(6).toString());
                        ui->etatComboBox_2->setCurrentText(qry.value(3).toString());
                        ui->ageLE_2->setText(qry.value(4).toString());
                        ui->capLineEdit_2->setText(qry.value(5).toString());
                         qrCodeData ="ID : "+qry.value(0).toString()+" | Matricul : "+qry.value(1).toString()+" | Nom : "+qry.value(2).toString()+" | Prix : "+qry.value(6).toString()+" | Etat : "+qry.value(3).toString()+" | Capacité : "+qry.value(5).toString();
                    }
                }
                //QR CODE
                using namespace qrcodegen;
                // Create the QR Code object
                  QrCode qr = QrCode::encodeText( qrCodeData.toUtf8().data(), QrCode::Ecc::MEDIUM );
                  qint32 sz = qr.getSize();
                  QImage im(sz,sz, QImage::Format_RGB32);
                  QRgb black = qRgb(  0,  0,  0);
                  QRgb white = qRgb(255,255,255);
               for (int y = 0; y < sz; y++)
                    for (int x = 0; x < sz; x++)
                         im.setPixel(x,y,qr.getModule(x, y) ? black : white );
               ui->qrCodeLabel->setPixmap( QPixmap::fromImage(im.scaled(150,150,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

void MainWindow::on_ajoutMaterielBtn_2_clicked()
{
    if(ui->prixLineEdit_2->text() =="" || ui->nomLE_2->text() == "" || ui->ageLE_2->text() =="" || ui->prixLineEdit_2->text() == "" || ui->capLineEdit_2->text() =="")
    {
        ui->alertAjout_6->show();ui->alertAjout_7->show();ui->alertAjout_8->show();ui->alertAjout_9->show();
        ui->alertAjout_10->show();
    }
    else{
        int id = ui->idMatLE->text().toInt();
        QString mat = ui->matLineEdit_2->text();
        QString nom = ui->nomLE_2->text();
        QString etat = ui->etatComboBox_2->currentText();
        int age = ui->ageLE_2->text().toInt();
        float prix = ui->prixLineEdit_2->text().toFloat();
        float cap = ui->capLineEdit_2->text().toFloat();
        materiel mtrl(id,age,nom,mat,etat,cap,prix);
        if(mtrl.modifierMateriel())
        {
            ui->materielTableView->setModel(m.afficherMateriel());
            ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
            ui->alertAjout_10->hide();
            ui->mainContentSTackWidget->setCurrentIndex(1);
            statMateriel();
            if(etat == "Non Fonctionnelle")
                sendMail(QString::number(id),nom);
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                                  QObject::tr("Echec d'opération. \n"
                                              "Click me to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_materielSuppBtn_clicked()
{
    QModelIndex indexItem = ui->materielTableView->currentIndex();
    int row = indexItem.row();
    QModelIndex sibling = indexItem.sibling(row,0);
    int id = ui->materielTableView->model()->data(sibling).toInt();
    if(m.supprimerMateriel(id))
    {
       ui->materielTableView->setModel(m.afficherMateriel());
       statMateriel();
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec d'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_employesRechBar_textChanged(const QString &arg1)
{
  ui->materielTableView->setModel(m.rechercherMateriel(arg1));
}

void MainWindow::on_triEmployesComboBox_currentIndexChanged(const QString &arg1)
{
    ui->materielTableView->setModel(m.triMateriel(arg1));
}
void MainWindow::statMateriel()
{
    QLayout* layoutTest = ui->materielStatContainer->layout();

    if (layoutTest) {
        delete layoutTest;
    }
    QChart *chart = new QChart();
    chart->setTitle("% Etat");
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    QVector<int> stat = m.statMateriel();
    int nbrF = stat.front(),nbrNF = stat.back();
    int somme = nbrF + nbrNF;
    float prcF = (float(nbrF) / somme)*100, prcNF = (float(nbrNF) / somme)*100;
    QPieSeries * seriesQuantity = new QPieSeries();
    seriesQuantity->append("Fonctionnelle %"+QString::number(prcF), stat.front());
    seriesQuantity->append("Non Fonctionnelle %"+QString::number(prcNF), stat.back());
    chart->addSeries(seriesQuantity);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->materielStatContainer->setLayout(layout);
}

void MainWindow::on_materielModifBtn_2_clicked()
{
    QString strStream;
       QTextStream out(&strStream);
       QDate currentDate = QDate::currentDate();
       QString date = currentDate.toString("dd-MM-yyyy");


       const int rowCount = ui->materielTableView->model()->rowCount();
       const int columnCount = ui->materielTableView->model()->columnCount();

       out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           <<  QString("<title>%1</title>\n").arg("col1")
           <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis "+date+"</h3>"
           "<h1 style='text-align: center;'>Liste des materiels</h1>\n"
           "<br>\n"
           "<br>\n"
               "<div align='center'>"
           "<table border=1>\n";

       // headers
       out << "<thead><tr bgcolor=#f0f0f0>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->materielTableView->isColumnHidden(column))
               out << QString("<th>%2</th>").arg(ui->materielTableView->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->materielTableView->isColumnHidden(column)) {
                   QString data = ui->materielTableView->model()->data(ui->materielTableView->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%2</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
               "</div>"
           "</body>\n"
           "</html>\n";

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);

       QPrinter printer;

           document->print(&printer);


       delete document;
}

void MainWindow::sendMail(QString id,QString nom)
{
    Smtp* smtp = new Smtp("mohamed.ouerfelli@esprit.tn","testtest123A", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailsent(QString)));
        smtp->sendMail("mohamed.ouerfelli@esprit.tn", "mohamedouerfelli3@gmail.com" , "ALERTE MATERIEL","Matériel Non Fonctionnelle ID : '"+id+"', Nom : '"+nom+"' ,Veuillez vérifier son état.");
}
void   MainWindow::mailsent(QString status)
{

    if(status == "Message sent")
    {
        QMessageBox::information(nullptr,QObject::tr("MAIL Sent!"),
                              QObject::tr("Done ! \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_sendChatBtn_clicked()
{
    QString text,space="";
    float rassemblance=0;
    int tr=0;
    QString msg=ui->inputChatbot->text();
    ui->chatBot->appendPlainText(space);
    ui->chatBot->appendPlainText(msg);
    QSqlQuery qry,query;
     if(msg[0]!="#")
     {
        qry.prepare("select * from chatbot" );
        qry.exec();
        while(qry.next() && tr==0)
        {
            QString quest = qry.value(0).toString();
                int eq = 0,dif = 0;
                for(int i=0 ; i < msg.size(); i++)
                {
                       if(quest[i] == msg[i])
                           eq++;
                       else
                           dif++;
                }
                rassemblance = (eq / static_cast<float>(msg.size()))*100;
                if(rassemblance > 80)
                {
                    ui->chatBot->appendPlainText( "\n"+qry.value(1).toString());
                    tr=1;
                }
         }
        if(tr == 0)
        {

                ui->chatBot->appendPlainText( "Voulez vous ajouter un nouveau mot ? Écrivez votre réponse avec un # au début.");
                ui->labelCache->setText(msg);

        }
     }
     else if (msg[0]=="#"){
         QString msg1=msg.mid(1,msg.length()-1);
         query.prepare("insert into chatbot (quest,rep)""values(:quest,:rep)");
         query.bindValue(":quest", ui->labelCache->text());
         query.bindValue(":rep", msg1);
         query.exec();
         ui->chatBot->appendPlainText( "\n Merci ! Pour cette information");

     }
}

void MainWindow::on_afficherMaterielPageBtn_2_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(2);
}

