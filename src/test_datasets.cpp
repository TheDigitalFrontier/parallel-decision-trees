#include <iostream>
#include "datasets.cpp"


int main(){

    DataLoader df_test_loader = DataLoader();  // Load test data.
    DataFrame df_test = df_test_loader.load();

    // Print as built-in print method:
    df_test.print(9);  // Optionally specify colwidth.

    // Print with overloaded stream operator:
    std::cout << df_test << std::endl;

    // Get last row:
    DataVector* test_row = df_test.row(-1);
    std::cout << *test_row << std::endl;

    // Get last column:
    DataVector* test_col = df_test.col(-1);
    std::cout << *test_col << std::endl;

};