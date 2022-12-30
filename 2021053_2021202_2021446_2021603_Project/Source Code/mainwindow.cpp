#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QBitmap>
#include <QGridLayout>
#include <QPushButton>
#include <QSize>
#include <QColor>
#include <QByteArray>
#include <QPixmap>
#include <QBoxLayout>
#include <QPainter>
#include <QTableWidget>
#include "mainwindow.h"
#include <QMouseEvent>
#include <QPair>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("DSA Project");

    b.get_data();


    b.correlationMatrix();
    b.update_corelation();
    b.weighted_graph(removeEdges);
    b.clustering();


    bitmapArray.resize(b.row);
    correlationMatrix.resize(b.row);

    for(int i = 0; i < b.row; i++)
    {
        bitmapArray[i].resize(b.row);
        correlationMatrix[i].resize(b.row);
        for(int  j = 0; j < b.row; j++)
        {
            bitmapArray[i][j] = b.bitmap[i][j];
            correlationMatrix[i][j] = b.corelation_matrix[i][j];
        }
    }

    clusterArray.resize(b.cluster_array.size());
    coordinates.resize(b.cluster_array.size());
    for(int i = 0; i < b.cluster_array.size(); i++)
    {
        clusterArray[i].resize(b.cluster_array[i].size());
        coordinates[i].resize(b.cluster_array[i].size());
        for(int j = 0; j < b.cluster_array[i].size(); j++)
        {
            maxSize++;
            clusterArray[i][j] = b.cluster_array[i][j];
        }
    }


    QHBoxLayout *mainMenuButtons = new QHBoxLayout;
    QHBoxLayout *bitmapBox = new QHBoxLayout(this);
    QLabel *textHolder = new QLabel(this);
    mainMenu = new QGridLayout;

    projectWelcome = new QLabel(this);
    graphValues = new QLineEdit(this);
    btn1 = new QPushButton(this);
    btn2 = new QPushButton(this);
    btn3 = new QPushButton(this);
    btn4 = new QPushButton(this);
    btn5 = new QPushButton(this);
    btn6 = new QPushButton(this);


    btn1->setText("Show Bitmap");
    btn2->setText("Show Correllation matrix");
    btn3->setText("Visualize Graph");
    btn4->setText("Permute Data Matrix");
    btn5->setText("Signature Recovery");
    btn6->setText("Remove Edges");

    projectWelcome->setText("Welcome to DSA Project");
    projectWelcome->move(0,500);


    mainMenuButtons->addWidget(btn1);
    mainMenuButtons->addWidget(btn2);

    mainMenu->addWidget(projectWelcome, 0, 2);
    mainMenu->addWidget(btn1, 1, 0);
    mainMenu->addWidget(btn2, 1, 2);
    mainMenu->addWidget(btn3,1,1);
    mainMenu->addWidget(btn4, 1,3);
    mainMenu->addWidget(btn5, 1,4);
    mainMenu->addWidget(graphValues, 2,0, 1, 4);
    mainMenu->addWidget(btn6, 2,4);




    this->centralWidget()->setLayout(mainMenu);

    connect(btn1, SIGNAL(clicked()), this, SLOT(on_pushButton_Draw_clicked()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(check()));
    connect(btn3, SIGNAL(clicked()), this, SLOT(toggleGraph()));
    connect(btn4, SIGNAL(clicked()), this, SLOT(permuteDataMatrix()));
    connect(btn5, SIGNAL(clicked()), this, SLOT(signatureTechnique()));
    connect(btn6, SIGNAL(clicked()), this, SLOT(removeValues()));

    b.update_correlation_for_green_shade();
for(int i = 0; i < bitmapArray.size(); i++)
{
    for(int j = 0;j < bitmapArray[i].size(); j++)
    {
        if(b.bitmap[i][j] != b.bitmap[j][i])
            std::cout << b.bitmap[i][j] << ' ';
    }
}

}

void MainWindow::removeValues()
{
    QString text = graphValues->text();
    removeEdges = text.toDouble();;

    b.weighted_graph(removeEdges);
    b.clustering();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::permuteDataMatrix()
{
    b.permute_data_matrix();
    b.correlationMatrix();
    b.update_corelation();

    b.weighted_graph(removeEdges);
    b.clustering();

    for(int i = 0; i < b.row; i++)
    {
        for(int  j = 0; j < b.row; j++)
        {
            bitmapArray[i][j] = b.bitmap[i][j];
            correlationMatrix[i][j] = b.corelation_matrix[i][j];
        }
    }

}

void MainWindow::signatureTechnique()
{
    b.signatureArrayFunction();
    b.rearrangeFunction();

    b.correlationMatrix();
    b.update_corelation();

    b.weighted_graph(removeEdges);
    b.clustering();

    for(int i = 0; i < b.row; i++)
    {
        for(int  j = 0; j < b.row; j++)
        {
            bitmapArray[i][j] = b.bitmap[i][j];
            correlationMatrix[i][j] = b.corelation_matrix[i][j];
        }
    }
}

void MainWindow::check2()
{

}
void MainWindow::paintEvent(QPaintEvent *event)
{

    if(m_flag)

    {
        projectWelcome->setText("");
        QPainter painter(this);
        QPen penPainter;
        penPainter.setColor(Qt::white);

        painter.setPen(penPainter);
        penPainter.setWidth(1*zoomFactor);


        for(int i = 0;i < b.bitmap.size(); i++)
        {
            for(int j = 0; j < b.bitmap[i].size(); j++)
            {
                if(b.bitmap[i][j] == 0)
                {
                    painter.drawPoint((330-50*zoomFactor)+(1*zoomFactor*j), (230-50*zoomFactor)+(1*zoomFactor*i));
                }

            }
        }

        penPainter.setColor(Qt::black);
        penPainter.setWidth(1*zoomFactor);

    painter.setPen(penPainter);

        for(int i = 0;i < b.bitmap.size(); i++)
        {
            for(int j = 0; j < b.bitmap.size(); j++)
            {
                if(b.bitmap[i][j] == 1)
                {
                    painter.drawPoint((330-50*zoomFactor)+(1*zoomFactor*j), (230-50*zoomFactor)+(1*zoomFactor*i));
                }

            }
        }

        if(colorCodeFlag)
        {

            QColor colorCoding(0,255,0,255);
            b.update_correlation_for_green_shade();

        penPainter.setColor(colorCoding);
        penPainter.setWidth(1*zoomFactor);

        painter.setPen(penPainter);

        for(int i = 0;i< b.bitmap.size(); i++)
        {
            for(int j = 0; j < b.bitmap.size(); j++)
            {
                this->correlationMatrix[i][j] = b.corelation_matrix[i][j];
            }
        }



        for(int i = 0;i < b.bitmap.size(); i++)
        {
            for(int j = 0; j < b.bitmap.size(); j++)
            {
                int opacity = b.corelation_matrix[i][j];

                colorCoding.setRgb(0,255,0,opacity-50);
                penPainter.setColor(colorCoding);
                painter.setPen(penPainter);

                painter.drawPoint((330-50*zoomFactor)+(1*zoomFactor*j), (230-50*zoomFactor)+(1*zoomFactor*i));

            }
        }
        }
    }



    if(graphFlag)
    {
        projectWelcome->setText("");
        QPainter painter(this);
        QPen penPainter;
        QPen penPainter2;
        penPainter.setColor(Qt::black);
        penPainter2.setColor(Qt::black);

        coordinates.resize(b.cluster_array.size());
        for(int i = 0; i < b.cluster_array.size(); i++)
        {
            coordinates[i].resize(b.cluster_array[i].size());
        }

        penPainter.setWidth(7);
        penPainter2.setWidth(0.11);

        painter.setPen(penPainter);
        QColor edgeColor;

        for(int i = 0; i < b.cluster_array.size(); i++)
        {
            painter.setPen(penPainter);



            for(int j = 0; j < b.cluster_array[i].size(); j++)
            {
                int randomX = rand() % 700;
                int randomY = rand() % 500;
                QPair<int,int> randomCoordinate;
                randomCoordinate.first = randomX+50;
                randomCoordinate.second = randomY+50;

                painter.drawPoint(50+randomX,50+randomY);

                coordinates[i][j] = randomCoordinate;
            }
            int r = rand() %255;
            int g = rand() %255;
            int b = rand() %255;
            edgeColor.setRgb(r,g,b);
            for(int k = 1; k < coordinates[i].size()-1; k++)
            {

                penPainter2.setColor(edgeColor);
                painter.setPen(penPainter2);
                painter.drawLine(coordinates[i][0].first, coordinates[i][0].second, coordinates[i][k].first, coordinates[i][k].second);
            }
        }


    }
}

void MainWindow::on_pushButton_Draw_clicked()
{
    if(!m_flag && colorCodeFlag == false)
    {
        m_flag = true;
        btn1->setText("Display Color Coding");
    }
    else if(m_flag && colorCodeFlag == false)
    {
        colorCodeFlag = true;
        btn1->setText("Hide bitmap");

    }
    else if(m_flag && colorCodeFlag == true)
    {
        colorCodeFlag = false;
        m_flag = false;
        btn1->setText("Show Bitmap");

    }
    update();
}

void MainWindow::toggleGraph()
{
    graphFlag = !graphFlag;
    update();
}


void MainWindow::check()
{
    tableFlag = !tableFlag;
    correlationMatrixDisplay(correlationMatrix.size(), correlationMatrix[0].size());
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0)
    {
        zoomFactor++;
    }
        else if(event->angleDelta().y() < 0)
    {
        if(zoomFactor !=1)
            zoomFactor--;
    }
   update();
}

void MainWindow::correlationMatrixDisplay(int row, int col)
{
    if(!tableFlag)
    {
        table->hide();
        return;
    }

    else
    {
        b.correlationMatrix();



    QVBoxLayout *box = new QVBoxLayout(this);
    QLabel *lab = new QLabel("AAAAAAAAAAA");
    table = new QTableWidget(this);



    table->setRowCount(row);
    table->setColumnCount(col);



    table->setMaximumWidth(800);


    for(int i = 0; i < table->rowCount(); i++)
    {
        QTableWidgetItem *item;
        for(int j = 0; j < table->columnCount(); j++)
        {
            item = new QTableWidgetItem;
            item->setText(QString::number(b.corelation_matrix[i][j]));

            table->setItem(i,j,item);

        }
    }

    mainMenu->addWidget(table, 5, 0, 1, 5);
    }


}





