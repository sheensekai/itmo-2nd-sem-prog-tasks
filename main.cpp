#include <iostream>
#include <cmath>
#include <ctime>
#include "lab5.h"

int main() {

    CCircle first;
    first.SetMass(10);
    CCircle second;
    second.SetMass(20);
    std::cout << (first < second);

    return 0;
}