#include "chart.h"


Chart::Chart(QWidget *parent) : QWidget(parent)
{
    customPlot = new QCustomPlot(this);
    customPlot->setMinimumSize(400, 400);
}

Chart::~Chart()
{
    delete customPlot;
}

void Chart::updateChart(const QVector<QPair<QString, int>>& data)
{
    // Clear existing data
    customPlot->clearGraphs();

    // Create a QCPBars object
    QCPBars *bars = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    // Set the data to the bars
    QVector<double> ticks;
    QVector<double> values;
    for (int i = 0; i < data.size(); ++i) {
        ticks << i + 1;
        values << data[i].second;
    }

    bars->setData(ticks, values);

    // Set up the appearance of the chart (similar to previous code)
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    customPlot->xAxis->setTicker(textTicker);

    QVector<QString> labels;
    for (int i = 0; i < data.size(); ++i) {
        labels << data[i].first;
    }

    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTickLabelRotation(60);

    customPlot->rescaleAxes();
    customPlot->replot();
}

