#include "connexion.h"

connection::connection()
{

}

bool connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("moncef");
    db.setPassword("esprit23");

    if(db.open())
        test=true;

    return test;
}

void connection::closeconnection()
{
    db.close();
}

