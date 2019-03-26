#include "lab5.h"


CCircle::CCircle(double rad, CVector2D const &centre) :
        rad_(rad),
        centre_(centre),
        size_(sizeof(CCircle)),
        name_("Nameless") {}


CCircle::CCircle() {
    InitFromDialog();
}

void CCircle::InitFromDialog() {
    std::cout << "Enter circle radius: ";
    double rad;
    std::cin >> rad;
    std::cout << "Enter circle centre's x and y coords: "
    CVector2D vect;
    std::cin >> vect.x >> vect.y;
    CCircle(rad, vect);
}

const char *CCircle::ClassName() const {
    return name_.c_str();
}

void CCircle::SetClassName(std::string name) {
   name_ = name;
}

size_t CCircle::Size() const {
    return size_;
}

void CCircle::Draw() const {
    std::cout << "Object name: " << name_ << std::endl;
    std::cout << "Object size " << size_ << std::endl;
    std::cout << "Circle radius: " << rad_ << std::endl;
    std::cout << "Centre pos: " << centre_.x << " " << centre_.y  << std::endl;
}

double CCircle::Square() {
    return M_PI * rad_ * rad_;
}

double CCircle::Perimeter() {
    return 2.0 * M_PI * rad_;
}




