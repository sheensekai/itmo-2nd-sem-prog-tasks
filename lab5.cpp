#include "lab5.h"


CCircle::CCircle(double rad, CVector2D const &centre) :
        rad_(rad),
        centre_(centre),
        size_(sizeof(CCircle)),
        name_("Nameless") {}


void CCircle::InitFromDialog() {
    std::cout << "Enter circle radius: " << std::endl;
    std::cin >> rad_;
    std::cout << "Enter circle centre's x and y coords: " << std::endl;
    std::cin >> centre_.x >> centre_.y;
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
    std::cout << "Object mass: " << mass_ << " " << std::endl;
    std::cout << std::endl;
}

double CCircle::Square() const {
    return M_PI * rad_ * rad_;
}

double CCircle::Perimeter() const {
    return 2.0 * M_PI * rad_;
}

void CCircle::SetRad(double rad) {
    rad_ = rad;
}

double CCircle::Mass() const {
    return mass_;
}

CVector2D CCircle::Position() const {
    return centre_;
}

void CCircle::SetMass(double val) {
    mass_ = val;
}

void CCircle::SetPosition(const CVector2D &vect) {
    centre_ = vect;
}

bool CCircle::operator==(const IPhysObject &ob) const {
    return mass_ == ob.Mass();
}

bool CCircle::operator!=(const IPhysObject &ob) const {
    return mass_ != ob.Mass();
}

bool CCircle::operator<(const IPhysObject &ob) const {
    return mass_ < ob.Mass();
}

bool CCircle::operator>(const IPhysObject &ob) const {
    return mass_ > ob.Mass();
}

bool CCircle::operator<=(const IPhysObject &ob) const {
    return mass_ <= ob.Mass();
}

bool CCircle::operator>=(const IPhysObject &ob) const {
    return mass_ >= ob.Mass();

}



