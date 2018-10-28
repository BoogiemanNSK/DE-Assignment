#ifndef MAINGRAPH_H
#define MAINGRAPH_H

#include <QVector>

class MainGraph
{
public:
    MainGraph(double, double, double, int);
    QVector<double> x, y, y_e, y_ie, y_rk;
    QVector<double> x_a, y_a;

private:
    double df(double, double);
    double ivp(double, double);
    double f(double, double);
    double asymp(double);
};

#endif // MAINGRAPH_H
