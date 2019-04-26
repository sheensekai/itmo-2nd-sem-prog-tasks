#include <cstdio>
#include <string>
#include <iostream>

class MyStackException {
public:
    MyStackException(int size, int maxsize) {
        if (size > maxsize) {
            error_ = 0;
            what_ = "Stack Overflow";
        } else if (size < 0) {
            error_ = 1;
            what_ = "Stack Underflow";
        }
    }

    std::string what_;
    int error_; // 0 - overflow, 1 - underflow
};

template<int N, typename T>
class CStack {
public:
    CStack() :
            maxsize_(size_t(N)),
            size_(0),
            data_(new T[maxsize_]) {}

    int push(T const &val) {

        try {
            ++size_;
            if (size_ > maxsize_)
                throw MyStackException(size_, maxsize_);
            data_[size_ - 1] = val;
            return 1;
        }

        catch (MyStackException const &exc) {
            std::cerr << exc.what_ << std::endl;
            if (exc.error_ == 0)
                size_ = maxsize_;
            else if (exc.error_ == 1)
                size_ = 0;
            return 0;
        }
    }

    T pop() {
        try {
            --size_;
            if (size_ < 0)
                throw MyStackException(size_, maxsize_);
            return data_[size_];
        }

        catch (MyStackException const &exc) {
            std::cerr << exc.what_ << std::endl;
            if (exc.error_ == 0)
                size_ = maxsize_;
            else if (exc.error_ == 1)
                size_ = 0;

            return T{};
        }

    }

private:
    size_t maxsize_;
    int size_;
    T *data_;

};