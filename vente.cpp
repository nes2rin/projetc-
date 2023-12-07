#include "vente.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QObject>
vente::vente()
{
    nom=0;type="";date="";code="";marche="";prix="";poids="";quantite="";

}
vente::vente(int nom,QString type,QString date,QString code,QString marche,QString prix,QString poids,QString quantite)
{
    this->nom=nom;
    this->type=type;
    this->date=date;
    this->code=code;
    this->marche=marche;
    this->prix=prix;
    this->poids=poids;
    this->quantite=quantite;
}
int vente::getnom(){return nom;}
QString vente::gettype(){return type;}
QString vente::getdate(){return date;}
QString vente::getcode(){return code;}
QString vente::getmarche(){return marche;}
QString vente::getprix(){return prix;}
QString vente::getpoids(){return poids;}
QString vente::getquantite(){return quantite;}
void vente::setnom(int nom){this->nom=nom;}
void vente::settype(QString type){this->type=type;}
void vente::setdate(QString date){this->date=date;}
void vente::setcode(QString code){this->code=code;}
void vente::setmarche(QString marche){this->marche=marche;}
void vente::setprix(QString prix){this->prix=prix;}
void vente::setpoids(QString poids){this->poids=poids;}
void vente::setquantite(QString quantite){this->quantite=quantite;}
bool vente::ajouter()
{
    bool test=false;
    QSqlQuery query;
    QString nom_string =QString::number(nom);
          query.prepare("INSERT INTO vente (nom, type, date_exp, code_promo,marche_vente,prix_vente,poids_net,quantite) "
                        "VALUES (:nom, :type, :date_exp, :code_promo, :marche_vente , :prix_vente , :poids_net , :quantite)");
          query.bindValue(":nom", nom);
          query.bindValue(":type", type);
          query.bindValue(":date_exp", date);
          query.bindValue(":code_promo", code);
          query.bindValue(":marche_vente", marche);
          query.bindValue(":prix_vente", prix);
          query.bindValue(":poids_net", poids);
          query.bindValue(":quantite", quantite);

          return query.exec();





    return test;
}

bool vente::supprimer(int nom)
{

    QSqlQuery query;
    QString nom_string =QString::number(nom);
          query.prepare("delete from vente where nom=:nom ");
          query.bindValue(":nom", nom);

          return query.exec();

}
QSqlQueryModel* vente::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM vente");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("code"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("marche"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("prix"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("poids"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("quantite"));
    return model;
}
QSqlQueryModel * vente::rechercher(QString recherche)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM vente WHERE (UPPER(nom) LIKE UPPER('%"+recherche+"%') OR UPPER(date_exp) LIKE UPPER('%"+recherche+"%') OR UPPER(type) LIKE UPPER('%"+recherche+"%'))");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("marche"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("poids"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("quantite"));
    return model;
}
QSqlQueryModel * vente::tri(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "Par défaut"){
        model->setQuery("SELECT * FROM vente");
    }
    else if(tri == "Nom"){
        model->setQuery("SELECT * FROM vente ORDER BY nom");
    }else if (tri == "Type") {
        model->setQuery("SELECT * FROM vente ORDER BY type");
    } else if (tri == "Quantité") {
        model->setQuery("SELECT * FROM vente ORDER BY quantite");
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("code"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("marche"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("poids"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("quantite"));
    return model;
}
QVector<int> vente::stat()
{
    QVector<int> stat;
    QSqlQuery query;
    int nbr1=0,nbr2=0;
    query.exec("SELECT "
               "SUM(CASE WHEN type = 'Details' THEN 1 ELSE 0 END) AS num_1, "
               "SUM(CASE WHEN type = 'Gros' THEN 1 ELSE 0 END) AS num_2 "
               "FROM vente");
    if (query.next()) {
        nbr1 = query.value("num_1").toInt();
        nbr2 = query.value("num_2").toInt();
    }
    stat.push_back(nbr1);
    stat.push_back(nbr2);
    return stat;
}
float vente::promo(QString nomProduit,QString codePromo)
{
    float prixInitial=0;
    QSqlQuery query;
    query.prepare("SELECT prix_vente FROM vente WHERE nom = :nom AND code_promo = :code");
    query.bindValue(":nom",nomProduit);
    query.bindValue(":code",codePromo);
    if(query.exec() && query.next()){
        prixInitial = query.value("prix_vente").toFloat();
    }
    return prixInitial;
}
