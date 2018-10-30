#include "maingraph.h"

/// Main Graphs Data Computation
MainGraph::MainGraph(double x0, double y0, double X, int N) {
    double k1, k2, k3, k4; // For Runge-Kutta
    double h = (X - x0) / (N - 1); // Step
    double C = ivp(x0, y0); // Constant

    x.resize(3); y.resize(3); y_e.resize(3); y_ie.resize(3); y_rk.resize(3);
    x_a.resize(4); y_a.resize(4);

    // Asymptotes
    double a = asymp(C);
    x_a[0] = x_a[1] = 0 < a ? 0 : a;
    x_a[2] = x_a[3] = 0 < a ? a : 0;
    y_a[0] = y_a[3] = -pow(10, 300);
    y_a[1] = y_a[2] = pow(10, 300);

    // X Axis
    double t = x0;
    for (int i = 0; i < N; i++, t+=h) {
        if (t < x_a[0]) { x[0].push_back(t); }
        else if (t > x_a[0] && t < x_a[2]) { x[1].push_back(t); }
        else { x[2].push_back(t); }
    }

    // Resizing
    int first_non_zero = -1;
    for (int i = 0; i < 3; i++) {
        y[i].resize(x[i].size());
        y_e[i].resize(x[i].size());
        y_ie[i].resize(x[i].size());
        y_rk[i].resize(x[i].size());
        if (first_non_zero == -1 && x[i].size() > 0) { first_non_zero = i; }
    }

    y[first_non_zero][0] =
            y_e[first_non_zero][0] =
            y_ie[first_non_zero][0] =
            y_rk[first_non_zero][0] = y0;

    // Y Axis
    for (int j = 0; j < 3; j++) {
        if (y[j].size() > 0 && first_non_zero < j) {
            y[j][0] = -1 * y[j - 1][y[j - 1].size() - 1];
            y_e[j][0] = -1 * y_e[j - 1][y[j - 1].size() - 1];
            y_ie[j][0] = -1 * y_ie[j - 1][y[j - 1].size() - 1];
            y_rk[j][0] = -1 * y_rk[j - 1][y[j - 1].size() - 1];
        }
        for (int i = 0; i < x[j].size() - 1; i++) {
            // Original
            y[j][i + 1] = f(x[j][i + 1], C);

            // Euler
            y_e[j][i + 1] = y_e[j][i] + h * df(x[j][i], y_e[j][i]);

            // Improved Euler
            y_ie[j][i + 1] = y_ie[j][i] + (h / 2) * (df(x[j][i], y_ie[j][i]) + df(x[j][i + 1], y_e[j][i + 1]));

            // Runge-Kutta
            k1 = df(x[j][i], y_rk[j][i]);
            k2 = df(x[j][i] + (h / 2), y_rk[j][i] + (h / 2) * k1);
            k3 = df(x[j][i] + (h / 2), y_rk[j][i] + (h / 2) * k2);
            k4 = df(x[j][i] + h, y_rk[j][i] + h * k3);
            y_rk[j][i + 1] = y_rk[j][i] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        }
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
