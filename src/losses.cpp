#include "losses.hpp"
#include "datasets.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <assert.h>
#include <math.h>


/**
 * LOSS FUNCTION - UTILITIES :
 */


double LossFunction::misclassification_rate(DataVector y_true, DataVector y_pred)
{
    /** Returns the loss calculated with misclassification_rate. */
    double loss;
    int correct = 0;
    int incorrect = 0;
    for (int i = 0; i < y_true.size(); i++)
    {
        if (y_true.value(i) == y_pred.value(i)){
            correct += 1;
        } else {
            incorrect += 1;
        }
    }
    loss = 1.0*incorrect/(correct+incorrect);
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
    double loss = 0;
    //// Find unique class labels
    //std::vector<double> classes;
    //for (int i = 0; i < y_true.size(); i++)
    //{
    //    classes.push_back(y_true.value(i));  // Add all values from y_true.
    //    classes.push_back(y_pred.value(i));  // Add all values from y_pred.
    //}
    //sort(classes.begin(), classes.end());
    //classes.erase(unique(classes.begin(), classes.end()), classes.end());
    //// For each class in set of unique class labels, calculate proportion and add to Gini:
    //double prop;
    //for(double& cur_class : classes){  // for-each
    //    // If class1 is not empty, iterate through it (perfect split means one df empty)
    //    if (class1.size() > 0){
    //        prop = double(std::count(class1.begin(), class1.end(), cur_class)) / class1.size();
    //        gini += (prop * (1.0 - prop));
    //    }
    //    if (class2.size() > 0){
    //        prop = double(std::count(class2.begin(), class2.end(), cur_class)) / class2.size();
    //        gini += (prop * (1 - prop));
    //    }
    //}
    return loss;
}


/**
 * LOSS FUNCTION - ACCESSORS :
 */


std::string LossFunction::method()
{
    /** Returns the name of the loss method. */
    return this->method_;
}


/**
 * LOSS FUNCTION - UTILITIES :
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
 * LOSS FUNCTION - OVERLOADED OPERATORS :
 */


/**
 * LOSS FUNCTION - CONSTRUCTORS :
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


/*
 * CLASSCOUNTER - ACCESSORS:
 */


int LabelCounter::size() const
{
    /** The number of labels seen by the LabelCounter. */
    return this->counts_.size();
}

int LabelCounter::total_size() const
{
    /** The number of labels seen by the LabelCounter. */
    return total_size_;
}


bool LabelCounter::has_label(double label) const
{
    /** Check if a label has been counted. */
    int key = this->convert_to_key(label);
    return (this->counts_.find(key) == this->counts_.end());
}

int LabelCounter::get_count(double label) const
{
    /** Get counter value for specified label (coerced to integer). */
    int key = this->convert_to_key(label);
    return counts_.at(key);
}

double LabelCounter::get_most_frequent() const
{
    /** Get most common label (breaking ties in favor of smallest label). */
    assert (this->size()>0);  // Not defined if counter is empty.
    double most_freq_key;
    int occurrences = 0;  // Number of occurrences of most frequent so far.
    std::map<int, int>::const_iterator it = this->counts_.begin();
    while (it != this->counts_.end())
    {
        int key = it->first;
        int value = it->second;
        if (value>occurrences)
        {
            most_freq_key = key;
            occurrences = value;
        } else if ((value==occurrences) and (key<most_freq_key)) {
            most_freq_key = key;
            occurrences = value;
        }
        it++;
    }
    return most_freq_key;
}

DataVector* LabelCounter::get_labels() const
{
    /** Get DataVector of labels. */
    DataVector *labels = new DataVector(false);  // is_row==false.
    std::map<int, int>::const_iterator it = this->counts_.begin();
    while (it != this->counts_.end())
    {
        int key = it->first;
        // int value = it->second;
        labels->addValue(key);
        it++;
    }
    return labels;
}
DataVector* LabelCounter::get_values() const
{
    /** Get DataVector of values. */
    DataVector *values = new DataVector(false);  // is_row==false.
    std::map<int, int>::const_iterator it = this->counts_.begin();
    while (it != this->counts_.end())
    {
        // int key = it->first;
        int value = it->second;
        values->addValue(value);
        it++;
    }
    return values;
}

std::string LabelCounter::to_string() const
{
    /** Represent LabelCounter as string. */
    std::string out = "";
    std::map<int, int>::const_iterator it = this->counts_.begin();
    while (it != this->counts_.end())
    {
        int key = it->first;
        int value = it->second;
        out += std::to_string(key) + " : " + std::to_string(value) + " ; ";
        it++;
    }
    out = out.substr(0,out.length()-2) + " .";
    return out;
}

void LabelCounter::print() const
{
    /** Print LabelCounter to standard output. */
    std::cout << this->to_string();
}


/*
 * CLASSCOUNTER - UTILITIES:
 */


int LabelCounter::convert_to_key(double label) const
{
    /** Verifies that the label is an integer and casts it to an int. */
    int key = (int) label;
    assert (std::floor(label) == key);
    return key;
}

void LabelCounter::reset()
{
    /** Reset counters to zero. */
    std::map<int, int> counts_;
    this->counts_ = counts_;
    this->total_size_ = 0;
}

void LabelCounter::increment(double label)
{
    /** Increment counter for specified class (coerced to integer). */
    int key = this->convert_to_key(label);
    if (this->counts_.find(key) == this->counts_.end()) {
        counts_.insert({key,1});
    } else {
        counts_.at(key) += 1;
    }
    this->total_size_ += 1;
}

void LabelCounter::increment(DataVector labels)
{
    /** Increment counter for a vector of labels. */
    for (int i = 0; i < labels.size(); i++)
    {
        this->increment( labels.value(i) );
    }
}

void LabelCounter::increment(DataVector *labels)
{
    /** Increment counter for a vector (pointer) of labels. */
    for (int i = 0; i < labels->size(); i++)
    {
        this->increment( labels->value(i) );
    }
}


/*
 * CLASSCOUNTER - OVERLOADED OPERATORS
 */


/*
 * CLASSCOUNTER - CONSTRUCTORS
 */


/*
 * DATA FRAME - I/O :
 */


std::ostream& operator<<(std::ostream& os, const LabelCounter& labelcounter)
{
    /**
     * Sends a string representation of the dataframe to the output stream.
     * Truncated or padded to the specified column width.
     **/
    os << labelcounter.to_string();
    return os;
}

LabelCounter::LabelCounter()
{
    /** Initialize counter with no counts. */
    this->total_size_ = 0;
}

LabelCounter::LabelCounter(DataVector labels)
{
    /** Initialize counter from given vector. */
    this->total_size_ = 0;
    this->increment(labels);
}

LabelCounter::LabelCounter(DataVector *labels)
{
    /** Initialize counter from given vector (pointer). */
    this->total_size_ = 0;
    this->increment(labels);
}
