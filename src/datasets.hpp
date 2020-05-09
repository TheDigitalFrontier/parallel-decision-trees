#ifndef DATASETS_HPP
#define DATASETS_HPP

#include <vector>
#include <string>
#include <random>

class DataVector
{
    /**
     * A row (or column) in a DataFrame.
     * */

private:

    // Attributes:
    bool is_locked_;  // Flag to prevent edits after construction.
    bool is_row_;  // Flag to track whether a vector is a row or column.
    std::vector<double> values_;  // Vector of value.
    int size_;  // Number of values in this vector.

public:

    // Accessors:
    int size() const;  // Returns number of entries in vector.
    bool is_row() const;  // Checks if object represents a row (true) or column (false).
    bool is_locked() const;  // Checks if object is read-only.
    double value(int i) const;  // Get value in given position.
    double getValue(int i) const;  // Get value in given position.
    std::vector<double> vector() const;  // Get a copy of values as a vector of doubles.
    double min() const;  // Returns the min of the values in the vector.
    double max() const;  // Returns the max of the values in the vector.
    double sum() const;  // Returns the sum of the values in the vector.
    double mean() const;  // Returns the mean of the values in the vector.

    // Setters:
    void setValue(int i, double value);  // Get value in given position.

    // Utilities:
    void lock();  // Lock object to make it read-only.
    void addValue(double value);  // Add value to vector.
    DataVector copy() const;  // Returns a copy of the DataVector.
    DataVector transpose() const;  // Returns a transposed copy of the DataVector.
    std::vector<DataVector> split(double split_threshold, bool equal_goes_left=true) const;  // Returns a pair of vectors (value above and below threshold).
    std::string to_string(bool new_line=true, int col_width=9) const;  // Return the DataVector as a string.
    void print(bool new_line=true, int col_width=9) const;  // Print the data vector.

    // Overloaded operators:
    friend std::ostream& operator<<(std::ostream& os, const DataVector& datavector);

    // Constructors:
    DataVector(bool is_row=true);
    DataVector(std::vector<double> vector, bool is_row=true);

};

class DataFrame
{
    /**
     * A representation of tabular data.
     * */

private:

    // Attributes:
    bool is_locked_;  // Flag to prevent edits after construction.
    int length_;  // Number of rows.
    int width_;  // Number of columns.
    std::vector<DataVector*> rows_;  // A vector of pointers to data rows.

public:

    // Accessors:
    int length() const;  // Returns number of rows.
    int width() const;  // Returns number of columns.
    bool is_locked() const;  // Checks if object is read-only.
    DataVector* row(int r) const;  // Get pointer to given row (stored internally).
    DataVector col(int c) const;  // Get given column (constructed on the fly).
    double value(int r, int c) const;  // Get value in given row and column.
    double getValue(int r, int c) const;  // Get value in given row and column.
    std::vector<std::vector<double>> matrix() const;  // Get a copy of values as a vector of vectors of doubles.
    DataVector min(bool axis=0) const;  // Returns a vector of the min down columns (axis==0) or across rows (axis==1).
    DataVector max(bool axis=0) const;  // Returns a vector of the max down columns (axis==0) or across rows (axis==1).
    DataVector sum(bool axis=0) const;  // Returns a vector of the means down columns (axis==0) or across rows (axis==1).
    DataVector mean(bool axis=0) const;  // Returns a vector of the means down columns (axis==0) or across rows (axis==1).

    // Setters:
    void setValue(int r, int c, double value);  // Set value in given row and column.

    // Utilities:
    void lock();  // Lock object to make it read-only.
    void addRow(DataVector *row);  // Append to the list of rows (as pointer).
    void addRow(std::vector<double> vector);  // Wrap the values in a DataRow and add its pointer to the list.
    void addCol(DataVector col);  // Append the values each row in the lists.
    void addCol(std::vector<double> vector);  // Append the values to each row in the list.
    DataFrame sample(int nrow = -1, int seed = -1, bool replace = true) const; // Samples
    DataFrame copy(bool deep=false) const;  // Returns a copy of the DataFrame.
    DataFrame transpose() const;  // Returns a transposed copy of the DataFrame.
    std::vector<DataFrame> split(int split_column, double split_threshold, bool equal_goes_left=true) const;  // Returns a pair of frames (value above and below threshold in specified column).
    std::vector<DataFrame> train_test_split(double split_pct, int seed = -1) const; // Returns a pair of train/test tables (sized using split_pct).
    std::string to_string(bool new_line=true, int col_width=9) const;  // Return the DataFrame as a string.
    void print(bool new_line=true, int col_width=9) const;  // Print the data frame.

    // Overloaded operators:
    friend std::ostream& operator<<(std::ostream& os, const DataFrame& dataframe);

    // Constructors:
    DataFrame();
    DataFrame(std::vector<std::vector<double>> matrix);

};

class DataLoader
{
    /**
     * A utility for building data frames.
     * */

private:

    // Attributes:
    DataFrame dataframe_;

    // Utilities:

public:

    // Accessors:

    // Utilities:
    DataFrame load();  // Return the loaded DataFrame.

    // Constructors:
    DataLoader();  // Load hard-coded dummy dataset.
    DataLoader(std::vector<std::vector<double>> matrix);
    DataLoader(std::string filename);

};

class SeedGenerator
{
    /** An object that generates pseudorandom seeds. */

private:

    // Attributes:
    int meta_seed_;
    std::mt19937 eng_;
    std::uniform_int_distribution<> distr_{1, 10000};
    // Utilities:

public:
    // Accessors:

    // Utilities:
    int new_seed();
    
    // Constructors:
    SeedGenerator(int meta_seed_=-1);
};

#endif
