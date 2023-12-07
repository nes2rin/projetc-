#include "pdf.h"
#include <QTextDocument>
#include <QTextCursor>
#include <QTextBlock>
#include <QtPrintSupport/QPrinter>  // Include QPrinter here
#include <QTextStream>
#include <QFile>

bool PDF::convertToPDF(const QString &data) {
    QTextDocument doc;
    QTextCursor cursor(&doc);
    cursor.insertText(data);

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("output.pdf");
    printer.setOutputFileName("C:/Users/Eya/Documents/pdf/output.pdf");
    doc.print(&printer);

    return true;
}
