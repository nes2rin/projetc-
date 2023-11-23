#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->materielBtn->setStyleSheet("qproperty-icon:url(:/icons-green/icons-green/home.svg); color: #4A7C59; border-top-left-radius: 15px; border-bottom-left-radius: 15px; background: #FAF3DD;");
    ui->mainContentSTackWidget->setCurrentIndex(0);
    ui->etatComboBox->addItem("Fonctionnelle");ui->etatComboBox->addItem("Non Fonctionnelle");
    ui->etatComboBox_2->addItem("Fonctionnelle");ui->etatComboBox_2->addItem("Non Fonctionnelle");
    ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
    ui->alertAjout_5->hide();
    ui->idMatLE->hide();
    ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
    ui->alertAjout_10->hide();
    ui->triEmployesComboBox->addItem("par défaut");
    ui->triEmployesComboBox->addItem("Age");
    ui->triEmployesComboBox->addItem("Capacité");
    ui->triEmployesComboBox->addItem("Prix");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajoutMaterielPageBtn_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(0);
    ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
    ui->alertAjout_5->hide();
    ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
    ui->alertAjout_10->hide();
}

void MainWindow::on_afficherMaterielPageBtn_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(1);
    ui->materielTableView->setModel(m.afficherMateriel());
    statMateriel();
    ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
    ui->alertAjout_5->hide();
    ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
    ui->alertAjout_10->hide();
}

void MainWindow::on_materielModifBtn_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(2);
}

void MainWindow::on_ajoutMaterielBtn_clicked()
{
    if(ui->prixLineEdit->text() =="" || ui->nomLE->text() == "" || ui->ageLE->text() =="" || ui->prixLineEdit->text() == "" || ui->capLineEdit->text() =="")
    {
        ui->alertAjout->show();ui->alertAjout_2->show();ui->alertAjout_3->show();ui->alertAjout_4->show();
        ui->alertAjout_5->show();
    }
    else{
        QString mat = ui->matLineEdit->text();
        QString nom = ui->nomLE->text();
        QString etat = ui->etatComboBox->currentText();
        int age = ui->ageLE->text().toInt();
        float prix = ui->prixLineEdit->text().toFloat();
        float cap = ui->capLineEdit->text().toFloat();
        materiel mtrl(0,age,nom,mat,etat,cap,prix);
        if(mtrl.ajouterMateriel())
        {
            ui->materielTableView->setModel(m.afficherMateriel());
            ui->alertAjout->hide();ui->alertAjout_2->hide();ui->alertAjout_3->hide();ui->alertAjout_4->hide();
            ui->alertAjout_5->hide();
            ui->mainContentSTackWidget->setCurrentIndex(1);
            statMateriel();
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                                  QObject::tr("Echec d'opération. \n"
                                              "Click me to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_materielTableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString qrCodeData;
    QModelIndex sibling = index.sibling(row,0);
    QString id = ui->materielTableView->model()->data(sibling).toString();

                QSqlQuery qry;
                qry.prepare("SELECT * FROM materiel WHERE id=:id" );
                qry.bindValue(":id",id);
                if(qry.exec())
                {
                    while(qry.next())
                    {
                        ui->idMatLE->setText(qry.value(0).toString());
                        ui->matLineEdit_2->setText(qry.value(1).toString());
                        ui->nomLE_2->setText(qry.value(2).toString());
                        ui->prixLineEdit_2->setText(qry.value(6).toString());
                        ui->etatComboBox_2->setCurrentText(qry.value(3).toString());
                        ui->ageLE_2->setText(qry.value(4).toString());
                        ui->capLineEdit_2->setText(qry.value(5).toString());
                         qrCodeData ="ID : "+qry.value(0).toString()+" | Matricul : "+qry.value(1).toString()+" | Nom : "+qry.value(2).toString()+" | Prix : "+qry.value(6).toString()+" | Etat : "+qry.value(3).toString()+" | Capacité : "+qry.value(5).toString();
                    }
                }
                //QR CODE
                using namespace qrcodegen;
                // Create the QR Code object
                  QrCode qr = QrCode::encodeText( qrCodeData.toUtf8().data(), QrCode::Ecc::MEDIUM );
                  qint32 sz = qr.getSize();
                  QImage im(sz,sz, QImage::Format_RGB32);
                  QRgb black = qRgb(  0,  0,  0);
                  QRgb white = qRgb(255,255,255);
               for (int y = 0; y < sz; y++)
                    for (int x = 0; x < sz; x++)
                         im.setPixel(x,y,qr.getModule(x, y) ? black : white );
               ui->qrCodeLabel->setPixmap( QPixmap::fromImage(im.scaled(150,150,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

void MainWindow::on_ajoutMaterielBtn_2_clicked()
{
    if(ui->prixLineEdit_2->text() =="" || ui->nomLE_2->text() == "" || ui->ageLE_2->text() =="" || ui->prixLineEdit_2->text() == "" || ui->capLineEdit_2->text() =="")
    {
        ui->alertAjout_6->show();ui->alertAjout_7->show();ui->alertAjout_8->show();ui->alertAjout_9->show();
        ui->alertAjout_10->show();
    }
    else{
        int id = ui->idMatLE->text().toInt();
        QString mat = ui->matLineEdit_2->text();
        QString nom = ui->nomLE_2->text();
        QString etat = ui->etatComboBox_2->currentText();
        int age = ui->ageLE_2->text().toInt();
        float prix = ui->prixLineEdit_2->text().toFloat();
        float cap = ui->capLineEdit_2->text().toFloat();
        materiel mtrl(id,age,nom,mat,etat,cap,prix);
        if(mtrl.modifierMateriel())
        {
            ui->materielTableView->setModel(m.afficherMateriel());
            ui->alertAjout_6->hide();ui->alertAjout_7->hide();ui->alertAjout_8->hide();ui->alertAjout_9->hide();
            ui->alertAjout_10->hide();
            ui->mainContentSTackWidget->setCurrentIndex(1);
            statMateriel();
            if(etat == "Non Fonctionnelle")
                sendMail(QString::number(id),nom);
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                                  QObject::tr("Echec d'opération. \n"
                                              "Click me to exit."), QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_materielSuppBtn_clicked()
{
    QModelIndex indexItem = ui->materielTableView->currentIndex();
    int row = indexItem.row();
    QModelIndex sibling = indexItem.sibling(row,0);
    int id = ui->materielTableView->model()->data(sibling).toInt();
    if(m.supprimerMateriel(id))
    {
       ui->materielTableView->setModel(m.afficherMateriel());
       statMateriel();
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("ERREUR!"),
                              QObject::tr("Echec d'opération. \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_employesRechBar_textChanged(const QString &arg1)
{
  ui->materielTableView->setModel(m.rechercherMateriel(arg1));
}

void MainWindow::on_triEmployesComboBox_currentIndexChanged(const QString &arg1)
{
    ui->materielTableView->setModel(m.triMateriel(arg1));
}
void MainWindow::statMateriel()
{
    QLayout* layoutTest = ui->materielStatContainer->layout();

    if (layoutTest) {
        delete layoutTest;
    }
    QChart *chart = new QChart();
    chart->setTitle("% Etat");
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    QVector<int> stat = m.statMateriel();
    int nbrF = stat.front(),nbrNF = stat.back();
    int somme = nbrF + nbrNF;
    float prcF = (float(nbrF) / somme)*100, prcNF = (float(nbrNF) / somme)*100;
    QPieSeries * seriesQuantity = new QPieSeries();
    seriesQuantity->append("Fonctionnelle %"+QString::number(prcF), stat.front());
    seriesQuantity->append("Non Fonctionnelle %"+QString::number(prcNF), stat.back());
    chart->addSeries(seriesQuantity);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->materielStatContainer->setLayout(layout);
}

void MainWindow::on_materielModifBtn_2_clicked()
{
    QString strStream;
       QTextStream out(&strStream);
       QDate currentDate = QDate::currentDate();
       QString date = currentDate.toString("dd-MM-yyyy");


       const int rowCount = ui->materielTableView->model()->rowCount();
       const int columnCount = ui->materielTableView->model()->columnCount();

       out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           <<  QString("<title>%1</title>\n").arg("col1")
           <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<h3 style='position: absolute; top: 0; right: 0; margin: 0; padding: 10px; text-align: right; font-size: 24px; color: #333;'> Tunis "+date+"</h3>"
           "<h1 style='text-align: center;'>Liste des materiels</h1>\n"
           "<br>\n"
           "<br>\n"
               "<div align='center'>"
           "<table border=1>\n";

       // headers
       out << "<thead><tr bgcolor=#f0f0f0>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->materielTableView->isColumnHidden(column))
               out << QString("<th>%2</th>").arg(ui->materielTableView->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++) {
           out << "<tr>";
           for (int column = 0; column < columnCount; column++) {
               if (!ui->materielTableView->isColumnHidden(column)) {
                   QString data = ui->materielTableView->model()->data(ui->materielTableView->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%2</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table>\n"
               "</div>"
           "</body>\n"
           "</html>\n";

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);

       QPrinter printer;

           document->print(&printer);


       delete document;
}

void MainWindow::sendMail(QString id,QString nom)
{
    Smtp* smtp = new Smtp("mohamed.ouerfelli@esprit.tn","testtest123A", "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailsent(QString)));
        smtp->sendMail("mohamed.ouerfelli@esprit.tn", "mohamedouerfelli3@gmail.com" , "ALERTE MATERIEL","Matériel Non Fonctionnelle ID : '"+id+"', Nom : '"+nom+"' ,Veuillez vérifier son état.");
}
void   MainWindow::mailsent(QString status)
{

    if(status == "Message sent")
    {
        QMessageBox::information(nullptr,QObject::tr("MAIL Sent!"),
                              QObject::tr("Done ! \n"
                                          "Click me to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_sendChatBtn_clicked()
{
    QString text,space="";
    float rassemblance=0;
    int tr=0;
    QString msg=ui->inputChatbot->text();
    ui->chatBot->appendPlainText(space);
    ui->chatBot->appendPlainText(msg);
    QSqlQuery qry,query;
     if(msg[0]!="#")
     {
        qry.prepare("select * from chatbot" );
        qry.exec();
        while(qry.next() && tr==0)
        {
            QString quest = qry.value(0).toString();
                int eq = 0,dif = 0;
                for(int i=0 ; i < msg.size(); i++)
                {
                       if(quest[i] == msg[i])
                           eq++;
                       else
                           dif++;
                }
                rassemblance = (eq / static_cast<float>(msg.size()))*100;
                if(rassemblance > 80)
                {
                    ui->chatBot->appendPlainText( "\n"+qry.value(1).toString());
                    tr=1;
                }
         }
        if(tr == 0)
        {

                ui->chatBot->appendPlainText( "Voulez vous ajouter un nouveau mot ? Écrivez votre réponse avec un # au début.");
                ui->labelCache->setText(msg);

        }
     }
     else if (msg[0]=="#"){
         QString msg1=msg.mid(1,msg.length()-1);
         query.prepare("insert into chatbot (quest,rep)""values(:quest,:rep)");
         query.bindValue(":quest", ui->labelCache->text());
         query.bindValue(":rep", msg1);
         query.exec();
         ui->chatBot->appendPlainText( "\n Merci ! Pour cette information");

     }
}

void MainWindow::on_afficherMaterielPageBtn_2_clicked()
{
    ui->mainContentSTackWidget->setCurrentIndex(2);
}
