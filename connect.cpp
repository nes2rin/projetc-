#include "connect.h"

Connect::Connect()
{
    // Initialize database connection using QODBC driver
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("nesrin");//inserer nom de l'utilisateur
    db.setPassword("123456789");//inserer mot de passe de cet utilisateur

    if (!db.open()) {
        qDebug() << "Error: Unable to open database";
    }
}

Connect::~Connect()
{
    db.close();
}

/*QVector<QPair<QString, int>> Connect::getData()
{
    QVector<QPair<QString, int>> data;

    // Fetch data from your ODBC database and populate 'data' vector

    return data;
}*/
QVector<QPair<QString, int>> Connect::getData()
{
    QVector<QPair<QString, int>> data;

    // Fetch data from the "plante" table in the database
    QSqlQuery query("SELECT name, quantity FROM plante");

    while (query.next()) {
        QString Name = query.value(0).toString();
        int quantity = query.value(1).toInt();
        data.append(qMakePair(Name, quantity));
    }

    return data;
}
