#include "sampleqtablewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SampleQTableWidget w;
    w.show();
    return a.exec();
}
