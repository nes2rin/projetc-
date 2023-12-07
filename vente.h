#ifndef VENTE_H
#define VENTE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>


class vente
{
public:
    vente();
    vente(int,QString,QString,QString,QString,QString,QString,QString);
    int getnom();
    QString gettype();
    QString getdate();
    QString getcode();
    QString getmarche();
    QString getprix();
    QString getpoids();
    QString getquantite();
    void setnom(int);
    void settype(QString);
    void setdate(QString);
    void setcode(QString);
    void setmarche(QString);
    void setprix(QString);
    void setpoids(QString);
    void setquantite(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    QSqlQueryModel * rechercher(QString recherche);
    QSqlQueryModel * tri(QString tri);
    QVector<int> stat();
    float promo(QString,QString);

private:
    int nom;
    QString type,date,code,marche,prix,poids,quantite;




};

#endif // VENTE_H
