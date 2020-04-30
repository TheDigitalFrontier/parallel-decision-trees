#include <iostream>
#include "datasets.cpp"


int main(){

    DataLoader df_test_loader = DataLoader();  // Load test data.
    DataFrame df_test = df_test_loader.load();

    df_test.print(9);  // Optionally specify colwidth.

    std::cout << df_test << std::endl;

    /*
    DataCol *test_col = df_test.col(1);
    for (int r = 0; r < df_test.length(); r++)
    {
        double value = test_col->cell(r)->value();
        std::cout << value << " | ";
    }
    */

};