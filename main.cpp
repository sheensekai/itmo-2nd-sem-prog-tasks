#include <iostream>
#include <cmath>
#include <ctime>
#include "lab5.h"

int main() {

    // Инициализация через консольку

    CCircle first(3.5, {0, 2}, 25);
    first.Draw();
    std::cout << std::endl;

    first.SetMass(30);
    first.SetRad(13.2);
    first.SetPosition({27.3, 19.2});
    first.SetClassName("New Name");
    first.Draw();
    std::cout << std::endl;

    CCircle etf(1, {0, 0}, 30); // equal_to_first
    CCircle mtf(1, {0, 0}, 35); // more_than_first
    CCircle ltf(1, {0, 0}, 25); // less_than_first

    std::cout << (etf == first) << " " << (etf != first) << " " << (etf < first) << " " << (etf > first) << std::endl;
    std::cout << (mtf == first) << " " << (mtf != first) << " " << (mtf < first) << " " << (mtf > first) << std::endl;
    std::cout << (ltf == first) << " " << (ltf != first) << " " << (ltf < first) << " " << (ltf > first) << std::endl;

    std::cout << std::endl;

    CCircleSystem sys;
    sys.AddCircle(first);
    sys.AddCircle(etf);
    sys.AddCircle(ltf);
    sys.AddCircle(5, {12, 24}, 100);

    sys.ShowCircles();
    sys.Draw();
    sys.Edit();

    return 0;
}