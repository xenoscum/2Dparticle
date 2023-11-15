#include "Model.cpp"
#include "density_init_functions.cpp"
#include <iostream>

int main() {
    Model model(10, 0.1, densInit1, Model::oneDimensional, 1.0);
    
    std::cout << "ok\n";
    return 0;
}