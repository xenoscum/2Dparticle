#include "Model.h"
#include "density_init_functions.cpp"

#include <iostream>

int main() {
    //Model model(10, 0.1, densInit1, Model::oneDimensional, 1.0);

    Model model(100, 0.1, densInitParaboloid, Model::twoDimensional, 1.0);

    model.runFor(100);

    std::cout << "ok\n";
    return 0;
}