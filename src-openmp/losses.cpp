#include "losses.hpp"
#include "datasets.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <assert.h>


/**
 * LOSS FUNCTION - UTILITIES :
 */


double LossFunction::misclassification_error(DataVector labels)
{
    /** Returns the loss calculated with misclassification_error. */
    double loss;
    LabelCounter label_counter = LabelCounter(labels);
    int prediction = label_counter.get_most_frequent();
    int correct = 0;
    int incorrect = 0;
    for (int i = 0; i < labels.size(); i++)
    {
        if (labels.value(i) == prediction) {
            correct += 1;
        } else {
            incorrect += 1;
        }
    }
    loss = 1.0*incorrect/(correct+incorrect);
    return loss;
}

double LossFunction::cross_entropy(DataVector labels)
{
    /** Returns the loss calculated with cross_entropy. */
    double loss;
    LabelCounter label_counter = LabelCounter(labels);
    int sum_of_counts = label_counter.get_values().sum();  // Get total number of labels.
    assert (sum_of_counts==labels.size());
    int predicted_label = label_counter.get_most_frequent();
    DataVector labels_ = label_counter.get_labels();  // Get labels.
    DataVector counts_ = label_counter.get_values();  // Get count for each label.
    double prop;  // Temporary variable to store proportion of current class.
    for (int i = 0; i < counts_.size(); i++)
    {
        int label = labels_.value(i);
        int count = counts_.value(i);
        prop = 1.0*count/sum_of_counts;
        loss += prop * std::log2(prop);
    }
    loss = -loss;  // Negate the sum.
    return loss;
}

double LossFunction::gini_impurity(DataVector labels)
{
    /** Returns the loss calculated with gini_impurity. */
    double loss = 0;
    LabelCounter label_counter = LabelCounter(labels);
    int sum_of_counts = label_counter.get_values().sum();  // Get total number of labels.
    assert (sum_of_counts==labels.size());
    //int predicted_label = label_counter.get_most_frequent();
    DataVector counts_ = label_counter.get_values();  // Get count for each label (don't actually need the label).
    double prop;  // Temporary variable to store proportion of current class.
    for (int i = 0; i < counts_.size(); i++)
    {
        prop = 1.0*counts_.value(i)/sum_of_counts;
        loss += prop*(1-prop);
    }
    return loss;
}

double LossFunction::mean_squared_error(DataVector labels)
{
    /** Returns the mean squared error of a set of labels, assuming most common is used as prediction. */
    double prediction = labels.mean();
    double loss = 0;
    double error;
    for (int i = 0; i < labels.size(); i++)
    {
        error = ( labels.value(i) - prediction );
        loss += (error*error);
    }
    loss = 1.0*loss/labels.size();
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


double LossFunction::calculate(DataVector labels)
{
    assert (labels.size()>0);  // Loss is undefined for empty list.
    double loss;
    if (this->method_=="misclassification_error") {
        loss = this->misclassification_error(labels);
    } else if (this->method_=="cross_entropy") {
        loss = this->cross_entropy(labels);
    } else if (this->method_=="gini_impurity") {
        loss = this->gini_impurity(labels);
    } else if (this->method_=="mean_squared_error") {
        loss = this->mean_squared_error(labels);
    }
    return loss;
}

double LossFunction::calculate(DataVector *labels)
{
    return this->calculate(*labels);
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
     *   misclassification_error
     *   cross_entropy
     *   gini_impurity
     * The loss will be minimized by the decision tree.
     */
    if ( (method=="misclassification_error") or (method=="cross_entropy") or (method=="gini_impurity") ) {
        // Loss functions for classification tasks.
        this->method_ = method;
    } else if ( (method=="mean_squared_error") ) {
        // Loss functions for regression tasks.
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

DataVector LabelCounter::get_labels() const
{
    /** Get DataVector of labels. */
    DataVector labels = DataVector(false);  // is_row==false.
    std::map<int, int>::const_iterator it = this->counts_.begin();
    while (it != this->counts_.end())
    {
        int key = it->first;
        // int value = it->second;
        labels.addValue(key);
        it++;
    }
    return labels;
}
DataVector LabelCounter::get_values() const
{
    /** Get DataVector of values. */
    DataVector values = DataVector(false);  // is_row==false.
    std::map<int, int>::const_iterator it = this->counts_.begin();
    while (it != this->counts_.end())
    {
        // int key = it->first;
        int value = it->second;
        values.addValue(value);
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
        out += std::to_string(key) + ":" + std::to_string(value) + "; ";
        it++;
    }
    out = out.substr(0,out.length()-2) + ".";
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
    this->increment( *labels );
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
    this->increment(*labels);
}
