#include "mainwindow.h"
#include "task.h"
#include <QTableWidget>

#include <QApplication>
#include <QLabel>
#include <QBitmap>
#include <QGridLayout>
#include <QBitmap>
#include <QListWidget>
#include <QPainter>
#include <QSize>
#include <QPixmap>
#include <QVector>
#include <QFile>
#include <QPen>
#include <QDir>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QListWidget *newWidget = new QListWidget;

    QDir dir("task.h");
    QString s;

    s = dir.relativeFilePath("C:/Users/Affan/Documents/test/data.txt");

    w.show();
    return a.exec();
}
