#include "polynomial.h"
#include <iostream>
#include <string>

Polynomial::Polynomial(int A[], int size) {
    unsigned int counter = 0;
    size_ = size;

    while (counter < size_) {
      polynomial_coefficients.insert_back(A[counter]);
      counter++;
    }
};

Polynomial* Polynomial::add(Polynomial *rhs) {

    int max_size = 0;

    if (rhs->size_ > size_) {
        max_size = rhs -> size_;
    } else {
        max_size = size_;
    }

    int resultant_coefficients[max_size];
    int this_coefficients = 0;
    int rhs_coefficients = 0;

    for (int i = 0; i < max_size; i++) {

        if (i >= size_) {
            this_coefficients = 0;
        } else {
            this_coefficients = polynomial_coefficients.select(i);
        }

        if (i >= rhs->size_) {
            rhs_coefficients = 0;
        } else {
            rhs_coefficients = rhs->polynomial_coefficients.select(i);
        }

        resultant_coefficients[i] = this_coefficients + rhs_coefficients;
    }

    Polynomial* resultant_polynomial = new Polynomial(resultant_coefficients, max_size);
    return resultant_polynomial;
};

Polynomial* Polynomial::sub(Polynomial *rhs) {

    int max_size = 0;

    if (rhs->size_ > size_) {
        max_size = rhs -> size_;
    } else {
        max_size = size_;
    }

    int resultant_coefficients[max_size];
    int this_coefficients = 0;
    int rhs_coefficients = 0;

    for (int i = 0; i < max_size; i++) {

        if (i >= size_) {
            this_coefficients = 0;
        } else {
            this_coefficients = polynomial_coefficients.select(i);
        }

        if (i >= rhs->size_) {
            rhs_coefficients = 0;
        } else {
            rhs_coefficients = rhs->polynomial_coefficients.select(i);
        }

        resultant_coefficients[i] = this_coefficients - rhs_coefficients;
    }

    Polynomial* resultant_polynomial = new Polynomial(resultant_coefficients, max_size);
    return resultant_polynomial;
};

Polynomial* Polynomial::mul(Polynomial *rhs) {

    int max_size = size_ + rhs->size_ - 1;
    int resultant_coefficients[max_size];

    for (int i = 0; i < max_size; i++) {
        resultant_coefficients[i] = 0;
    }

    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < rhs->size_; j++) {
            int this_coefficients = polynomial_coefficients.select(i);
            int rhs_coefficients = rhs->polynomial_coefficients.select(j);
            resultant_coefficients[i+j] += this_coefficients * rhs_coefficients;
        }
    }

    Polynomial* resultant_polynomial = new Polynomial(resultant_coefficients, size_ + rhs-> size_ - 1);
    return resultant_polynomial;
};

void Polynomial::print() {

    int zero_counter = 0;
    std::string print_item;

    int counter = 0;
    for (int i = 0; i < size_-1; i++) {
        if (polynomial_coefficients.select(i) != 0) {
            counter++;
        }
    }

    for (int i = size_-1; i >= 0; i--) {

        print_item = "";
        if (i == size_-1 || counter == 1) {
            ;
        } else {
            print_item += " + ";
        }

        if (polynomial_coefficients.select(i) == 0) {
            zero_counter++;
            if (zero_counter == size_) { std::cout << "empty"; break; }
            continue;
        } else if (polynomial_coefficients.select(i) < 0) {
            print_item += "(" + (std::to_string(polynomial_coefficients.select(i))) + ")" + "x^" + std::to_string(i);
        } else {
            print_item += std::to_string(polynomial_coefficients.select(i)) + "x^" + std::to_string(i);
        }

        std::cout << print_item;
    }
    std::cout << std::endl;
}