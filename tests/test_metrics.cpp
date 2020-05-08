#include <iostream>
#include "../src/datasets.cpp"
#include "../src/metrics.cpp"

int main(){
    DataLoader df_test_loader = DataLoader();  // Load test data.
    DataFrame df_test = df_test_loader.load();
    
    // Get copy of last column:
    std::cout << "Print last column:" << std::endl;
    DataVector targets = df_test.col(-1).copy();
    std::cout << targets << std::endl;
    
    // Test accuracy calculation
    std::cout << "Accuracy of same vector twice:" << std::endl;
    std::cout << accuracy(targets, targets) << std::endl;
    std::cout << "\nContrived 54.54% (recurring) accuracy:" << std::endl;
    std::cout << accuracy(targets, DataVector {{0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0}}) << std::endl;
};