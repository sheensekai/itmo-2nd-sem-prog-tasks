#include "lab1.h"
#include <math.h>

// 1
void swap_link(int & a, int & b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swap_point(int * a, int * b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 4
void floor_link(double & a) {
    a = std::floor(a);
}

void floor_point(double * a) {
    *a = std::floor(*a);
}

// 9
void mult_link(complex_number & a, double b) {
    a.im *= b;
    a.re *= b;
}

void mult_point(complex_number * a, double b) {
    a->im *= b;
    a->re *= b;
}

//12
void move_link(circle & a, vector b) {
    a.centre.x += b.x;
    a.centre.y += b.y;
}

void move_point(circle * a, vector b) {
    a->centre.x += b.x;
    a->centre.y += b.y;
}

