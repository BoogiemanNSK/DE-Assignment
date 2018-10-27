#include "mainwindow.h"
#include "ui_mainwindow.h"

double df(double, double);
double f(double);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->initX->setText(QString::number(1));
    ui->initY->setText(QString::number(0.5));
    ui->maxX->setText(QString::number(5));
    ui->pointsNum->setText(QString::number(20));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    double x0 = ui->initX->toPlainText().toDouble();
    double y0 = ui->initY->toPlainText().toDouble();
    double X = ui->maxX->toPlainText().toDouble();
    int N = ui->pointsNum->toPlainText().toInt();

    double h = (X - x0) / (N - 1);
    QVector<double> x(N), y(N), y_e(N), y_ie(N), y_rk(N);

    x[0] = x0;
    y[0] = y_e[0] = y_ie[0] = y_rk[0] = y0;

    // X Axis
    for (int i = 1; i < N; i++) {
        x[i] = x[i - 1] + h;
    }

    // Original Equation
    for (int i = 1; i < N; i++) {
        y[i] = f(x[i]);
    }

    // Euler Method
    for (int i = 0; i < N - 1; i++) {
        y_e[i + 1] = y_e[i] + h * df(x[i], y_e[i]);
    }

    // Improved Euler Method
    for (int i = 0; i < N - 1; i++) {
        y_ie[i + 1] = y_ie[i] + (h / 2) * (df(x[i], y_ie[i]) + df(x[i + 1], y_e[i + 1]));
    }

    // Runge-Kutta Method
    double k1, k2, k3, k4;
    for (int i = 0; i < N - 1; i++) {
        k1 = df(x[i], y_rk[i]);
        k2 = df(x[i] + (h / 2), y_rk[i] + (h / 2) * k1);
        k3 = df(x[i] + (h / 2), y_rk[i] + (h / 2) * k2);
        k4 = df(x[i] + h, y_rk[i] + h * k3);
        y_rk[i + 1] = y_rk[i] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
    }

    ui->graph->clearGraphs();

    ui->graph->addGraph();
    ui->graph->addGraph();
    ui->graph->addGraph();
    ui->graph->addGraph();

    ui->graph->graph(0)->setData(x, y);
    ui->graph->graph(1)->setData(x, y_e);
    ui->graph->graph(2)->setData(x, y_ie);
    ui->graph->graph(3)->setData(x, y_rk);

    ui->graph->graph(0)->setPen(QColor(40, 40, 40, 255));
    ui->graph->graph(1)->setPen(QColor(0, 0, 255, 255));
    ui->graph->graph(2)->setPen(QColor(255, 0, 0, 255));
    ui->graph->graph(3)->setPen(QColor(0, 255, 50, 255));

    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->graph->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");
    ui->graph->xAxis->setRange(x0, X);

    double minY = y[0], maxY = y[0];
    for (int i=1; i<N; i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y_e[i]<minY) minY = y_e[i];
        if (y_ie[i]<minY) minY = y_ie[i];
        if (y_rk[i]<minY) minY = y_rk[i];

        if (y[i]>maxY) maxY = y[i];
    }
    ui->graph->yAxis->setRange(minY, maxY);
    ui->graph->replot();
}

double df(double x, double y) {
    return pow(x, 3) * pow(y, 4) - (y / x);
}

double f(double x) {
    return pow(1.0 / (11.0*pow(x, 3) - 3.0*pow(x, 4)), (1.0 / 3.0));
}
