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

CCircle::CCircle(double rad, CVector2D const &centre, double mass, std::string const &name) :
        rad_(rad),
        centre_(centre),
        size_(sizeof(CCircle)),
        name_(name),
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
    std::cout << "Class Type: " << name_ << std::endl;
    std::cout << "Class Size: " << size_ << std::endl;
    std::cout << "Object mass: " << mass_ << " " << std::endl;
    std::cout << "Object Square = " << Square() << std::endl;
    std::cout << "Circle radius: " << rad_ << std::endl;
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

double CCircle::Radius() const {
    return rad_;
}

void CCircleSystem::AddCircle(double rad, CVector2D const &centre, double mass, std::string const &name) {
    if (head_ >= size_ * 0.7) {
        CCircle *tmp = new CCircle[int(floor(size_ * 1.))];
        for (int i = 0; i < size_; ++i)
            tmp[i] = arr_[i];
        delete[] arr_;
    }

    arr_[head_].SetPosition(centre);
    arr_[head_].SetRad(rad);
    arr_[head_].SetMass(mass);
    arr_[head_].SetClassName(name);

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
        mass += arr_[i].Mass();
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

    CCircle right[last - middle + 1];
    for (int k = 0; k < last - middle + 1; k++)
        right[k] = arr_[middle + k - 1];

    int i = 0, j = 0, k = first;
    while (i < middle - first && j < last - middle + 1)
        arr_[k++ - 1] = left[i] <= right[j] ? left[i++] : right[j++];
    while (k <= last)
        arr_[k++ - 1] = i >= middle - first ? right[j++] : left[i++];
}

void CCircleSystem::AddCircle(CCircle const &circle) {
    AddCircle(circle.Radius(), circle.Position(), circle.Mass(), circle.ClassName());
}

void CCircleSystem::Draw() {
    std::cout << "Class Type: Circles System" << std::endl;
    std::cout << "Class Size: " << CircleTotalSize() << std::endl;
    std::cout << "Object mass: " << CirclesTotalMass() << " " << std::endl;
    CVector2D const &centre = CirclesMassCentre();
    std::cout << "Objects centre of mass: " << centre.x << " " << centre.y << std::endl;
    std::cout << "Object Square = " << CiclesTotalSquare() << std::endl;
    std::cout << "Objects Perimeters = " << CirclesTotalPerimeter() << std::endl;
    std::cout << "Objects Radius = " << CirclesTotalRadius() << std::endl;

    std::cout << std::endl;
}

double CCircleSystem::CirclesTotalRadius() {
    double total_radius = 0;
    for (int i = 0; i < head_; ++i)
        total_radius += arr_[i].Radius();
    return total_radius;
}

void CCircleSystem::ShowCirclesMasses() {
    for (int i = 0; i < head_; ++i)
        std::cout << arr_[i].Mass() << " ";
    std::cout << std::endl;
}

void CCircleSystem::Edit() {
    std::string buffer;
    std::cin >> buffer;
    double mass = 0;
    CVector2D centre = {0, 0};
    while (buffer != "exit") {

        if (buffer == "add") {
            std::cin >> mass >> centre.x >> centre.y;
            AddCircle(0, centre, mass);
        } else if (buffer == "show-mass") {
            ShowCirclesMasses();
        } else if (buffer == "show-full") {
            ShowCircles();
        } else if (buffer == "sort") {
            CirclesMergeSort(1, head_);
        }

        std::cin >> buffer;
    }
}

CParalgram::CParalgram(double side1, double side2, CVector2D pos, double angle, double mass, std::string name) :
        side1_(side1),
        side2_(side2),
        pos_(pos),
        angle_(angle),
        mass_(mass),
        size_(sizeof(CParalgram)),
        name_(name) {}

size_t CParalgram::Size() const {
    return size_;
}

const char *CParalgram::ClassName() const {
    return name_.c_str();
}

void CParalgram::SetClassName(std::string name) {
    name_ = name;
}

void CParalgram::InitFromDialog() {
    std::cout << "Enter first and second sides" << std::endl;
    std::cin >> side1_ >> side2_;
    std::cout << "Enter x and y position of |_ corner" << std::endl;
    std::cin >> pos_.x >> pos_.y;
    std::cout << "Enter angle of |_ corner" << std::endl;
    std::cin >> angle_;
}

void CParalgram::SetSide1(double val) {
    side1_ = val;
}

void CParalgram::SetSide2(double val) {
    side2_ = val;
}

double CParalgram::Mass() const {
    return mass_;
}

double CParalgram::Side1() const {
    return side1_;
}

double CParalgram::Side2() const {
    return side1_;
}

void CParalgram::SetMass(double val) {
    mass_ = val;
}

CVector2D CParalgram::Position() const {
    return pos_;
}

void CParalgram::SetPosition(const CVector2D &vect) {
    pos_ = vect;
}

void CParalgram::Draw() const {
    std::cout << "Class Type: " << name_ << std::endl;
    std::cout << "Class Size: " << size_ << std::endl;
    std::cout << "Object mass: " << mass_ << " " << std::endl;
    std::cout << "Object Square = " << Square() << std::endl;
    std::cout << "Parallelogram sides: " << side1_ << " " << side2_ << std::endl;
    std::cout << "Parallelogram corner: " << pos_.x << " " << pos_.y << std::endl;
    std::cout << "Parallelogram corner angle: " << angle_ << std::endl;
    std::cout << std::endl;
}

double CParalgram::Square() const {
    return side1_ * side2_ * sin(angle_);
}

double CParalgram::Perimeter() const {
    return side1_ * 2 + side2_ * 2;
}

bool CParalgram::operator==(const IPhysObject &ob) const {
    return mass_ == ob.Mass();
}

bool CParalgram::operator!=(const IPhysObject &ob) const {
    return mass_ != ob.Mass();
}

bool CParalgram::operator<(const IPhysObject &ob) const {
    return mass_ < ob.Mass();
}

bool CParalgram::operator>(const IPhysObject &ob) const {
    return mass_ > ob.Mass();
}

bool CParalgram::operator<=(const IPhysObject &ob) const {
    return mass_ <= ob.Mass();
}

bool CParalgram::operator>=(const IPhysObject &ob) const {
    return mass_ >= ob.Mass();
}

void CParalgram::SetAngle(double val) {
    angle_ = val;
}

double CParalgram::Angle() const {
    return angle_;
}

void
CParalgramSystem::AddParalgram(double side1, double side2, CVector2D pos, double angle, double mass, std::string const &name) {
    if (head_ >= size_ * 0.7) {
        CParalgram *tmp = new CParalgram[int(floor(size_ * 1.))];
        for (int i = 0; i < size_; ++i)
            tmp[i] = arr_[i];
        delete[] arr_;
    }

    arr_[head_].SetPosition(pos);
    arr_[head_].SetSide1(side1);
    arr_[head_].SetSide2(side2);
    arr_[head_].SetMass(mass);
    arr_[head_].SetClassName(name);

    ++head_;
}

void CParalgramSystem::AddParalgram(CParalgram const &pgram) {
    AddParalgram(pgram.Side1(), pgram.Side2(), pgram.Position(), pgram.Angle(), pgram.Mass(), pgram.ClassName());
}

void CParalgramSystem::ShowParalgrams() {
    for (int i = 0; i < head_; ++i)
        arr_[i].Draw();
}

void CParalgramSystem::Draw() {
    std::cout << "Class Type: Parallelogram System" << std::endl;
    std::cout << "Class Size: " << ParalgramsTotalSize() << std::endl;
    std::cout << "Object mass: " << ParalgramsTotalMass() << " " << std::endl;
    CVector2D const &centre = ParalgramsMassCentre();
    std::cout << "Objects centre of mass: " << centre.x << " " << centre.y << std::endl;
    std::cout << "Object Square = " << ParalgramsTotalSquare() << std::endl;
    std::cout << "Objects Perimeters = " << ParalgramsTotalPerimeter() << std::endl;

    std::cout << std::endl;
}

double CParalgramSystem::ParalgramsTotalSquare() {
    double square = 0;
    for (int i = 0; i < head_; ++i)
        square += arr_[i].Square();
    return square;
}

double CParalgramSystem::ParalgramsTotalPerimeter() {
    double perimeter = 0;
    for (int i = 0; i < head_; ++i)
        perimeter += arr_[i].Perimeter();
    return perimeter;
}

double CParalgramSystem::ParalgramsTotalMass() {
    double mass = 0;
    for (int i = 0; i < head_; ++i)
        mass += arr_[i].Mass();
    return mass;
}

CVector2D CParalgramSystem::ParalgramsMassCentre() {
    CVector2D mass_centre;
    for (int i = 0; i < head_; ++i)
        mass_centre += arr_[head_].Position() * arr_[head_].Mass();
    mass_centre /= ParalgramsTotalMass();
    return mass_centre;
}

size_t CParalgramSystem::ParalgramsTotalSize() {
    size_t size = 0;
    for (int i = 0; i < head_; ++i)
        size += arr_[i].Size();
    return size;
}

void CParalgramSystem::ParalgramsMassSort() {
    ParalgramsMergeSort(1, size_);
}

void CParalgramSystem::ShowParalgramsMasses() {
    for (int i = 0; i < head_; ++i)
        std::cout << arr_[i].Mass() << " ";
    std::cout << std::endl;
}

void CParalgramSystem::ParalgramsMergeSort(int first, int last) {
    if (first < last) {
        ParalgramsMergeSort(first, (first + last) / 2);
        ParalgramsMergeSort((first + last) / 2 + 1, last);
        ParalgramsMerge(first, last, (first + last) / 2 + 1);
    }
}

void CParalgramSystem::ParalgramsMerge(int first, int last, int middle) {
    CParalgram left[middle - first];
    for (int k = 0; k < middle - first; k++)
        left[k] = arr_[first + k - 1];

    CParalgram right[last - middle + 1];
    for (int k = 0; k < last - middle + 1; k++)
        right[k] = arr_[middle + k - 1];

    int i = 0, j = 0, k = first;
    while (i < middle - first && j < last - middle + 1)
        arr_[k++ - 1] = left[i] <= right[j] ? left[i++] : right[j++];
    while (k <= last)
        arr_[k++ - 1] = i >= middle - first ? right[j++] : left[i++];
}

void CParalgramSystem::Edit() {
    std::string buffer;
    std::cin >> buffer;
    double mass = 0;
    double rad = 0;
    CVector2D centre = {0, 0};
    while (buffer != "exit") {

        if (buffer == "add") {
            std::cin >> mass >> centre.x >> centre.y;
            AddParalgram(0, 0, centre, 0, mass);
        } else if (buffer == "show-mass") {
            ShowParalgramsMasses();
        } else if (buffer == "show-full") {
            ShowParalgrams();
        } else if (buffer == "sort") {
            ParalgramsMergeSort(1, head_);
        }

        std::cin >> buffer;
    }
}
