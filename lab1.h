#ifndef PROGTASKSCPP_LAB1_H
#define PROGTASKSCPP_LAB1_H

//1
void swap_link(int & a, int & b) ;
void swap_point(int * a, int * b);

//4
void floor_link(double & a);
void floor_point(double * a);

//9
struct complex_number {
    complex_number & operator + (complex_number arg) {
        this->im += arg.im;
        this->re += arg.re;

        return *this;
    }

    double re;
    double im;
};
void mult_link(complex_number & a, double b);
void mult_point(complex_number * a, double b);

//12
struct point {
    double x;
    double y;
};
struct circle {
    point centre;
    double radius;
};
struct vector {
    double x;
    double y;
};
void move_link(circle & a, vector b);
void move_point(circle * a, vector b);


#endif //PROGTASKSCPP_LAB1_H
