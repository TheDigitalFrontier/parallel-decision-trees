#include <vector>

class DataCell
{
    /** 
     * A cell in a DataRow.
     * */

private:

    // Attributes:
    bool locked_;  // Flag to prevent edits after construction.
    double value_;

public:
    
    // Accessors:
    double value();

    // Utilities:
    void lock();

    // Constructors:
    DataCell();
    DataCell(double value);

};

class DataRow
{
    /** 
     * A row in a DataFrame.
     * */

private:

    // Attributes:
    bool locked_;  // Flag to prevent edits after construction.
    std::vector<DataCell> cells_;  // Vector of cells in this row.
    int width_;  // Number of cells in this row.

public:

    // Accessors:
    int width();
    DataCell *cell(int c);  // Get cell in given column.

    // Utilities:
    void lock();
    void addCell(DataCell *cell);

    // Constructors:
    DataRow();
    DataRow(std::vector<double> vector);

};

class DataCol
{
    /** 
     * A column in a DataFrame.
     * Not part of the DataFrame structure; only used as a return type.
     * */

private:

    // Attributes:
    bool locked_;  // Flag to prevent edits after construction.
    std::vector<DataCell> cells_;  // Vector of cells in this column.
    int length_;  // Number of cells in this row.

public:

    // Accessors:
    int length();
    DataCell *cell(int r);  // Get cell in given row.
    
    // Utilities:
    void lock();
    void addCell(DataCell *cell);

    // Constructors:
    DataCol();
    DataCol(std::vector<double> vector);

};

class DataFrame
{
    /** 
     * A representation of tabular data.
     * */

private:

    // Attributes:
    bool locked_;  // Flag to prevent edits after construction.
    int length_;  // Number of rows.
    int width_;  // Number of columns.
    std::vector<DataRow> rows_;

public:

    // Accessors:
    int length();
    int width();
    DataRow *row(int r);  // Get given row.
    DataCol *col(int c);  // Get given column.
    DataCell *cell(int r, int c);  // Get cell in given row and column.

    // Utilities:
    void lock();
    void addRow(DataRow *row);

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
    DataFrame load();

    // Constructors:
    DataLoader();  // Load hard-coded dummy dataset.
    DataLoader(std::vector<std::vector<double>> matrix);

};
