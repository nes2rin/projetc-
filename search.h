#ifndef SEARCH_H
#define SEARCH_H

#include <QSqlQueryModel>

class Search : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit Search(QObject *parent = nullptr);

    void setSearchTerm(const QString &searchTerm);

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QString m_searchTerm;
};

#endif // SEARCH_H
