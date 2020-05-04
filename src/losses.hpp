#ifndef LOSSES_HPP
#define LOSSES_HPP

#include "datasets.hpp"
#include <string>
#include <map>

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

class LabelCounter
{
    /** 
     * An object representing the number of occurences in each label.
     * Accepts doubles (because that's how )
     * */

private:

    // Attributes:
    std::map<int, int> counts_;  // The label counts.
    int total_size_;  // The total number of occurrences.

    // Utilities:
    int convert_to_key(double label) const;  // Verifies that the label is an integer and casts it to an int.

public:

    // Accessors:
    int size() const;  // The number of labels seen by the LabelCounter.
    int total_size() const; // The total number of instances.
    bool has_label(double label) const;  // Check if a label has been counted.
    int get_count(double label) const;  // Get counter value for specified label (coerced to integer).
    DataVector* get_labels() const;  // Get DataVector of labels.
    DataVector* get_values() const;  // Get DataVector of values.
    std::string to_string() const;  // Represent LabelCounter as string.
    void print() const;  // Print LabelCounter to standard output.

    // Utilities:
    void reset();  // Reset counters to zero.
    void increment(double label);  // Increment counter for specified label (coerced to integer).
    void increment(DataVector labels);  // Increment counter for a vector of labels.
    void increment(DataVector *labels);  // Increment counter for a vector (pointer) of labels.

    // Overloaded operators:
    friend std::ostream& operator<<(std::ostream& os, const LabelCounter& labelcounter);  // Print label counts.

    // Constructors:
    LabelCounter();  // Initialize counter with no counts.
    LabelCounter(DataVector labels);  // Initialize counter from given vector.
    LabelCounter(DataVector *labels);  // Initialize counter from given vector (pointer).

};

#endif
