#include "mainwindow.h"
#include <math.h>
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

double df(double, double);
double f(double);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QLineSeries *original = new QLineSeries();
    QLineSeries *euler = new QLineSeries();
    QLineSeries *improvedEuler = new QLineSeries();
    QLineSeries *rungeKutta = new QLineSeries();

    original->setName("Original Equation");
    euler->setName("Euler Method");
    improvedEuler->setName("Improved Euler Method");
    rungeKutta->setName("Runge-Kutta Method");

    double x0 = 1, y0 = 0.5;

    int N = 100;
    double X = 50;
    double h = (X - x0) / (N - 1);

    double *x = new double[N];
    double *y = new double[N];
    double *y_e = new double[N];
    double *y_ie = new double[N];
    double *y_rk = new double[N];

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

    for (int i = 0; i < N; i++) {
        original->append(x[i], y[i]);
        euler->append(x[i], y_e[i]);
        improvedEuler->append(x[i], y_ie[i]);
        rungeKutta->append(x[i], y_rk[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(original);
    chart->addSeries(euler);
    chart->addSeries(improvedEuler);
    chart->addSeries(rungeKutta);
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    w.setCentralWidget(chartView);
    w.show();

    return a.exec();
}

double df(double x, double y) {
    return pow(x, 3) * pow(y, 4) - (y / x);
}

double f(double x) {
    return pow(1.0 / (19.0*pow(x, 3) - 3.0*pow(x, 4)), (1.0 / 3.0));
}

