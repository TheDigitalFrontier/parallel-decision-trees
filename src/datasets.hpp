#include <vector>

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
    int size();  // Returns number of entries in vector.
    bool is_row();  // Checks if object represents a row (true) or column (false).
    bool is_locked();  // Checks if object is read-only.
    double value(int c);  // Get value in given position.
    std::vector<double> vector();  // Get a copy of values as a vector of doubles.

    // Utilities:
    void lock();  // Lock object to make it read-only.
    void addValue(double value);  // Add value to vector.

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
    int length();  // Returns number of rows.
    int width();  // Returns number of columns.
    bool is_locked();  // Checks if object is read-only.
    DataVector* row(int r);  // Get pointer to given row (stored internally).
    DataVector col(int c);  // Get given column (constructed on the fly).
    double value(int r, int c);  // Get value in given row and column.
    std::vector<std::vector<double>> matrix();  // Get a copy of values as a vector of vectors of doubles.

    // Utilities:
    void lock();  // Lock object to make it read-only.
    void addRow(DataVector *row);  // Append the pointer to the list of rows.
    void addRow(std::vector<double> vector);  // Wrap the values in a DataRow and add its pointer to the list.
    void addCol(DataVector col);  // Append the values to each row in the list.
    void addCol(std::vector<double> vector);  // Append the values to each row in the list.
    DataFrame transpose();  // Returns a transposed copy of the DataFrame.

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
