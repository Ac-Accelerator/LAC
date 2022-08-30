#ifndef DETERMINANT_H
#define DETERMINANT_H

#include "base.h"
#pragma once
class Determinant : public Base
{
public:
    int m_rank; //阶数
    Determinant(/* args */);
    Determinant(const Determinant &);
    Determinant(string, int, Fraction *);
    Determinant cofactor(int, int);
    Determinant triangular();
    Fraction calculate();
    ~Determinant();
};

#endif // DETERMINANT_H
