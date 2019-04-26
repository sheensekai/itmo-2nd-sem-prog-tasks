#ifndef PROGTASKSCPP_LAB10_H
#define PROGTASKSCPP_LAB10_H

#include <iterator>

template<typename ValueType>
class MyIterator;

template<typename Type>
class MyArray {
public:
    typedef MyIterator<Type> iterator;
    typedef MyIterator<Type const> const_iterator;

    MyArray() :
            size_(10),
            data_(new Type[size_]) {}

    iterator begin() {
        return MyIterator<Type>(&data_[0]);
    }

    iterator end() {
        return MyIterator<Type>(&data_[size_]);
    }

    const_iterator cbegin() const {
        return MyIterator<Type>(&data_[0]);
    }

    const_iterator cend() const {
        return MyIterator<Type>(&data_[size_]);

    }

private:
    size_t size_;
    Type *data_;
};

template<typename ValueType>
class MyIterator : public std::iterator<std::forward_iterator_tag, ValueType> {
    friend class MyArray<ValueType>;

private:
    explicit  MyIterator(ValueType *ptr) :
            ptr_(ptr) {}

public:
    MyIterator(MyIterator const &other) :
            ptr_(other.p) {}

    bool operator!=(MyIterator const &other) const {
        return ptr_ != other.ptr_;
    }

    bool operator==(MyIterator const &other) const {
        return ptr_ == other.ptr_;
    }

    typename MyIterator::reference operator*() const {
        return *ptr_;
    }

    MyIterator &operator++() {
        ++ptr_;
        return *this;
    }

private:
    ValueType *ptr_;
};

#endif //PROGTASKSCPP_LAB10_H
