#include <iostream>
#include "datasets.cpp"


int main(){

    DataLoader df_test_loader = DataLoader();  // Load test data.
    DataFrame df_test = df_test_loader.load();

    for (int r = 0; r < df_test.length(); r++)
    {
        std::cout << "| ";
        for (int c = 0; c < df_test.width(); c++)
        {
            double value = df_test.value(r,c);
            std::cout << value << " | ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    /*
    DataCol *test_col = df_test.col(1);
    for (int r = 0; r < df_test.length(); r++)
    {
        double value = test_col->cell(r)->value();
        std::cout << value << " | ";
    }
    */

};