#include "lab2.h"

double triangle::area() {
    double a = pow(pow(this->b.x - this->a.x, 2.0) + pow(this->b.y - this->a.y, 2.0), 0.5);
    double b = pow(pow(this->c.x - this->b.x, 2.0) + pow(this->c.y - this->b.y, 2.0), 0.5);
    double c = pow(pow(this->a.x - this->c.x, 2.0) + pow(this->a.y - this->c.y, 2.0), 0.5);
    double p = (a + b + c) / 2.0;

    return pow(p * (p - a) * (p - b) * (p - c), 0.5);
}

bool triangle::operator == (triangle right) {
    return this->area() == right.area();
}

bool triangle::operator != (triangle right) {
    return this->area() != right.area();
}

bool triangle::operator > (triangle right) {
    return this->area() > right.area();
}

bool triangle::operator < (triangle right) {
    return this->area() < right.area();
}

IntArray::IntArray() : size(0), arr(new int[0]) {}
IntArray::IntArray(int size)  {
    if (size > 0)
        this->size = size;
    else this->size = 0;

    this->arr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        arr[i] = 0;
}
IntArray::~IntArray() {
    delete[] arr;
}

IntArray IntArray::operator + (IntArray const & right) {
    IntArray res_arr;
    res_arr.size = this->size + right.size;
    res_arr.arr = new int[res_arr.size];

    for (int i = 0; i < this->size; i++)
        res_arr.arr[i] = this->arr[i];
    for (int i = 0; i < right.size; i++)
        res_arr.arr[i + this->size] = right.arr[i];

    return res_arr;
}

IntArray & IntArray::operator = (IntArray const & right) {
    delete[] this->arr;

    this->size = right.size;
    this->arr = new int[this->size];
    for (int i = 0; i < this->size; i++)
        this->arr[i] = right.arr[i];

    return *this;
}

int & IntArray::get(int pos) {
    if (pos > 0)
        return this->arr[pos];
    else return this->arr[0];
}

int IntArray::length() {
    return size;
}

bool IntArray::operator == (IntArray const & right) {
    return this->size == right.size;
}
bool IntArray::operator != (IntArray const & right) {
    return this->size != right.size;
}
bool IntArray::operator < (IntArray const & right) {
    return this->size < right.size;
}
bool IntArray::operator > (IntArray const & right) {
    return this->size > right.size;
}