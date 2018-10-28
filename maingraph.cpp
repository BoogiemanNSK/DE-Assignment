#include "maingraph.h"

/// Main Graphs Data Computation
MainGraph::MainGraph(double x0, double y0, double X, int N) {
    x.resize(N); y.resize(N);
    y_e.resize(N); y_ie.resize(N); y_rk.resize(N);
    x_a.resize(4); y_a.resize(4);

    double k1, k2, k3, k4; // For Runge-Kutta
    double h = (X - x0) / (N - 1); // Step
    double C = ivp(x0, y0); // Constant

    x[0] = x0;
    y[0] = y_e[0] = y_ie[0] = y_rk[0] = y0;

    // Asymptotes
    double a = asymp(C);
    x_a[0] = x_a[1] = 0 < a ? 0 : a;
    x_a[2] = x_a[3] = 0 < a ? a : 0;
    y_a[0] = y_a[3] = -pow(10, 300);
    y_a[1] = y_a[2] = pow(10, 300);

    // X Axis
    for (int i = 1; i < N; i++) {
        x[i] = x[i - 1] + h;
    }

    // Y Axis
    for (int i = 0; i < N - 1; i++) {
        // Original
        y[i + 1] = f(x[i + 1], C);

        // Asymptotes check
        /*if ((x[i] <= x_a[0] && x[i + 1] >= x_a[0]) ||
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
}

/// Variant 20 Differential Function
double MainGraph::df(double x, double y) {
    return pow(x, 3) * pow(y, 4) - (y / x);
}

/// Returns C (const) for given initial values
double MainGraph::ivp(double x0, double y0) {
    double r = 1 / (pow(x0,3) * pow(y0,3));
    return r + 3*x0;
}

/// Analytically found Solution to Variant 20
double MainGraph::f(double x, double C) {
    double r = 1 / (C * pow(x, 3) - 3 * pow(x, 4));
    double p = (r > 0) ? pow(r, (1.0/3)) : (-1)*pow((-1) * r, (1.0/3));
    return p;
}

/// Returns second asymptote [x^3(C - 3x) = 0]
double MainGraph::asymp(double C) {
    return C / 3.0;
}
