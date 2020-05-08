#ifndef METRICS_HPP
#define METRICS_HPP

#include "datasets.hpp"
#include <string>
#include <map>

// class Metric
// {
//     /**
//      * 
//      * */
// private:
//     std::string method_; // Metric type
//     // Utilities
// public:
//     // Accessors:
//     std::string method();
//     // Metric functions
//     double accuracy(DataVector targets, DataVector predictions);
//     double accuracy(DataVector *targets, DataVector *predictions);

//     // Overloaded operators:

//     // Constructors
//     Metric(std::string method);
// };

double accuracy(DataVector targets, DataVector predictions);
double accuracy(DataVector *targets, DataVector *predictions);

/* double precision(DataVector targets, DataVector predictions);
double precision(DataVector *targets, DataVector *predictions);

double recall(DataVector targets, DataVector predictions);
double recall(DataVector *targets, DataVector *predictions);

double f1_score(DataVector targets, DataVector predictions);
double f1_score(DataVector *targets, DataVector *predictions); */

#endif
