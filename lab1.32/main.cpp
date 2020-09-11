#include <iostream>
#include "lab1.32.h"

using namespace lab1;

int main() {
    Matrix matrix = Matrix();
    matrix = input();
    std::cout<<matrix;

    matrix.Matrix::createVector();

    return 0;
}

