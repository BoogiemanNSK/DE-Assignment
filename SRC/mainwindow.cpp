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
    ui->minY->setText(QString::number(-1));
    ui->maxY->setText(QString::number(1));
    ui->pointsNum->setText(QString::number(200));

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
    ui->graph->graph(0)->setData(MG->x[0], MG->y[0]);
    ui->graph->graph(0)->setName("Original Equation");
    ui->graph->graph(0)->setPen(QColor(40, 40, 40, 255));
    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->addGraph();
    ui->graph->graph(1)->setData(MG->x[1], MG->y[1]);
    ui->graph->graph(1)->setPen(QColor(40, 40, 40, 255));
    ui->graph->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(1)->removeFromLegend();
    ui->graph->addGraph();
    ui->graph->graph(2)->setData(MG->x[2], MG->y[2]);
    ui->graph->graph(2)->setPen(QColor(40, 40, 40, 255));
    ui->graph->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(2)->removeFromLegend();

    // Euler Method Plot
    ui->graph->addGraph();
    ui->graph->graph(3)->setData(MG->x[0], MG->y_e[0]);
    ui->graph->graph(3)->setName("Euler Method");
    ui->graph->graph(3)->setPen(QColor(0, 0, 255, 255));
    ui->graph->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->addGraph();
    ui->graph->graph(4)->setData(MG->x[1], MG->y_e[1]);
    ui->graph->graph(4)->setPen(QColor(0, 0, 255, 255));
    ui->graph->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(4)->removeFromLegend();
    ui->graph->addGraph();
    ui->graph->graph(5)->setData(MG->x[2], MG->y_e[2]);
    ui->graph->graph(5)->setPen(QColor(0, 0, 255, 255));
    ui->graph->graph(5)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(5)->removeFromLegend();

    // Improved Euler Method Plot
    ui->graph->addGraph();
    ui->graph->graph(6)->setData(MG->x[0], MG->y_ie[0]);
    ui->graph->graph(6)->setName("Improved Euler Method");
    ui->graph->graph(6)->setPen(QColor(255, 0, 0, 255));
    ui->graph->graph(6)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->addGraph();
    ui->graph->graph(7)->setData(MG->x[1], MG->y_ie[1]);
    ui->graph->graph(7)->setPen(QColor(255, 0, 0, 255));
    ui->graph->graph(7)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(7)->removeFromLegend();
    ui->graph->addGraph();
    ui->graph->graph(8)->setData(MG->x[2], MG->y_ie[2]);
    ui->graph->graph(8)->setPen(QColor(255, 0, 0, 255));
    ui->graph->graph(8)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(8)->removeFromLegend();

    // Runge-Kutta Method Plot
    ui->graph->addGraph();
    ui->graph->graph(9)->setData(MG->x[0], MG->y_rk[0]);
    ui->graph->graph(9)->setName("Runge-Kutta Method");
    ui->graph->graph(9)->setPen(QColor(0, 255, 50, 255));
    ui->graph->graph(9)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->addGraph();
    ui->graph->graph(10)->setData(MG->x[1], MG->y_rk[1]);
    ui->graph->graph(10)->setPen(QColor(0, 255, 50, 255));
    ui->graph->graph(10)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(10)->removeFromLegend();
    ui->graph->addGraph();
    ui->graph->graph(11)->setData(MG->x[2], MG->y_rk[2]);
    ui->graph->graph(11)->setPen(QColor(0, 255, 50, 255));
    ui->graph->graph(11)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(11)->removeFromLegend();

    // Asymptotes Plot (2 vertical lines)
    ui->graph->addGraph();
    ui->graph->graph(12)->setData(MG->x_a, MG->y_a);
    ui->graph->graph(12)->setName("Asymptotes");
    ui->graph->graph(12)->setPen(QColor(20, 20, 20, 128));
    ui->graph->graph(12)->setPen(Qt::DashLine);

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

    int NAll = MG->x[0].size() + MG->x[1].size() + MG->x[2].size();
    QVector<double> xAll(NAll);
    for (int i = 0, j = 0, k = 0; i < NAll; i++, k++) {
        if (k >= MG->x[j].size()) { j++; k = 0; }
        xAll[i] = MG->x[j][k];
    }

    ui->error_graph->clearGraphs();

    // Euler Error Plot
    ui->error_graph->addGraph();
    ui->error_graph->graph(0)->setData(xAll, EG->e_e);
    ui->error_graph->graph(0)->setName("Euler Error");
    ui->error_graph->graph(0)->setPen(QColor(0, 0, 255, 255));
    ui->error_graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // Improved Euler Error Plot
    ui->error_graph->addGraph();
    ui->error_graph->graph(1)->setData(xAll, EG->e_ie);
    ui->error_graph->graph(1)->setName("Improved Euler Error");
    ui->error_graph->graph(1)->setPen(QColor(255, 0, 0, 255));
    ui->error_graph->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // Runge-Kutta Error Plot
    ui->error_graph->addGraph();
    ui->error_graph->graph(2)->setData(xAll, EG->e_rk);
    ui->error_graph->graph(2)->setName("Runge-Kutta Error");
    ui->error_graph->graph(2)->setPen(QColor(0, 255, 50, 255));
    ui->error_graph->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    // UI Separator
    ui->error_graph->addGraph();
    ui->error_graph->graph(3)->setPen(QColor(0, 0, 0, 0));
    ui->error_graph->graph(3)->setName("------------------------------------");

    std::string name;

    // Euler Total Error (on Legend)
    name = "Euler Total Error = " + std::to_string(EG->total_e);
    ui->error_graph->addGraph();
    ui->error_graph->graph(4)->setPen(QColor(0, 0, 0, 0));
    ui->error_graph->graph(4)->setName(QString::fromStdString(name));

    // Improved Euler Total Error (on Legend)
    name = "Improved Euler Total Error = " + std::to_string(EG->total_ie);
    ui->error_graph->addGraph();
    ui->error_graph->graph(5)->setPen(QColor(0, 0, 0, 0));
    ui->error_graph->graph(5)->setName(QString::fromStdString(name));

    // Runge-Kutta Total Error (on Legend)
    name = "Runge-Kutta Total Error = " + std::to_string(EG->total_rk);
    ui->error_graph->addGraph();
    ui->error_graph->graph(6)->setPen(QColor(0, 0, 0, 0));
    ui->error_graph->graph(6)->setName(QString::fromStdString(name));

    // Axis Settings
    ui->error_graph->xAxis->setLabel("X");
    ui->error_graph->yAxis->setLabel("Y Error");
    ui->error_graph->xAxis->setRange(x0, X);
    ui->error_graph->yAxis->setRange(0, maxY);

    // Legend Settings
    ui->error_graph->legend->setVisible(true);
    ui->error_graph->legend->setBrush(QBrush(QColor(255,255,255,120)));
    ui->error_graph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->error_graph->replot();
}
