#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H
#include <QMainWindow>
#include <QCalendarWidget>
#include <QPushButton>
#include <QSqlDatabase>

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow2(QWidget *parent = nullptr);
    QList<QString> loadEventsForDate(const QDate &date);

private slots:
    void onDateSelected(const QDate &date);
    void onAddEventClicked();
    void onEditEventClicked();
    void onDeleteEventClicked();

private:
    QCalendarWidget *calendarWidget;
    QPushButton *addEventButton;
    QPushButton *editEventButton;
    QPushButton *deleteEventButton;
    int eventId;

signals:
    void eventAdded(const QString &eventTitle);
    void eventEdited(const QString &eventTitle);
    void eventDeleted();

    // Add any other necessary member variables and functions
};

#endif // MAINWINDOW2_H
