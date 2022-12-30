#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "task.h"
#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <qvector.h>
#include <QGridLayout>
#include <QTableWidget>
#include <QVector2D>
#include <QLabel>
#include <QPair>
#include <QPushButton>
#include <QWheelEvent>
#include <QLineEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget *aa = new QWidget;
    bool m_flag = false;
    int zoomFactor = 1;
    bool tableFlag = false;
    bool graphFlag = false;
    bool colorCodeFlag = false;
    double removeEdges = 0.2;
    QVector<QVector<int>> bitmapArray;
    QVector<QVector<int>> clusterArray;
    QVector<QVector<double>> correlationMatrix;
    QVector<QVector<QPair<int,int>>> coordinates;
    QLabel *projectWelcome;
    QLineEdit *graphValues;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    void correlationMatrixDisplay(int row, int col);
    QGridLayout *mainMenu;
    QTableWidget *table;
    int maxSize = 0;
    void drawClusters();
    data_clustering b;



    virtual void paintEvent(QPaintEvent *event);
    virtual void wheelEvent(QWheelEvent * event);

public slots:
    void on_pushButton_Draw_clicked();
    void check();
    void check2();
    void toggleGraph();
    void permuteDataMatrix();
    void signatureTechnique();
    void removeValues();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
