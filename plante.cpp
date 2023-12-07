// plante.cpp
#include "plante.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>


Plante::Plante(int id, const QString &name, const QString &characteristics, int quantity)
    : m_id(id), m_name(name), m_characteristics(characteristics), m_quantity(quantity)
{
}

int Plante::getId() const
{
    return m_id;
}

QString Plante::getName() const
{
    return m_name;
}

QString Plante::getCharacteristics() const
{
    return m_characteristics;
}

int Plante::getQuantity() const
{
    return m_quantity;
}

void Plante::setId(int id)
{
    m_id = id;
}

void Plante::setName(const QString &name)
{
    m_name = name;
}

void Plante::setCharacteristics(const QString &characteristics)
{
    m_characteristics = characteristics;
}

void Plante::setQuantity(int quantity)
{
    m_quantity = quantity;
}

bool Plante::insert()
{
    QSqlQuery query;
    query.prepare("INSERT INTO PLANTE (id, name, characteristics, quantity) "
                  "VALUES (:id, :name, :characteristics, :quantity)");
    query.bindValue(":id", m_id);
    query.bindValue(":name", m_name);
    query.bindValue(":characteristics", m_characteristics);
    query.bindValue(":quantity", m_quantity);

    if (!query.exec())
    {
        qDebug() << "Error executing insert query:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Plante::update()
{
    QSqlQuery query;
    query.prepare("UPDATE PLANTE SET name = :name, characteristics = :characteristics, "
                  "quantity = :quantity WHERE id = :id");
    query.bindValue(":id", m_id);
    query.bindValue(":name", m_name);
    query.bindValue(":characteristics", m_characteristics);
    query.bindValue(":quantity", m_quantity);

    if (!query.exec())
    {
        qDebug() << "Error executing update query:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Plante::remove()
{
    QSqlQuery query;
    query.prepare("DELETE FROM \"PLANTE\" WHERE \"ID\" = :id");
    query.bindValue(":id", m_id);

    if (!query.exec())
    {
        qDebug() << "Error executing remove query:" << query.lastError().text();
        return false;
    }

    // Check if any rows were affected by the delete operation
    if (query.numRowsAffected() == 0)
    {
        qDebug() << "No rows were deleted for ID:" << m_id;
        return false;
    }

    return true;
}
