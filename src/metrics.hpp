#ifndef METRICS_HPP
#define METRICS_HPP

#include "datasets.hpp"
#include <string>
#include <map>

double accuracy(DataVector targets, DataVector predictions);
double accuracy(DataVector *targets, DataVector *predictions);

/* double precision(DataVector targets, DataVector predictions);
double precision(DataVector *targets, DataVector *predictions);

double recall(DataVector targets, DataVector predictions);
double recall(DataVector *targets, DataVector *predictions);

double f1_score(DataVector targets, DataVector predictions);
double f1_score(DataVector *targets, DataVector *predictions); */

#endif
