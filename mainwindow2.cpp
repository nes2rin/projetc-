#include "mainwindow2.h"
#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include<QSqlQuery>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QSqlError>
#include <QDate>



MainWindow2::MainWindow2(QWidget *parent)
    : QMainWindow(parent)
{


    calendarWidget = new QCalendarWidget(this);
    addEventButton = new QPushButton("Add Event", this);
    editEventButton = new QPushButton("Edit Event", this);
    deleteEventButton = new QPushButton("Delete Event", this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(calendarWidget);
    mainLayout->addWidget(addEventButton);
    mainLayout->addWidget(editEventButton);
    mainLayout->addWidget(deleteEventButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);



    connect(calendarWidget, &QCalendarWidget::clicked, this, &MainWindow2::onDateSelected);
    connect(addEventButton, &QPushButton::clicked, this, &MainWindow2::onAddEventClicked);
    connect(editEventButton, &QPushButton::clicked, this, &MainWindow2::onEditEventClicked);
    connect(deleteEventButton, &QPushButton::clicked, this, &MainWindow2::onDeleteEventClicked);

    // Add layout, set up the main window, etc.
}

QList<QString> MainWindow2::loadEventsForDate(const QDate &date)
{
    // Implement the logic to load events for the selected date
    QList<QString> events;

    // Example: add sample events
    events << "Event 1: " << date.toString("dd/MM/yyyy") << " at 10:00" << "AM" << "Location: Room 1" << "\n";
    events << "Event 2: " << date.toString("dd/MM/yyyy") << " at 12:00" << "PM" << "Location: Room 2" << "\n";

    return events;
}

void MainWindow2::onDateSelected(const QDate &date)
{
    // Handle date selection, load events for the selected date, etc.
    qDebug() << "Selected date:" << date.toString();

    // Example: load events for the selected date
    QList<QString> events = loadEventsForDate(date);

    // Example: display the events in a message box
    QMessageBox::information(this, "Events for " + date.toString(), events.join("\n"));
}

void MainWindow2::onAddEventClicked()
{
    // Create a dialog to add a new event
    QDialog dialog;
    QVBoxLayout layout(&dialog);

    QLabel titleLabel("Event Title:", &dialog);
    QLineEdit titleEdit(&dialog);

    QLabel datetimeLabel("Event Datetime:", &dialog);
    QDateTimeEdit datetimeEdit(&dialog);
    datetimeEdit.setDateTime(QDateTime::currentDateTime());

    QLabel notesLabel("Event Notes:", &dialog);
    QTextEdit notesEdit(&dialog);

    QLabel plantIdLabel("Plant ID:", &dialog);
    QSpinBox plantIdSpin(&dialog);

    QPushButton addButton("Add Event", &dialog);

    layout.addWidget(&titleLabel);
    layout.addWidget(&titleEdit);

    layout.addWidget(&datetimeLabel);
    layout.addWidget(&datetimeEdit);

    layout.addWidget(&notesLabel);
    layout.addWidget(&notesEdit);

    layout.addWidget(&plantIdLabel);
    layout.addWidget(&plantIdSpin);

    layout.addWidget(&addButton);

    QObject::connect(&addButton, &QPushButton::clicked, [&](){
        QString eventTitle = titleEdit.text();
        QDateTime eventDatetime = datetimeEdit.dateTime();
        QString eventNotes = notesEdit.toPlainText();
        int plantId = plantIdSpin.value();

        // Add your logic to insert a new event into the "events" table
        QSqlQuery query;
        query.prepare("INSERT INTO events (EVENTNAME, EVENTDATETIME, EVENTNOTES, PLANTID) "
                      "VALUES (:eventName, :eventDatetime, :eventNotes, :plantId)");
        query.bindValue(":eventName", eventTitle);
        query.bindValue(":eventDatetime", eventDatetime);
        query.bindValue(":eventNotes", eventNotes);
        query.bindValue(":plantId", plantId);

        if (query.exec()) {
            emit eventAdded(eventTitle);
            dialog.close();
        } else {
            QMessageBox::critical(this, "Error", "Failed to add event: " + query.lastError().text());
        }
    });

    dialog.exec();
}

void MainWindow2::onEditEventClicked()
{
    // Create a dialog to edit an existing event



    QDialog dialog;
    QVBoxLayout layout(&dialog);

    QLabel eventIdLabel("Event ID:", &dialog);
    QSpinBox eventIdSpin(&dialog);

    QLabel titleLabel("Event Title:", &dialog);
    QLineEdit titleEdit(&dialog);

    QLabel datetimeLabel("Event Datetime:", &dialog);
    QDateTimeEdit datetimeEdit(&dialog);

    QLabel notesLabel("Event Notes:", &dialog);
    QTextEdit notesEdit(&dialog);

    QLabel plantIdLabel("Plant ID:", &dialog);
    QSpinBox plantIdSpin(&dialog);

    QPushButton editButton("Edit Event", &dialog);


    layout.addWidget(&eventIdLabel);
    layout.addWidget(&eventIdSpin);

    layout.addWidget(&titleLabel);
    layout.addWidget(&titleEdit);

    layout.addWidget(&datetimeLabel);
    layout.addWidget(&datetimeEdit);

    layout.addWidget(&notesLabel);
    layout.addWidget(&notesEdit);

    layout.addWidget(&plantIdLabel);
    layout.addWidget(&plantIdSpin);

    layout.addWidget(&editButton);

    QObject::connect(&editButton, &QPushButton::clicked, [&](){
        int eventId =eventIdSpin.value();
        QString eventTitle = titleEdit.text();
        QDateTime eventDatetime = datetimeEdit.dateTime();
        QString eventNotes = notesEdit.toPlainText();
        int plantId = plantIdSpin.value();

        // Add your logic to update an existing event in the "events" table
        QSqlQuery query;
        query.prepare("UPDATE events SET EVENTNAME = :eventName, "
                      "EVENTDATETIME = :eventDatetime, "
                      "EVENTNOTES = :eventNotes, "
                      "PLANTID = :plantId WHERE EVENTID = :eventId");
        query.bindValue(":eventName", eventTitle);
        query.bindValue(":eventDatetime", eventDatetime);
        query.bindValue(":eventNotes", eventNotes);
        query.bindValue(":plantId", plantId);
        // Assume you have an event ID for the event you want to edit
        query.bindValue(":eventId", eventId);//arj3 hnee

        if (query.exec()) {
            emit eventEdited(eventTitle);
            dialog.close();
        } else {
            QMessageBox::critical(this, "Error", "Failed to edit event: " + query.lastError().text());
        }
    });

    dialog.exec();
}
void MainWindow2::onDeleteEventClicked()
{
    // Confirm event deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Event", "Are you sure you want to delete this event?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Create a dialog to input the event ID for deletion
        QDialog dialog;
        QVBoxLayout layout(&dialog);

        QLabel eventIdLabel("Event ID:", &dialog);
        QLineEdit eventIdLineEdit(&dialog);

        QPushButton deleteButton("Delete Event", &dialog);

        layout.addWidget(&eventIdLabel);
        layout.addWidget(&eventIdLineEdit);
        layout.addWidget(&deleteButton);

        QObject::connect(&deleteButton, &QPushButton::clicked, [&](){
            // Get the eventId from the QLineEdit
            QString eventIdString = eventIdLineEdit.text();
            bool conversionOk;
            int eventId = eventIdString.toInt(&conversionOk);

            if (!conversionOk) {
                QMessageBox::critical(this, "Error", "Invalid Event ID");
                return;
            }

            // Add your logic to delete an existing event from the "events" table
            QSqlQuery query;
            query.prepare("DELETE FROM events WHERE EVENTID = :eventId");
            query.bindValue(":eventId", eventId);

            if (query.exec()) {
                emit eventDeleted();
                dialog.close();
            } else {
                QMessageBox::critical(this, "Error", "Failed to delete event: " + query.lastError().text());
            }
        });

        dialog.exec();
    }
}


