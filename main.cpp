#include <iostream>
#include <cmath>
#include <ctime>
#include "lab6.h"

#include <cstddef>

template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0, const T& value = T()) :
            size_(size),
            data_((T *)malloc(size_ * sizeof(T))) {
        for (int i = 0; i < size_; ++i)
            new (data_ + i) T(value);
    }
    Array(const Array& other) :
            size_(other.size_),
            data_((T *)malloc(size_ * sizeof(T))) {
        for (int i = 0; i < size_; ++i)
            new (data_ + i) T(other.data_[i]);
    }
    ~Array() {
        for (int i = 0; i < size_; ++i)
            data_[i].~T();
        free(data_);
    }
    Array& operator=(Array const &other) {
        if (&other == this)
            return *this;

        size_ = other.size_;
        data_ = (T *)malloc(size_ * sizeof(T));
        for (int i = 0; i < size_; ++i)
            new (data_ + i) T(other.data_[i]);

        return *this;
    }
    size_t size() const {
        return size_;
    }
    T& operator[](size_t idx) {
        return data_[idx];
    }
    const T& operator[](size_t idx) const {
        return data_[idx];
    }

    void none() {
        std::cout << "4" << std::endl;
    }

private:
    size_t size_;
    T *data_;
};

bool less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) const { return b < a; } };

template <typename T, class Comp>
T minimum(Array<T> const & arr, Comp compare)  {
    T min = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        if (compare(arr[i], min))
            min = arr[i];
    }
    return min;
}

int main() {

    Array<int> ints(3);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;
    int min = minimum(ints, less); // в min должно попасть число 2
    int max = minimum(ints, Greater()); // в max должно попасть число 15


    return 0;
}