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
    int size() const;  // Returns number of entries in vector.
    bool is_row() const;  // Checks if object represents a row (true) or column (false).
    bool is_locked() const;  // Checks if object is read-only.
    double value(int c) const;  // Get value in given position.
    std::vector<double> vector() const;  // Get a copy of values as a vector of doubles.

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
    int length() const;  // Returns number of rows.
    int width() const;  // Returns number of columns.
    bool is_locked() const;  // Checks if object is read-only.
    DataVector* row(int r) const;  // Get pointer to given row (stored internally).
    DataVector col(int c) const;  // Get given column (constructed on the fly).
    double value(int r, int c) const;  // Get value in given row and column.
    std::vector<std::vector<double>> matrix() const;  // Get a copy of values as a vector of vectors of doubles.

    // Utilities:
    void lock();  // Lock object to make it read-only.
    void addRow(DataVector *row);  // Append the pointer to the list of rows.
    void addRow(std::vector<double> vector);  // Wrap the values in a DataRow and add its pointer to the list.
    void addCol(DataVector col);  // Append the values to each row in the list.
    void addCol(std::vector<double> vector);  // Append the values to each row in the list.
    DataFrame transpose() const;  // Returns a transposed copy of the DataFrame.
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
