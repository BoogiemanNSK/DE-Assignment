#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <limits>

double df(double, double);
double ivp(double, double);
double f(double, double);
double asymp(double);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->initX->setText(QString::number(1));
    ui->initY->setText(QString::number(0.5));
    ui->maxX->setText(QString::number(5));
    ui->minY->setText(QString::number(-2));
    ui->maxY->setText(QString::number(2));
    ui->pointsNum->setText(QString::number(100));
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

    double minY = ui->minY->toPlainText().toDouble();
    double maxY = ui->maxY->toPlainText().toDouble();

    double h = (X - x0) / (N - 1);
    double C = ivp(x0, y0);
    QVector<double> x(N), y(N), y_e(N), y_ie(N), y_rk(N);
    QVector<double> x_a(4), y_a(4);

    double a = asymp(C);
    x_a[0] = x_a[1] = 0 < a ? 0 : a;
    x_a[2] = x_a[3] = 0 < a ? a : 0;
    y_a[0] = y_a[3] = -pow(10, 300);
    y_a[1] = y_a[2] = pow(10, 300);

    x[0] = x0;
    y[0] = y_e[0] = y_ie[0] = y_rk[0] = y0;

    int i;

    // X Axis
    for (i = 1; i < N; i++) {
        x[i] = x[i - 1] + h;
    }

    double k1, k2, k3, k4;
    for (int i = 0; i < N - 1; i++) {
        // Original
        y[i + 1] = f(x[i + 1], C);

        /*// Asymptotes check
        if ((x[i] <= x_a[0] && x[i + 1] >= x_a[0]) ||
                (x[i] <= x_a[2] && x[i + 1] >= x_a[2])) {
            y[i + 1] = f(x[i + 1], C);
            y_e[i + 1] = f(x[i + 1], C);
            y_ie[i + 1] = f(x[i + 1], C);
            y_rk[i + 1] = f(x[i + 1], C);
            continue;
        }*/

        // Euler
        y_e[i + 1] = y_e[i] + h * df(x[i], y_e[i]);

        // Improved Euler
        y_ie[i + 1] = y_ie[i] + (h / 2) * (df(x[i], y_ie[i]) + df(x[i + 1], y_e[i + 1]));

        // Runge-Kutta
        k1 = df(x[i], y_rk[i]);
        k2 = df(x[i] + (h / 2), y_rk[i] + (h / 2) * k1);
        k3 = df(x[i] + (h / 2), y_rk[i] + (h / 2) * k2);
        k4 = df(x[i] + h, y_rk[i] + h * k3);
        y_rk[i + 1] = y_rk[i] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
    }

    ui->graph->clearGraphs();

    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x, y);
    ui->graph->graph(0)->data()->erase(ui->graph->graph(0)->data()->find(2));
    ui->graph->graph(0)->setName("Original Equation");
    ui->graph->graph(0)->setPen(QColor(40, 40, 40, 255));
    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    ui->graph->addGraph();
    ui->graph->graph(1)->setData(x, y_e);
    ui->graph->graph(1)->setName("Euler Method");
    ui->graph->graph(1)->setPen(QColor(0, 0, 255, 255));
    ui->graph->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    ui->graph->addGraph();
    ui->graph->graph(2)->setData(x, y_ie);
    ui->graph->graph(2)->setName("Improved Euler Method");
    ui->graph->graph(2)->setPen(QColor(255, 0, 0, 255));
    ui->graph->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    ui->graph->addGraph();
    ui->graph->graph(3)->setData(x, y_rk);
    ui->graph->graph(3)->setName("Runge-Kutta Method");
    ui->graph->graph(3)->setPen(QColor(0, 255, 50, 255));
    ui->graph->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

    ui->graph->addGraph();
    ui->graph->graph(4)->setData(x_a, y_a);
    ui->graph->graph(4)->setName("Asymptotes");
    ui->graph->graph(4)->setPen(QColor(20, 20, 20, 128));
    ui->graph->graph(4)->setPen(Qt::DashLine);

    ui->graph->xAxis->setLabel("X");
    ui->graph->yAxis->setLabel("Y");
    ui->graph->xAxis->setRange(x0, X);
    ui->graph->yAxis->setRange(minY, maxY);

    ui->graph->legend->setVisible(true);
    ui->graph->legend->setBrush(QBrush(QColor(255,255,255,150)));
    ui->graph->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignTop);

    ui->graph->replot();
}

double df(double x, double y) {
    return pow(x, 3) * pow(y, 4) - (y / x);
}

double ivp(double x0, double y0) {
    double r = 1 / (pow(x0,3) * pow(y0,3));
    return r + 3*x0;
}

double f(double x, double C) {
    double r = 1 / (C * pow(x, 3) - 3 * pow(x, 4));
    double p = (r > 0) ? pow(r, (1.0/3)) : (-1)*pow((-1) * r, (1.0/3));
    return p;
}

double asymp(double C) {
    return C / 3.0;
}
