#include "errorgraph.h"

/// Errors Data Computation
ErrorGraph::ErrorGraph(MainGraph* MG) {
    int N = MG->x[0].size() + MG->x[1].size() + MG->x[2].size();
    e_e.resize(N);
    e_ie.resize(N);
    e_rk.resize(N);

    total_e = total_ie = total_rk = 0;

    for (int i = 0, j = 0, k = 0; i < N; i++, k++) {
        if (k >= MG->x[j].size()) { j++; k = 0; }

        e_e[i] = std::abs(MG->y[j][k] - MG->y_e[j][k]);
        e_ie[i] = std::abs(MG->y[j][k] - MG->y_ie[j][k]);
        e_rk[i] = std::abs(MG->y[j][k] - MG->y_rk[j][k]);

        total_e += e_e[i];
        total_ie += e_ie[i];
        total_rk += e_rk[i];
    }
}
