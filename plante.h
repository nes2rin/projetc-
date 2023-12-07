#ifndef PLANTE_H
#define PLANTE_H

#include <QString>

class Plante
{
public:
    Plante(int id, const QString& name, const QString& characteristics, int quantity);

    // Getters
    int getId() const;
    QString getName() const;
    QString getCharacteristics() const;
    int getQuantity() const;

    // Setters
    void setId(int id);
    void setName(const QString& name);
    void setCharacteristics(const QString& characteristics);
    void setQuantity(int quantity);

    // Database operations
    bool insert();
    bool update();
    bool remove();

private:
    int m_id;
    QString m_name;
    QString m_characteristics;
    int m_quantity;
};

#endif // PLANTE_H
