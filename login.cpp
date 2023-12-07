#include "login.h"
#include "ui_login.h"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}
int login ::recherche(QString email,QString mdp )
{
    QSqlQuery query;
    query.prepare("select * from employe where email=:email");
    query.bindValue(":email",email);
    if(query.exec()){
        query.next();
        if(query.value(4)== mdp){
            employee.setId(query.value(0).toInt());
            employee.setNom(query.value(1).toString());
            employee.setPrenom(query.value(2).toString());
            employee.setEmail(query.value(3).toString());
            employee.setMdp(query.value(4).toString());
            employee.setPoste(query.value(5).toString());
            employee.setAdresse(query.value(6).toString());
            employee.setSalaire(query.value(7).toDouble());
            employee.setNum(query.value(8).toInt());
            test = 1;
        }else {
             employee.setId(0);
             test = 0;
        }
    }else {
        employee.setId(0);
        test = 0;
    }
    return test;
}
void login::on_log_clicked()
{
    QString email = ui->email_2->text();
    QString mdp = ui->mdp_2->text();
    if(login::recherche(email,mdp) == 1) {
        QMessageBox::information(this, "Login", "Username and password is correct");
        if(employee.getPoste() == "Admin"){
        MainWindow *myLog = new MainWindow();
        //Close the welcome class
        this->close();
        //open the Login class
        myLog->show();
        }
        else{
        rh *myLog = new rh();
        //Close the welcome class
        this->close();
        //open the Login class
        myLog->show();
        }

    }
    else {
        QMessageBox::warning(this,"Login", "username and password is not correct");
    }
}


