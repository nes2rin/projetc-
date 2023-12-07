#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QVector>
#include <QPair>
#include "qcustomplot.h"
class Chart : public QWidget
{
    Q_OBJECT
public:
    Chart(QWidget *parent = nullptr);
    ~Chart();

    void updateChart(const QVector<QPair<QString, int>>& data);

private:
    QCustomPlot *customPlot;
};

#endif // CHART_H
