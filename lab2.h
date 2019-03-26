#ifndef PROGTASKSCPP_LAB2_H
#define PROGTASKSCPP_LAB2_H

#include <cmath>

struct point {
    double x;
    double y;
};
struct triangle {
    double area();

    bool operator == (triangle right);
    bool operator != (triangle right);
    bool operator > (triangle right);
    bool operator < (triangle right);

    point a;
    point b;
    point c;
};

struct IntArray {
    IntArray();
    IntArray(int size);
    ~IntArray();

    IntArray operator + (IntArray const & right);
    IntArray & operator = (IntArray const & right);
    bool operator == (IntArray const & right);
    bool operator != (IntArray const & right);
    bool operator < (IntArray const & right);
    bool operator > (IntArray const & right);

    int & get(int pos);
    int length();

    int * arr;
    int size;
};


#endif //PROGTASKSCPP_LAB2_H
