#include <iostream>
#include "datasets.cpp"


int main(){

    DataLoader df_test_loader = DataLoader();  // Load test data.
    DataFrame df_test = df_test_loader.load();

    // Print as print method:
    std::cout << "Print test dataframe (with print method):" << std::endl;
    df_test.print(4);  // Optionally specify colwidth (truncates if too long).

    // Print with overloaded stream operator:
    std::cout << "Print test dataframe (with overloaded steam operator):" << std::endl;
    std::cout << df_test << std::endl;

    // Get last row:
    std::cout << "Print last row:" << std::endl;
    DataVector* test_row = df_test.row(-1);
    std::cout << *test_row << std::endl;

    // Get last column:
    std::cout << "Print last column:" << std::endl;
    DataVector* test_col = df_test.col(-1);
    std::cout << *test_col << std::endl;
    
    // Get transpose of first column:
    std::cout << "Print transpose of first column:" << std::endl;
    DataVector* test_transpose = df_test.col(0)->transpose();
    std::cout << *test_transpose << std::endl;

};