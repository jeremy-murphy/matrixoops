#include "matrix.hpp"

#include <iostream>

using namespace OOPS;

int main()
{
    using Matrix2x3 = Matrix<int, 2, 3>;
    Matrix2x3 m1, m2;
    
    m1.empty();
    m2.empty();

    
    m1.setElement(0, 0, 10);
    m1.setElement(0, 1, 20);
    m1.setElement(0, 2, 30);
    m1.setElement(1, 0, 40);
    m1.setElement(1, 1, 50);
    m1.setElement(1, 2, 60);
    m2.setElement(0, 0, 30);
    m2.setElement(0, 1, 50);
    m2.setElement(0, 2, 70);
    m2.setElement(1, 0, 10);
    m2.setElement(1, 1, 60);
    m2.setElement(1, 2, 90);

    std::cout << "Matrix m1 is \n";
    std::cout << m1 << "\n";

    std::cout << "Matrix m2 is \n";
    std::cout << m2 << "\n";
    
    std::cout << "m1 equals m1: " << std::boolalpha << (m1 == m1) << "\n\n";
    std::cout << "m1 equals m2: " << std::boolalpha << (m1 == m2) << "\n\n";
    
    std::cout << "m1 + m2 equals\n";
    std::cout << m1 + m2;
}
