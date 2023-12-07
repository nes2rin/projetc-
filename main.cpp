
#include "login.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "employe.h"
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;

    // Save an integer to settings
    Connection c;

    bool test=c.createconnect();
        login w;
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("CORRECT !"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
=======
#include "mainwindow.h"
#include <QApplication>
#include "connexion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    connection c;
    bool cnx = c.createconnection();
    if(cnx)
        w.show();
    else
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Data Base connection failed. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    return a.exec();
}
 
