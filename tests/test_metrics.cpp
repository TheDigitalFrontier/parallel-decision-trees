#include <iostream>
#include "../src/datasets.cpp"
#include "../src/metrics.cpp"

int main(){

    DataLoader df_test_loader = DataLoader();  // Load test data.
    DataFrame df_test = df_test_loader.load();

    DataLoader csv_loader = DataLoader("../data/sonar.all-data_temp.csv");  // Load CSV test data.
    DataFrame csv_test = csv_loader.load();

    // Print as print method:
    std::cout << "Print test dataframe (with print method):" << std::endl;
    df_test.print(4);

    // Get copy of last column:
    std::cout << "Print last column:" << std::endl;
    DataVector targets = df_test.col(-1).copy();
    std::cout << targets << std::endl;
    
};