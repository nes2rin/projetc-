#include <QtNetwork>
#include "sms.h"
#include <QSslSocket>


QString twilio_phone_number = "+16626333608";


sms::sms(){

}
void sms::sendSMS(const QString &to, const QString &message) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QUrl url("https://api.twilio.com/2010-04-01/Accounts/ACe2d67e3af9df79b17bac9c33edf35c3b/Messages.json");
    QNetworkRequest request(url);


    QString credentials = "ACe2d67e3af9df79b17bac9c33edf35c3b:2cf035a4a5f36eae65db5896c43442b5";
    QByteArray base64Credentials = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + base64Credentials);


    QByteArray postData;
    postData.append("From="+twilio_phone_number);
    postData.append("&To=" + to);
    postData.append("&Body=" + message);


    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Make the request
    QNetworkReply *reply = manager->post(request, postData);


    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "SMS sent successfully";
        } else {
            qDebug() << "Failed to send SMS:" << reply->errorString();
        }


        reply->deleteLater();
        manager->deleteLater();
    });
}
