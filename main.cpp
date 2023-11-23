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
