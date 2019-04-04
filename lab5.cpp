#include "lab5.h"

CVector2D &CVector2D::operator+=(CVector2D const &other) {
    x += other.x;
    y += other.y;
    return *this;
}

CVector2D &CVector2D::operator*=(double val) {
    x *= val;
    y *= val;
    return *this;
}

CVector2D &CVector2D::operator/=(double val) {
    x /= val;
    y /= val;
    return *this;
}

CVector2D operator*(CVector2D lhs, double val) {
    lhs *= val;
    return lhs;
}

CVector2D operator/(CVector2D lhs, double val) {
    lhs /= val;
    return lhs;
}

CVector2D operator+(CVector2D lhs, CVector2D const &other) {
    lhs += other;
    return lhs;
}

CCircle::CCircle(double rad, CVector2D const &centre, double mass) :
        rad_(rad),
        centre_(centre),
        size_(sizeof(CCircle)),
        name_("Nameless"),
        mass_(mass) {}

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
    std::cout << "Centre pos: " << centre_.x << " " << centre_.y << std::endl;
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

void CCircleSystem::AddCircle(double rad, CVector2D const &centre, double mass) {
    if (head_ >= size_ * 0.7) {
        CCircle *tmp = new CCircle[int(floor(size_ * 1.))];
        for (int i = 0; i < size_; ++i)
            tmp[i] = arr_[i];
        delete[] arr_;
    }



    arr_[head_].SetPosition(centre);
    arr_[head_].SetRad(rad);
    arr_[head_].SetMass(mass);

    ++head_;
}

void CCircleSystem::ShowCircles() {
    for (int i = 0; i < head_; ++i)
        arr_[i].Draw();
}

double CCircleSystem::CiclesTotalSquare() {
    double square = 0;
    for (int i = 0; i < head_; ++i)
        square += arr_[i].Square();
    return square;
}

double CCircleSystem::CirclesTotalPerimeter() {
    double perimeter = 0;
    for (int i = 0; i < head_; ++i)
        perimeter += arr_[i].Square();
    return perimeter;
}

double CCircleSystem::CirclesTotalMass() {
    double mass = 0;
    for (int i = 0; i < head_; ++i)
        mass += arr_[head_].Mass();
    return mass;
}

CVector2D CCircleSystem::CirclesMassCentre() {
    CVector2D mass_centre;
    for (int i = 0; i < head_; ++i)
        mass_centre += arr_[head_].Position() * arr_[head_].Mass();
    mass_centre /= CirclesTotalMass();
    return mass_centre;
}

size_t CCircleSystem::CircleTotalSize() {
    size_t total_size = 0;
    for (int i = 0; i < head_; ++i)
        total_size += arr_[head_].Size();
    return total_size;
}

void CCircleSystem::CirclesMassSort() {
    CirclesMergeSort(1, size_);
}

void CCircleSystem::CirclesMergeSort(int first, int last) {
    if (first < last) {
        CirclesMergeSort(first, (first + last) / 2);
        CirclesMergeSort((first + last) / 2 + 1, last);
        CirclesMerge(first, last, (first + last) / 2 + 1);
    }
}

void CCircleSystem::CirclesMerge(int first, int last, int middle) {
    CCircle left[middle - first];
    for (int k = 0; k < middle - first; k++)
        left[k] = arr_[first + k - 1];

    std::printf("Hello");

    CCircle right[last - middle + 1];
    for (int k = 0; k < last - middle + 1; k++)
        right[k] = arr_[middle + k - 1];

    int i = 0, j = 0, k = first;
    // тут чет не ок
    while (i < middle - first && j < last - middle + 1)
        arr_[k++ - 1] = left[i] <= right[j] ? left[i++] : right[j++];
    while (k <= last)
        arr_[k++ - 1] = i >= middle - first ? right[j++] : left[i++];
}