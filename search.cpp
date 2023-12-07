#include "search.h"
#include <QSqlQuery>

Search::Search(QObject *parent)
    : QSqlQueryModel(parent)
{
}

void Search::setSearchTerm(const QString &searchTerm)
{
    m_searchTerm = searchTerm;
    setQuery(QString("SELECT * FROM your_table_name WHERE your_column_name LIKE '%%1%'").arg(m_searchTerm));
}

QVariant Search::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);

    if (role == Qt::DisplayRole && index.column() == 0) {
        value = QString("%1. %2").arg(index.row() + 1).arg(value.toString());
    }

    return value;
}
