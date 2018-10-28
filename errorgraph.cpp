#include "errorgraph.h"

/// Errors Data Computation
ErrorGraph::ErrorGraph(MainGraph* MG) {
    int N = MG->x.size();
    e_e.resize(N);
    e_ie.resize(N);
    e_rk.resize(N);

    for (int i = 0; i < N; i++) {
        e_e[i] = std::abs(MG->y[i] - MG->y_e[i]);
        e_ie[i] = std::abs(MG->y[i] - MG->y_ie[i]);
        e_rk[i] = std::abs(MG->y[i] - MG->y_rk[i]);
    }
}
