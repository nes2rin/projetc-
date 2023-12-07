#include "employe.h"
#include <QtDebug>
employe::employe()
{

}
bool employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employe (nom,prenom,email,mdp,adresse,poste,salaire,num) "
      "VALUES (:nom,:prenom,:email,:mdp,:adresse,:poste,:salaire,:num)");
    query.bindValue(":nom",nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":mdp",mdp );
    query.bindValue(":adresse",adresse );
    query.bindValue(":poste",poste );
    query.bindValue(":salaire",salaire);
    query.bindValue(":num",num );

return query.exec();


}
QSqlQueryModel *employe ::afficher()
{
QSqlQueryModel*model =new QSqlQueryModel();

     model->setQuery("SELECT* FROM employe ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("Prenom"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("E-mail"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Poste"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numéro"));

return model;
}
QSqlQueryModel* employe::afficher1(int id)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Numéro"));

    return model;
}



bool employe::supprimer()
{
    QSqlQuery query;
    query.prepare("DELETE FROM employe where id=:id");

    query.bindValue(":id",id);

return query.exec();
}

bool employe::modifier()
{
    QSqlQuery query;
    query.prepare("update employe set nom=:nom, prenom=:prenom, email=:email, mdp=:mdp, adresse=:adresse, poste=:poste, salaire=:salaire, num=:num where id=:id");
    query.bindValue(":nom",nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":mdp",mdp );
    query.bindValue(":adresse",adresse );
    query.bindValue(":poste",poste );
    query.bindValue(":salaire",salaire );
    query.bindValue(":num",num );
    query.bindValue(":id",id );
    return query.exec();

}
int employe::statistiquesemploye(QString poste)
{
    QSqlQuery query;
    query.prepare("select count(*) from employe where poste=:poste ");
    query.bindValue(":poste",poste);
    query.exec();
    query.next();

    return query.value(0).toInt();

}

QSqlQueryModel * employe::recherche_employe(QString search)
{

    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from employe  where id like '%"+search+"%'or nom like '%"+search+"%' or prenom like '%"+search+"%' or email like '%"+search+"%'or mdp like '%"+search+"%' or adresse like '%"+search+"%'or mdp like '%"+search+"%' or poste like '%"+search+"%'or num like '%"+search+"%'";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}
QSqlQueryModel * employe::triID()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY id");
    return model;

}
//pour increment nb eh
bool employe::incrementNbEmp() {
    QSqlQuery query;
    query.prepare("UPDATE NB_EMPLOYE SET NBEMP = NBEMP + 1");

    if (!query.exec()) {
        qDebug() << "Failed to increment NBEMP in database";
        return false;
    }

    return true;
}
