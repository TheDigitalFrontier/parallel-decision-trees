#include "datasets.hpp"
#include <assert.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <random>


/*
 * DATA VECTOR - ACCESSORS :
 */


int DataVector::size() const
{
    /** Returns the number of values in the row/column. */
    return this->size_;
}

bool DataVector::is_row() const
{
    /**
     * Returns true if the vector represents a row
     * and false if it represents a column.
     */
    return this->is_row_;
}

bool DataVector::is_locked() const
{
    /** Checks if object is read-only. */
    return this->is_locked_;
}

double DataVector::value(int i) const
{
    /** Get cell in given position (positive or negative index). */
    if (i>=0)
    {
        // Index from beginning (positive):
        assert ( i<this->size() );
    } else {
        // Index from end (negative):
        assert ( i>=-this->size() );
        i += this->size();
    }
    return this->values_[ i ];
}

std::vector<double> DataVector::vector() const
{
    /** Get a copy of the values as a vector of doubles. */
    std::vector<double> vector;
    for (int i = 0; i < this->size(); i++)
    {
        vector.push_back( this->values_[ i ] );
    }
    return vector;
}

double DataVector::min() const
{
    /** Returns the min of the values in the vector. */
    assert (this->size()>0);
    double min = this->values_[0];
    double val;
    for (int i = 0; i < this->size(); i++)
    {
        val = this->values_[i];
        if (val<min) { min = val; }
    }
    return min;
}

double DataVector::max() const
{
    /** Returns the min of the values in the vector. */
    assert (this->size()>0);
    double max = this->values_[0];
    double val;
    for (int i = 0; i < this->size(); i++)
    {
        val = this->values_[i];
        if (val>max) { max = val; }
    }
    return max;
}

double DataVector::sum() const
{
    /** Returns the sum of the values in the vector. */
    double sum = 0;
    for (int i = 0; i < this->size(); i++)
    {
        sum += this->values_[i];
    }
    return sum;
}

double DataVector::mean() const
{
    /** Returns the mean of the values in the vector. */
    double sum = 0;
    for (int i = 0; i < this->size(); i++)
    {
        sum += this->values_[i];
    }
    return sum / this->size();
}


/*
 * DATA VECTOR - UTILITES :
 */


void DataVector::lock()
{
    /** Prevent unwanted changes to data. */
    this->is_locked_ = true;
}

void DataVector::addValue(double value)
{
    /** Adds a cell to a row. */
    assert (!this->is_locked());
    this->values_.push_back(value);
    this->size_ += 1;
}

DataVector DataVector::copy() const
{
    /** Returns a copy of the DataVector. */
    bool new_is_row = this->is_row();
    DataVector new_vector = DataVector(this->vector(),new_is_row);
    return new_vector;
}

DataVector DataVector::transpose() const
{
    /** Returns a pointer to a new vector that is the transpose of this one. */
    bool new_is_row = !this->is_row();
    DataVector new_vector = DataVector(this->vector(),new_is_row);
    return new_vector;
}

std::vector<DataVector> DataVector::split(double split_threshold, bool equal_goes_left) const
{
    /**
     * Returns a pair of vectors (value above and below split_threshold).
     * Values equal to the threshold go left if equal_goes_left==true and right otherwise.
     */
    DataVector left = DataVector(this->is_row());
    DataVector right = DataVector(this->is_row());
    for (int i = 0; i < this->size(); i++)
    {
        double split_val = this->value(i);
        if (split_val<split_threshold) {
            left.addValue(split_val);
        } else if (split_val>split_threshold) {
            right.addValue(split_val);
        } else if (equal_goes_left) {
            left.addValue(split_val);
        } else if (!equal_goes_left) {
            right.addValue(split_val);
        }
    }
    std::vector<DataVector> results = { left, right };
    return results;
}

std::string DataVector::to_string(bool new_line, int col_width) const
{
    /**
     * Returns a string representation (row or column) of the vector.
     * Truncated or padded to the specified column width.
     */
    std::string out = "";
    for (int i = 0; i < this->size(); i++)
    {
        out += "| ";
        double value = this->value(i);
        std::string pad,val = "";
        val = std::to_string(value);
        // Add space to align negative sign:
        if (value>=0)
        {
            val = ' '+val;
        }
        // Truncate if too long:
        if (val.length()>col_width)
        {
            val = val.substr(0,col_width);
        }
        // Pad if too short:
        if (val.length()<col_width)
        {
            pad.append(col_width-val.length(),' ');
        }
        // Append padding and value:
        out += pad;
        out += val;
        if ((!this->is_row()) or (i==this->size()-1))
        {
            out += " |\n";
        } else {
            out += ' ';
        }
    }
    // Add (optional) extra newline character:
    if (new_line)
    {
        out += '\n';
    }
    return out;
}

void DataVector::print(bool new_line, int col_width) const
{
    /**
     * Prints a string representation (row or column) of the vector.
     * Truncated or padded to the specified column width.
     */
    std::cout << this->to_string(new_line, col_width);
}


/*
 * DATA VECTOR - I/O :
 */


std::ostream& operator<<(std::ostream& os, const DataVector& datavector)
{
    /**
     * Sends a string representation (row or column) of the vector to the output stream.
     * Truncated or padded to the specified column width.
     */
    os << datavector.to_string(false);  // Don't add extra newline character.
    return os;
}


/*
 * DATA VECTOR - CONSTRUCTORS :
 */


DataVector::DataVector(bool is_row)
{
    this->is_row_ = is_row;
    this->is_locked_ = false;
    this->size_ = 0;
}

DataVector::DataVector(std::vector<double> vector, bool is_row)
{
    this->is_row_ = is_row;
    this->is_locked_ = false;
    this->size_ = 0;  // Wil be incremented as values are added.
    for (int i = 0; i < vector.size(); i++)
    {
        this->addValue( vector[i] );
    }
}


/*
 * DATA FRAME - ACCESSORS :
 */


int DataFrame::length() const
{
    /** Returns the number of rows in the frame. */
    return this->length_;
}

int DataFrame::width() const
{
    /** Returns the number of columns in the frame. */
    return this->width_;
}

bool DataFrame::is_locked() const
{
    /** Checks if object is read-only. */
    return this->is_locked_;
}

DataVector* DataFrame::row(int r) const
{
    /** Get pointer to given row (stored internally). */
    if (r>=0)
    {
        // Index from beginning (positive):
        assert ( r<this->length() );
    } else {
        // Index from end (negative):
        assert ( r>=-this->length() );
        r += this->length();
    }
    return this->rows_[ r ];
}

DataVector DataFrame::col(int c) const
{
    /** Get given column (constructed on the fly). */
    DataVector col = DataVector(false);  // is_row==false.
    if (c>=0)
    {
        // Index from beginning (positive):
        assert ( c<this->width() );
    } else {
        // Index from end (negative):
        assert ( c>=-this->width() );
        c += this->width();
    }
    for (int i = 0; i < this->length(); i++)
    {
        col.addValue( this->rows_[i]->value(c) );
    }
    return col;
}

double DataFrame::value(int r, int c) const
{
    /** Get value in given row and column. */
    return this->row(r)->value(c);
}

std::vector<std::vector<double>> DataFrame::matrix() const
{
    /** Get a copy of values as a vector of vectors of doubles. */
    std::vector<std::vector<double>> matrix;
    for (int i = 0; i < this->length(); i++)
    {
        std::vector<double> temp_vector;
        for (int j = 0; j < this->width(); j++)
        {
            temp_vector.push_back( this->value(i,j) );
        }
        matrix.push_back(temp_vector);
    }
    return matrix;
}

DataVector DataFrame::min(bool axis) const
{
    /**
     * Returns a vector of the min down columns (axis==0) or across rows (axis==1).
     * Returns a row if axis==0 and a column if axis==1.
     */
    DataVector result;
    if (axis==0) {
        result = DataVector(true);  // is_row==true.
        for (int i = 0; i < this->width(); i++) { result.addValue( this->col(i).min() ); }
    } else {
        result = DataVector(false);  // is_row==false.
        for (int i = 0; i < this->length(); i++) { result.addValue( this->row(i)->min() ); }
    }
    return result;
}

DataVector DataFrame::max(bool axis) const
{
    /**
     * Returns a vector of the max down columns (axis==0) or across rows (axis==1).
     * Returns a row if axis==0 and a column if axis==1.
     */
    DataVector result;
    if (axis==0) {
        result = DataVector(true);  // is_row==true.
        for (int i = 0; i < this->width(); i++) { result.addValue( this->col(i).max() ); }
    } else {
        result = DataVector(false);  // is_row==false.
        for (int i = 0; i < this->length(); i++) { result.addValue( this->row(i)->max() ); }
    }
    return result;
}

DataVector DataFrame::sum(bool axis) const
{
    /**
     * Returns a vector of the means down columns (axis==0) or across rows (axis==1).
     * Returns a row if axis==0 and a column if axis==1.
     */
    DataVector result;
    if (axis==0) {
        result = DataVector(true);  // is_row==true.
        for (int i = 0; i < this->width(); i++) { result.addValue( this->col(i).sum() ); }
    } else {
        result = DataVector(false);  // is_row==false.
        for (int i = 0; i < this->length(); i++) { result.addValue( this->row(i)->sum() ); }
    }
    return result;
}

DataVector DataFrame::mean(bool axis) const
{
    /**
     * Returns a vector of the means down columns (axis==0) or across rows (axis==1).
     * Returns a row if axis==0 and a column if axis==1.
     */
    DataVector result;
    if (axis==0) {
        result = DataVector(true);  // is_row==true.
        for (int i = 0; i < this->width(); i++) { result.addValue( this->col(i).mean() ); }
    } else {
        result = DataVector(false);  // is_row==false.
        for (int i = 0; i < this->length(); i++) { result.addValue( this->row(i)->mean() ); }
    }
    return result;
}


/*
 * DATA FRAME - UTILITES :
 */


void DataFrame::lock()
{
    /** Prevent unwanted changes to data. */
    this->is_locked_ = true;
    for (int i = 0; i < this->length(); i++)
    {
        this->rows_[i]->lock();
    }
}

void DataFrame::addRow(DataVector *row)
{
    /** Append the pointer to the list of rows. */
    assert (!this->is_locked());
    assert (row->is_row());
    if (this->rows_.size()==0)
    {
        // If this is the first row, set dimensions:
        this->width_ = row->size();  // Length will be incremented below.
    } else {
        // Otherwise, make sure it matches existing dimension.
        assert (row->size()==this->width());
    }
    this->rows_.push_back(row);
    this->length_ += 1;
}

void DataFrame::addRow(std::vector<double> vector)
{
    /** Wrap the values in a DataRow and add its pointer to the list. */
    // Create DataVector (row):
    DataVector* row = new DataVector(true);  // is_row==true.
    for (int i = 0; i < this->width(); i++)
    {
        row->addValue( vector[i] );
    }
    // Add DataVector to frame (and perform error-checking):
    this->addRow(row);
}

void DataFrame::addCol(DataVector col)
{
    /** Append the values to each row in the list. */
    assert (!this->is_locked());
    assert (!col.is_row());
    // If dataframe is empty, initialize empty rows:
    if (this->rows_.size()==0)
    {
        std::vector<double> empty_row = {};
        for (int i = 0; i < col.size(); i++) { this->addRow(empty_row); }
    }
    // Verify dimensions:
    assert (col.size()==this->length());
    for (int i = 0; i < this->length(); i++)
    {
        assert (!this->rows_[i]->is_locked());
        this->rows_[i]->addValue( col.value(i) );
    }
    this->width_ += 1;
}

void DataFrame::addCol(std::vector<double> vector)
{
    /** Append the values to each row in the list. */
    // Create DataVector (column):
    DataVector col = DataVector(vector,false);  // is_row==false.
    // Add DataColumn to frame (and perform error-checking):
    this->addCol(col);
}

DataFrame DataFrame::copy(bool deep) const
{
    /** Returns a copy of the DataFrame. (If deep=true, also copies each row.) */
    DataFrame new_frame;
    if (deep){
        new_frame = DataFrame(this->matrix());
    } else {
        new_frame = DataFrame();
        for (int i = 0; i < this->length(); i++)
        {
            new_frame.addRow(this->row(i));
        }
    }
    return new_frame;
}

DataFrame DataFrame::sample(int nrow, int seed) const{
    // Set random seed for reproducibility if specified
    if (seed == -1){
        // obtain a random number from hardware
        std::random_device rd;
        seed = rd();
    }else{
        assert(seed >= 0);
    }
    // number of rows to pull
    if (nrow == -1){
        nrow = this->length();
    }else{
        assert(nrow > 0);
    }
    // Seed the generator
    std::mt19937 eng(seed);
    // Draw row indices from uniform distribution
    std::uniform_int_distribution<> distr(0, this->length()-1);
    // Create new empty DataFrame
    DataFrame new_frame = DataFrame();
    // pull random rows (as pointers, not copies) until full
    while (new_frame.length() < nrow)
    {
        // get random row index with replacement
        int rand_row = distr(eng);
        // get pointer to that row in original dataframe and store in bootstrap
        new_frame.addRow(this->row(rand_row));
    }
    return new_frame;
}

DataFrame DataFrame::transpose() const
{
    /** Returns a new dataframe that is the transpose of this one. */
    DataFrame new_frame = DataFrame();
    // Get each column, transpose it, and add it as a row in new frame:
    for (int i = 0; i < this->width(); i++)
    {
        new_frame.addRow(this->col(i).transpose().vector());
    }
    return new_frame;
}

std::vector<DataFrame> DataFrame::split(int split_column, double split_threshold, bool equal_goes_left) const
{
    /**
     * Returns a pair of tables (value above and below split_threshold in specified column).
     * Values equal to the threshold go left if equal_goes_left==true and right otherwise.
     */
    DataFrame left = DataFrame();
    DataFrame right = DataFrame();
    for (int i = 0; i < this->length(); i++)
    {
        DataVector* row = this->row(i);
        double split_val = row->value(split_column);
        if (split_val<split_threshold) {
            left.addRow(row);
        } else if (split_val>split_threshold) {
            right.addRow(row);
        } else if (equal_goes_left) {
            left.addRow(row);
        } else if (!equal_goes_left) {
            right.addRow(row);
        }
    }
    std::vector<DataFrame> results = { left, right };
    return results;
}

std::vector<DataFrame> DataFrame::train_test_split(double split_pct) const
{
    /**
     * Returns a pair of train/test tables (sized using split_pct).
     * Calculates table sizes from val_split percent.
     */

    assert (split_pct >= 0 && split_pct <= 1)

    // length of dataframe. assert non-empty.
    nrows = this->length();
    assert(nrows > 0);

    // length of train dataframe
    int len_train = int (nrows * split_pct) // Always rounds down

    // length of test dataframe
    int len_test = int (nrows - len_train)

    // initialize new dataframes
    DataFrame left = DataFrame();  // Train
    DataFrame right = DataFrame(); // Test

    for (int i = 0; i < nrows; i++)
    {
        DataVector* row = this->row(i);
        if (i < len_train) {
            left.addRow(row);
        } else if (i >= len_train) {
            right.addRow(row);
    }

    // validate test size
    assert (right.size()==len_test);

    std::vector<DataFrame> results = { left, right };
    return results;
}

std::string DataFrame::to_string(bool new_line, int col_width) const
{
    /**
     * Returns a string representation of the dataframe.
     * Truncated or padded to the specified column width.
     **/
    std::string out = "";
    for (int i = 0; i < this->length(); i++)
    {
        out += this->row(i)->to_string(false, col_width);  // new_line==false.
    }
    // Add (optional) extra newline character:
    if (new_line)
    {
        out += '\n';
    }
    return out;
}

void DataFrame::print(bool new_line, int col_width) const
{
    /**
     * Prints a string representation of the dataframe.
     * Truncated or padded to the specified column width.
     **/
    std::cout << this->to_string(new_line, col_width);
}


/*
 * DATA FRAME - I/O :
 */


std::ostream& operator<<(std::ostream& os, const DataFrame& dataframe)
{
    /**
     * Sends a string representation of the dataframe to the output stream.
     * Truncated or padded to the specified column width.
     **/
    os << dataframe.to_string(false);  // Don't add extra newline character.
    return os;
}


/*
 * DATA FRAME - CONSTRUCTORS :
 */


DataFrame::DataFrame()
{
    this->is_locked_ = false;
    this->width_ = 0;
    this->length_ = 0;
}

DataFrame::DataFrame(std::vector<std::vector<double>> matrix)
{
    this->is_locked_ = false;
    this->length_ = 0;  // Will be incremented below.
    if (matrix.size()>0){
        this->width_ = matrix[0].size();
    } else {
        this->width_ = 0;
    }
    for (int i = 0; i < matrix.size(); i++)
    {
        assert (matrix[i].size()==this->width());
        this->addRow(matrix[i]);
    }
}


/*
 * DATA LOADER - ACCESSORS :
 */


/*
 * DATA LOADER - UTILITES :
 */

DataFrame DataLoader::load()
{
    /** Returns the loaded frame. */
    return this->dataframe_;
}


/*
 * DATA LOADER - CONSTRUCTORS :
 */


DataLoader::DataLoader()
{
    /** Load hard-coded dummy dataset. */
    std::vector<std::vector<double>> matrix = {
        {2.7810836,2.550537003,0},
        {1.465489372,2.362125076,0},
        {7.627531214,2.759262235,1},
        {3.396561688,4.400293529,0},
        {8.675418651,-0.242068655,1},
        {1.38807019,1.850220317,0},
        {3.06407232,3.005305973,0},
        {5.332441248,2.088626775,1},
        {6.922596716,1.77106367,1},
        {7.673756466,3.508563011,1},
        {7.673756466,3.301233593,1}
    };
    this->dataframe_ = DataFrame(matrix);
}

DataLoader::DataLoader(std::vector<std::vector<double>> matrix)
{
    /** Load dataset from vector of vectors. */
    this->dataframe_ = DataFrame(matrix);
}

DataLoader::DataLoader(std::string filename)
{
    /** Load dataset from CSV file at filename */
    std::string line;
    std::ifstream myfile(filename); // Open file as a stream

    // Check whether file is open
    if (myfile.is_open())
    {
        std::vector<std::vector<double>> df = {}; // Initialize a matrix
        std::vector<double> newrow; // Initialize a vector

        // Grab line from file stream
        while (std::getline(myfile, line))
        {
            newrow = {};

            // Create a string stream for current line
            std::stringstream line_stream(line);

            // Check whether line stream still has remaining elements
            while (line_stream.good()) {

                // Save column value as string
                std::string column_value;
                std::getline(line_stream, column_value, ',');

                // Convert column value to double
                double column_val;
                column_val = std::stod(column_value);

                // Append column value to vector
                newrow.push_back(column_val);

            }

            // Append vector to matrix
            df.push_back(newrow);

        }

        // Save matrix as DataFrame
        this->dataframe_ = df;
        myfile.close();

    }

    else std::cout << "Unable to open file";

}

/*
 * SEED GENERATOR - UTILITES :
 */

int SeedGenerator::new_seed()
{
    /**
     * Obtain a new non-negative integer seed
     * (returns -1 if SeedGenerator is in non-deterministic mode).
     */
    if (this->meta_seed_==-1) {
        return -1;
    } else {
        return -1;  // PLACEHOLDER.
    }
}

/*
 * SEED GENERATOR - CONSTRUCTORS :
 */

SeedGenerator::SeedGenerator(int meta_seed)
{
    /**
     * Construct a SeedGenerator to obtain pseudo-random seeds.
     * Set meta_seed to -1 for non-deterministic sequence,
     * or non-negative for repeatable sequence.
     */
    assert (meta_seed>=-1);
    this->meta_seed_ = meta_seed;
}
