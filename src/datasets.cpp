#include "datasets.hpp"
#include <vector>
#include <assert.h>


/*
 * DATA CELL - ACCESSORS :
 */


double DataCell::value()
{
    /** Returns the value (double) in a cell. */
    return this->value_;
}


/*
 * DATA CELL - UTILITES :
 */


void DataCell::lock()
{
    /** Prevent unwanted changes to data. */
    this->locked_ = true;
}


/*
 * DATA CELL - CONSTRUCTORS :
 */


DataCell::DataCell()
{
    /** Create cell without assigning value. */
    this->locked_ = false;
}

DataCell::DataCell(double value)
{
    /** Create cell with value */
    this->locked_ = false;
    this->value_ = value;
}


/*
 * DATA ROW - ACCESSORS :
 */


int DataRow::width()
{
    /** Returns the number of columns (cells) in the row. */
    return this->width_;
}

DataCell *DataRow::cell(int c)
{
    /** Get cell in given column (positive or negative index). */
    if (c>=0)
    {
        // Index from beginning (positive):
        assert ( c<this->width() );
    } else {
        // Index from end (negative):
        assert ( c>=-this->width() );
        c += this->width();
    }
    return &this->cells_[ c ];
}


/*
 * DATA ROW - UTILITES :
 */


void DataRow::lock()
{
    /** Prevent unwanted changes to data. */
    this->locked_ = true;
}

void DataRow::addCell(DataCell *cell)
{
    /** Adds a cell to a row. */
    //assert (this->locked_==false);
    this->cells_.push_back(*cell);
    this->width_ += 1;
}


/*
 * DATA ROW - CONSTRUCTORS :
 */


DataRow::DataRow()
{
    this->locked_ = false;
    this->width_ = 0;
}

DataRow::DataRow(std::vector<double> vector)
{
    this->locked_ = false;
    this->width_ = vector.size();
    for (int c = 0; c < vector.size(); c++)
    {
        double value = vector[c];
        DataCell datacell = DataCell(value);
        //datacell.lock();
        this->addCell(&datacell);
    }
    //this->lock();
}

void DataRow::lock_all()
{
    /** Prevent unwanted changes to data. */
    this->locked_ = true;
    // Lock cells:
    for (int c = 0; c < this->width_; c++)
    {
        this->cells_[c].lock();
    }
}



/*
 * DATA COL - ACCESSORS :
 */


int DataCol::length()
{
    /** Returns the number of rows (cells) in the column. */
    return this->length_;
}

DataCell *DataCol::cell(int r)
{
    /** Get cell in given row (positive or negative index). */
    if (r>=0)
    {
        // Index from beginning (positive):
        assert ( r<this->length() );
    } else {
        // Index from end (negative):
        assert ( r>=-this->length() );
        r += this->length();
    }
    return &this->cells_[ r ];
}


/*
 * DATA COL - UTILITES :
 */


void DataCol::lock()
{
    /** Prevent unwanted changes to data. */
    this->locked_ = true;
}

void DataCol::lock_all()
{
    /** Prevent unwanted changes to data. */
    this->locked_ = true;
    // Lock cells:
    for (int r = 0; r < this->length_; r++)
    {
        this->cells_[r].lock();
    }
}

void DataCol::addCell(DataCell *cell)
{
    /** Adds a cell to a row. */
    //assert (this->locked_==false);
    this->cells_.push_back(*cell);
    this->length_ += 1;
}


/*
 * DATA COL - CONSTRUCTORS :
 */


DataCol::DataCol()
{
    this->locked_ = false;
    this->length_ = 0;
}

DataCol::DataCol(std::vector<double> vector)
{
    this->locked_ = false;
    this->length_ = vector.size();
    for (int r = 0; r < vector.size(); r++)
    {
        double value = vector[r];
        DataCell datacell = DataCell(value);
        //datacell.lock();
        this->addCell(&datacell);
    }
    //this->lock();
}


/*
 * DATA FRAME - ACCESSORS :
 */


int DataFrame::length()
{
    /** Returns the number of rows in the frame. */
    return this->length_;
}

int DataFrame::width()
{
    /** Returns the number of columns in the frame. */
    return this->width_;
}

DataRow *DataFrame::row(int r)
{
    /** Get given row (positive or negative index). */
    if (r>=0)
    {
        // Index from beginning (positive):
        assert ( r<this->length() );
    } else {
        // Index from end (negative):
        assert ( r>=-this->length() );
        r += this->length();
    }
    return &this->rows_[ r ];
}

DataCol *DataFrame::col(int c)
{
    /** Get given column (positive or negative index). */
    if (c>=0)
    {
        // Index from beginning (positive):
        assert ( c<this->width() );
    } else {
        // Index from end (negative):
        assert ( c>=-this->width() );
        c += this->width();
    }
    return &this->cols_[ c ];
}

DataCell *DataFrame::cell(int r, int c)
{
    /** Get value in given row and column. */
    DataRow *datarow = this->row(r);
    DataCell *datacell = datarow->cell(c);
    return datacell;
}


/*
 * DATA FRAME - UTILITES :
 */


void DataFrame::lock()
{
    /** Prevent unwanted changes to data. */
    this->locked_ = true;
}

void DataFrame::lock_all()
{
    /** Prevent unwanted changes to data. */
    this->locked_ = true;
    // Lock rows:
    for (int r = 0; r < this->length_; r++)
    {
        this->rows_[r].lock_all();
    }
    // Lock columns:
    for (int c = 0; c < this->width_; c++)
    {
        this->cols_[c].lock_all();
    }
}

void DataFrame::addRow(DataRow *row)
{
    /** Adds a row to a frame. */
    //assert (this->locked_==false);
    // Add new row to row list:
    this->rows_.push_back(*row);
    // Add each new value to column list:
    for (int r = 0; r < row->width(); r++)
    {
        this->cols_[r].addCell( row->cell(r) );
    }
}

void DataFrame::addCol(DataCol *col)
{
    /** Adds a row to a frame. */
    //assert (this->locked_==false);
    // Add new column to column list:
    this->cols_.push_back(*col);
    // Add each new value to row list:
    for (int c = 0; c < col->length(); c++)
    {
        this->cols_[c].addCell( col->cell(c) );
    }
}


/*
 * DATA FRAME - CONSTRUCTORS :
 */


DataFrame::DataFrame()
{
    this->locked_ = false;
    this->width_ = 0;
    this->length_ = 0;
}

DataFrame::DataFrame(std::vector<std::vector<double>> matrix)
{
    this->locked_ = false;
    this->length_ = matrix.size();
    if (matrix.size()>0){
        this->width_ = matrix[0].size();
    } else {
        this->width_ = 0;
    }
    for (int r = 0; r < this->length_; r++)
    {
        this->rows_.push_back( DataRow() );
        assert (matrix[r].size()==this->width_);
        for (int c = 0; c < this->width_; c++)
        {
            if (r==0){
                this->cols_.push_back( DataCol() );
            }
            double value = matrix[r][c];
            DataCell datacell = DataCell(value);
            //datacell.lock();
            this->rows_[r].addCell(&datacell);
            this->cols_[c].addCell(&datacell);
        }
    }
    //this->lock();
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
