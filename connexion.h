#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlQuery>
#include <QSqlQueryModel>

class connection
{
    QSqlDatabase db;
public:
    connection();
    bool createconnection();
    void closeconnection();
};

#endif // CONNEXION_H
