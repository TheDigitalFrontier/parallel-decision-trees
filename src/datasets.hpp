#ifndef DATASETS_HPP
#define DATASETS_HPP

#include <vector>
#include <string>

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
    double value(int c) const;  // Get value in given position.
    std::vector<double> vector() const;  // Get a copy of values as a vector of doubles.
    double sum() const;  // Returns the sum of the values in the vector.
    double mean() const;  // Returns the mean of the values in the vector.

    // Utilities:
    void lock();  // Lock object to make it read-only.
    void addValue(double value);  // Add value to vector.
    DataVector* copy() const;  // Returns a copy of the DataVector.
    DataVector* transpose() const;  // Returns a transposed copy of the DataVector.
    std::vector<DataVector*> split(double split_threshold, bool equal_goes_left=true) const;  // Returns a pair of vectors (value above and below threshold).
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
    DataVector* col(int c) const;  // Get pointerto given column (constructed on the fly).
    double value(int r, int c) const;  // Get value in given row and column.
    std::vector<std::vector<double>> matrix() const;  // Get a copy of values as a vector of vectors of doubles.
    DataVector* sum(bool axis=0) const;  // Returns a vector of the means down columns (axis==0) or across rows (axis==1).
    DataVector* mean(bool axis=0) const;  // Returns a vector of the means down columns (axis==0) or across rows (axis==1).

    // Utilities:
    void lock();  // Lock object to make it read-only.
    void addRow(DataVector *row);  // Append to the list of rows (as pointer).
    void addRow(std::vector<double> vector);  // Wrap the values in a DataRow and add its pointer to the list.
    void addCol(DataVector *col);  // Append the values each row in the list (from pointer).
    void addCol(std::vector<double> vector);  // Append the values to each row in the list.
    DataFrame copy() const;  // Returns a copy of the DataFrame.
    DataFrame transpose() const;  // Returns a transposed copy of the DataFrame.
    std::vector<DataFrame*> split(int split_column, double split_threshold, bool equal_goes_left=true) const;  // Returns a pair of frames (value above and below threshold in specified column).
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

};

#endif
