#include "materiel.h"

materiel::materiel()
{

}
materiel::materiel(int id,int age,QString nom,QString matricul,QString etat,float cap,float prix)
{
    this->id = id;
    this->age = age;
    this->nom_machine = nom;
    this->matricul = matricul;
    this->etat = etat;
    this->capacite = cap;
    this->prix = prix;
}
bool materiel::ajouterMateriel()
{
    QSqlQuery query;
    QString pr = QString::number(prix);
    QString cap = QString::number(capacite);
    QString ag = QString::number(age);
    query.prepare("INSERT INTO materiel (matricul,nom_machine,etat,age,capacite,prix)""VALUES (:matricul,:nom_machine,:etat,:age,:capacite,:prix)");
    query.bindValue(":matricul",matricul);
    query.bindValue(":nom_machine",nom_machine);
    query.bindValue(":etat",etat);
    query.bindValue(":age",ag);
    query.bindValue(":capacite",cap);
    query.bindValue(":prix",pr);
    return query.exec();
}
QSqlQueryModel * materiel::afficherMateriel()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from materiel");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom du machine"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Age"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Capacité"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Prix"));
    return model;
}
bool materiel::supprimerMateriel(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM materiel WHERE id= :id");
    query.bindValue(":id",id);
    return query.exec();
}

bool materiel::modifierMateriel()
{
    QSqlQuery query;
    QString pr = QString::number(prix);
    QString cap = QString::number(capacite);
    QString ag = QString::number(age);
    QString idS = QString::number(id);
    query.prepare("UPDATE materiel "" SET matricul=:matricul, nom_machine=:nom, etat=:etat, age=:age, capacite=:capacite, prix=:prix WHERE id=:id");
    query.bindValue(":id", idS);
    query.bindValue(":matricul",matricul);
    query.bindValue(":nom",nom_machine);
    query.bindValue(":etat",etat);
    query.bindValue(":age",ag);
    query.bindValue(":capacite",cap);
    query.bindValue(":prix",pr);
    return query.exec();
}

QSqlQueryModel * materiel::rechercherMateriel(QString recherche)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * from materiel WHERE (UPPER(matricul) LIKE UPPER('%"+recherche+"%') OR UPPER(nom_machine) LIKE UPPER('%"+recherche+"%') OR UPPER(id) LIKE UPPER('%"+recherche+"%') )");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom du machine"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Age"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Capacité"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Prix"));
    return model;
}

QSqlQueryModel * materiel::triMateriel(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "par défaut"){
        model->setQuery("SELECT * FROM materiel");
    }else if (tri == "Age") {
        model->setQuery("SELECT * FROM materiel ORDER BY age");
    } else if (tri == "Capacité") {
        model->setQuery("SELECT * FROM materiel ORDER BY capacite");
    } else if (tri == "Prix") {
        model->setQuery("SELECT * FROM materiel ORDER BY prix");
    }
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Nom du machine"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Age"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Capacité"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Prix"));
    return model;
}

QVector<int> materiel::statMateriel()
{
    QVector<int> stat;
    QSqlQuery query;
    int nbr1=0,nbr2=0;
    query.exec("SELECT "
               "SUM(CASE WHEN etat = 'Fonctionnelle' THEN 1 ELSE 0 END) AS num_1, "
               "SUM(CASE WHEN etat = 'Non Fonctionnelle' THEN 1 ELSE 0 END) AS num_2 "
               "FROM materiel");
    if (query.next()) {
        nbr1 = query.value("num_1").toInt();
        nbr2 = query.value("num_2").toInt();
    }
    stat.push_back(nbr1);
    stat.push_back(nbr2);
    return stat;
}
