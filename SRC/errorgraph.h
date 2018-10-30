#ifndef ERRORGRAPH_H
#define ERRORGRAPH_H

#include "maingraph.h"

class ErrorGraph
{
public:
    ErrorGraph(MainGraph*);
    QVector<double> e_e, e_ie, e_rk;
    double total_e, total_ie, total_rk;
};

#endif // ERRORGRAPH_H
