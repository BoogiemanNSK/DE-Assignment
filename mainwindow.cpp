#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maingraph.h"
#include "errorgraph.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /// Setting Initial Values from Task

    ui->setupUi(this);
    ui->initX->setText(QString::number(1));
    ui->initY->setText(QString::number(0.5));
    ui->maxX->setText(QString::number(5));
    ui->minY->setText(QString::number(-2));
    ui->maxY->setText(QString::number(2));
    ui->pointsNum->setText(QString::number(100));

    connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (ButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ButtonClicked()
{
    /// Reading Input

    double x0 = ui->initX->toPlainText().toDouble();
    double y0 = ui->initY->toPlainText().toDouble();
    double X = ui->maxX->toPlainText().toDouble();
    int N = ui->pointsNum->toPlainText().toInt();

    double minY = ui->minY->toPlainText().toDouble();
    double maxY = ui->maxY->toPlainText().toDouble();

    MainGraph *MG = new MainGraph(x0, y0, X, N);
    ErrorGraph *EG = new ErrorGraph(MG);


    /// Main Graphs Plotting

    ui->graph->clearGraphs();

    // Analytical Solution Plot
    ui->graph->addGraph();
    ui->graph->graph(0)->setData(MG->x, MG->y);
    ui->graph->graph(0)->setName("Original Equation");
    ui->graph->graph(0)->setPen(QColor(40, 40, 40, 255));
    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // Euler Method Plot
    ui->graph->addGraph();
    ui->graph->graph(1)->setData(MG->x, MG->y_e);
    ui->graph->graph(1)->setName("Euler Method");
    ui->graph->graph(1)->setPen(QColor(0, 0, 255, 255));
    ui->graph->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // Improved Euler Method Plot
    ui->graph->addGraph();
    ui->graph->graph(2)->setData(MG->x, MG->y_ie);
    ui->graph->graph(2)->setName("Improved Euler Method");
    ui->graph->graph(2)->setPen(QColor(255, 0, 0, 255));
    ui->graph->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // Runge-Kutta Method Plot
    ui->graph->addGraph();
    ui->graph->graph(3)->setData(MG->x, MG->y_rk);
    ui->graph->graph(3)->setName("Runge-Kutta Method");
    ui->graph->graph(3)->setPen(QColor(0, 255, 50, 255));
    ui->graph->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // Asymptotes Plot (2 vertical lines)
    ui->graph->addGraph();
    ui->graph->graph(4)->setData(MG->x_a, MG->y_a);
    ui->graph->graph(4)->setName("Asymptotes");
    ui->graph->graph(4)->setPen(QColor(20, 20, 20, 128));
    ui->graph->graph(4)->setPen(Qt::DashLine);

    // Axis Settings
    ui->graph->xAxis->setLabel("X");
    ui->graph->yAxis->setLabel("Y");
    ui->graph->xAxis->setRange(x0, X);
    ui->graph->yAxis->setRange(minY, maxY);

    // Legend Settings
    ui->graph->legend->setVisible(true);
    ui->graph->legend->setBrush(QBrush(QColor(255,255,255,150)));
    ui->graph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignTop);

    ui->graph->replot();


    /// Error Graphs Plotting

    ui->error_graph->clearGraphs();

    // Euler Error Plot
    ui->error_graph->addGraph();
    ui->error_graph->graph(0)->setData(MG->x, EG->e_e);
    ui->error_graph->graph(0)->setName("Euler Error");
    ui->error_graph->graph(0)->setPen(QColor(0, 0, 255, 255));
    ui->error_graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // Improved Euler Error Plot
    ui->error_graph->addGraph();
    ui->error_graph->graph(1)->setData(MG->x, EG->e_ie);
    ui->error_graph->graph(1)->setName("Improved Euler Error");
    ui->error_graph->graph(1)->setPen(QColor(255, 0, 0, 255));
    ui->error_graph->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // Runge-Kutta Error Plot
    ui->error_graph->addGraph();
    ui->error_graph->graph(2)->setData(MG->x, EG->e_rk);
    ui->error_graph->graph(2)->setName("Runge-Kutta Error");
    ui->error_graph->graph(2)->setPen(QColor(0, 255, 50, 255));
    ui->error_graph->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // Axis Settings
    ui->error_graph->xAxis->setLabel("X");
    ui->error_graph->yAxis->setLabel("Y Error");
    ui->error_graph->xAxis->setRange(x0, X);
    ui->error_graph->yAxis->setRange(0, maxY);

    // Legend Settings
    ui->error_graph->legend->setVisible(true);
    ui->error_graph->legend->setBrush(QBrush(QColor(255,255,255,150)));
    ui->error_graph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignTop);

    ui->error_graph->replot();
}
