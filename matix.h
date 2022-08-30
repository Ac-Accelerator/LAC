#ifndef MATIX_H
#define MATIX_H

#include "base.h"
#include "determinant.h"
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_math.h>
#pragma once
struct eigen
{
    gsl_vector_complex *value;
    gsl_matrix_complex *matix;
};

class Matix : public Base
{
public:
    Matix(string, int, int, Fraction *);
    Matix();
    Matix(const Matix &);
    Matix(string, int, Fraction); //阶数，常数
    Determinant Det();
    Matix adjoint();
    int rank();
    Matix inverse();
    // double *eigenvalue(double, double, double);
    eigen eigenvalue();
    friend Matix operator+(const Matix &, const Matix &);
    friend Matix operator-(const Matix &, const Matix &);
    friend Matix operator*(const Matix &, const Matix &);
    friend Matix operator*(const Matix &, const int);
    friend bool operator==(const Matix &, const Matix &);
    Matix &operator+=(const Matix &);
    Matix &operator-=(const Matix &);
    Matix &operator*=(const Matix &);
};
Matix operator*(const Matix &, Fraction &);
Matix operator+(const Matix &, const Matix &);
Matix operator-(const Matix &, const Matix &);
Matix operator*(const Matix &, const Matix &);
bool operator==(const Matix &, const Matix &);
bool Equivalent(const Matix &, const Matix &);

#endif // MATIX_H
