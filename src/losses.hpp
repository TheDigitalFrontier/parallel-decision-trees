#ifndef LOSSES_HPP
#define LOSSES_HPP

#include "datasets.hpp"
#include <string>

class LossFunction
{
    /** 
     * An object representing a loss function.
     * */

private:

    // Attributes:
    std::string method_;  // The loss type.

    // Utilities:
    double misclassification_rate(DataVector y_true, DataVector y_pred);
    double binary_cross_entropy(DataVector y_true, DataVector y_pred);
    double gini_impurity(DataVector y_true, DataVector y_pred);

public:

    // Accessors:
    std::string method();

    // Utilities:
    double calculate(DataVector y_true, DataVector y_pred);

    // Overloaded operators:

    // Constructors:
    LossFunction(std::string method);

};

#endif
