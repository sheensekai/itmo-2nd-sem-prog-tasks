#ifndef PROGTASKSCPP_LAB6_H
#define PROGTASKSCPP_LAB6_H

#include <iostream>
#include <cmath>

template <typename Type>
Type FindMax(Type * array, size_t size) {
    if (size == 1)
        return array[0];

    Type max = array[0];
    for (size_t i = 1; i < size; ++i) {
        if (array[i] > max)
            max = array[i];
    }

    return max;
}

template <typename Type>
Type FindMin(Type first, Type second) {
    return (first >= second ? first : second);
}

template <typename Type>
void Swap(Type &first, Type &second) {
    Type tmp = first;
    first = second;
    second = tmp;
}

#endif //PROGTASKSCPP_LAB6_H
