#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QSqlQuery>
#include<QSqlQueryModel>

class employe
{
private :
    int id,num;
    double salaire;
    QString nom,prenom,email,adresse,poste,mdp;

public:


    employe();
    employe(int id,QString nom,QString prenom,QString email,QString mdp,QString adresse,QString poste,double salaire,int num)
    {
        this->id=id;
        this->nom=nom;
        this->prenom=prenom;
        this->email=email;
        this->mdp=mdp;
        this->adresse=adresse;
        this->poste=poste;
        this->salaire=salaire;
        this->num=num;

    }
    employe(QString nom,QString prenom,QString email,QString mdp,QString adresse,QString poste,double salaire,int num)
    {
        this->nom=nom;
        this->prenom=prenom;
        this->email=email;
        this->mdp=mdp;
        this->adresse=adresse;
        this->poste=poste;
        this->salaire=salaire;
        this->num=num;

    }
    employe (int id)
    {
        this->id=id;
    }
    void setNom(QString nom){
        this->nom = nom;
    }
    void setPrenom(QString prenom){
        this->prenom = prenom;
    }
    void setEmail(QString email){
        this->email = email;
    }
    void setMdp(QString mdp){
        this->mdp = mdp;
    }
    void setPoste(QString poste){
        this->poste = poste;
    }
    void setAdresse(QString adresse){
        this->adresse = adresse;
    }
    void setSalaire(double salaire){
        this->salaire = salaire;
    }
    void setNum(int num){
        this->num = num;
    }
    void setId(int id){
        this->id = id;
    }
    int getId(){
        return this->id;
    }
    QString getNom(){
        return this->nom;
    }
    QString getPrenom(){
        return this->prenom;
    }
    QString getEmail(){
        return this->email;
    }
    QString getMdp(){
        return this->mdp;
    }
    QString getPoste(){
        return this->poste;
    }
    QString getAdresse(){
        return this->adresse;
    }
    double getSalaire(){
        return this->salaire;
    }
    int getNum(){
        return this->num;
    }

    bool ajouter();
   QSqlQueryModel *afficher();
   QSqlQueryModel*afficher1(int id);
    bool modifier ();
    bool supprimer ();
    QSqlQueryModel* recherche_employe(QString search);
    QSqlQueryModel* triID();
    int statistiquesemploye(QString occ);
    bool incrementNbEmp();



};

#endif // EMPLOYE_H
