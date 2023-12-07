#include "rh.h"
#include "ui_rh.h"

rh::rh(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rh)
{
    ui->setupUi(this);
    employe E;
    employemodel *model = new employemodel;
    model->refresh1(); // load data from the database

    ui->tableemploye1->setModel(model);
    ui->tableemploye1->resizeColumnsToContents();
    ui->tableemploye1->verticalHeader()->setDefaultSectionSize(50);
}

rh::~rh()
{
    delete ui;
}
employe rh::getEmployeeData(int employeeId) {
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

void rh::on_tableemploye1_clicked(const QModelIndex &index)
{
    selected = ui->tableemploye1->model()->data(index).toInt();
    employe e = getEmployeeData(selected);

    ui->nom1->setText(e.getNom());
    ui->prenom1->setText(e.getPrenom());
    ui->email1->setText(e.getEmail());
    ui->mdp1->setText(e.getMdp());
    ui->adresse1->setText(e.getAdresse());
    if(e.getPoste() == "Admin")
    ui->poste1->setCurrentIndex(0);
    else
    ui->poste1->setCurrentIndex(1);
    ui->salaire1->setText(QString::number(e.getSalaire()));
    ui->num1->setText(QString::number(e.getNum()));
}
void rh::on_modifier1_clicked()
{
    QString nom  = ui->nom1->text();
    QString prenom=ui->prenom1->text();
    QString email=ui->email1->text();
    QString mdp=ui->mdp1->text();
    QString adresse=ui->adresse1->text();
    QString poste=ui->poste1->currentText();
    int num= (int) ui->num1->text().toInt();
    float salaire= (float) ui->salaire1->text().toFloat();



    QSqlQuery query;
  employe e(selected,nom,prenom,email,mdp,adresse,poste,salaire,num);
  bool test=e.modifier();
    if (test)
    {
       QMessageBox::information(nullptr, QObject::tr("CORRECT !"),
                   QObject::tr("Create successful.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
       employemodel *model = new employemodel;
       model->refresh1(); // load data from the database
       ui->tableemploye1->setModel(model);
       ui->tableemploye1->resizeColumnsToContents();
       ui->tableemploye1->verticalHeader()->setDefaultSectionSize(50);
       ui->nom1->setText("");
       ui->prenom1->setText("");
       ui->email1->setText("");
       ui->mdp1->setText("");
       ui->adresse1->setText("");
       ui->poste1->setCurrentIndex(-1);
       ui->salaire1->setText("");
       ui->num1->setText("");

    }
    else

       QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                   QObject::tr("create  failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}
