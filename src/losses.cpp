#include "losses.hpp"
#include "datasets.hpp"
#include <stdexcept>
#include <assert.h>


/**
 * UTILITIES :
 */

double LossFunction::misclassification_rate(DataVector y_true, DataVector y_pred)
{
    /** Returns the loss calculated with misclassification_rate. */
    double loss;
    throw std::logic_error{"TO DO: implement misclassification_rate."};
    return loss;
}

double LossFunction::binary_cross_entropy(DataVector y_true, DataVector y_pred)
{
    /** Returns the loss calculated with binary_cross_entropy. */
    double loss;
    throw std::logic_error{"TO DO: implement binary_cross_entropy."};
    return loss;
}

double LossFunction::gini_impurity(DataVector y_true, DataVector y_pred)
{
    /** Returns the loss calculated with gini_impurity. */
    double loss;
    throw std::logic_error{"TO DO: implement gini_impurity."};
    return loss;
}

/**
 * ACCESSORS :
 */

std::string LossFunction::method()
{
    /** Returns the name of the loss method. */
    return this->method_;
}

/**
 * UTILITIES :
 */

double LossFunction::calculate(DataVector y_true, DataVector y_pred)
{
    assert (y_true.size()==y_pred.size());
    assert (y_true.size()>0);
    double loss;
    if (this->method_=="misclassification_rate") {
        loss = this->misclassification_rate(y_true,y_pred);
    } else if (this->method_=="binary_cross_entropy") {
        loss = this->binary_cross_entropy(y_true,y_pred);
    } else if (this->method_=="gini_impurity") {
        loss = this->gini_impurity(y_true,y_pred);
    }
    return loss;
}

/**
 * OVERLOADED OPERATORS :
 */

/**
 * CONSTRUCTORS :
 */

LossFunction::LossFunction(std::string method)
{
    /**
     * Initialize a loss function with one of the specified methods:
     *   misclassification_rate
     *   binary_cross_entropy
     *   gini_impurity
     * The loss will be minimized by the decision tree.
     */
    if (method=="misclassification_rate") {
        this->method_ = method;
    } else if (method=="binary_cross_entropy") {
        this->method_ = method;
    } else if (method=="gini_impurity") {
        this->method_ = method;
    } else {
        throw std::invalid_argument( "Received invalid loss method: "+method );
    }

}
