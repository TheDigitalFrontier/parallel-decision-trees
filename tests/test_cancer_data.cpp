#include <iostream>
#include "../src/datasets.cpp"

int main(){

    DataLoader csv_loader = DataLoader("../data/classification_cancer.csv");  // Load CSV test data.
    DataFrame csv_test = csv_loader.load();
    // csv_test.print();
    DataVector* test_row = csv_test.row(-1);
    std::cout << *test_row << std::endl;
    
};