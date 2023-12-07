#include "employemodel.h"
#include "login.h"
#include <QDebug>
void employemodel::refresh()
{

    setQuery("SELECT * FROM employe ");

}

void employemodel::refresh1()
{
    setQuery(QString("SELECT * FROM employe WHERE id = %1").arg(11));
}

