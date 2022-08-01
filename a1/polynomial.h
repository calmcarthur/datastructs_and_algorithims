#ifndef SYDE223_A1_POLYNOMIAL_H
#define SYDE223_A1_POLYNOMIAL_H

#include "doubly-linked-list.h"

class Polynomial {
private:
    unsigned int size_;
    DoublyLinkedList polynomial_coefficients;

public:
    Polynomial(int A[], int size);

    Polynomial* add(Polynomial* rhs);
    Polynomial* sub(Polynomial* rhs);
    Polynomial* mul(Polynomial* rhs);

    void print();
};

#endif
