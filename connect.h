#ifndef CONNECT_H
#define CONNECT_H

#include <QtSql>

class Connect
{
public:
    Connect();
    ~Connect();

    QVector<QPair<QString, int>> getData();

private:
    QSqlDatabase db;
};

#endif // CONNECT_H
