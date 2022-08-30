#ifndef FRACTION_H
#define FRACTION_H

#include <algorithm>
#include <iostream>
#pragma once
using namespace std;
class Fraction
{
public:
    /* data */
    long long molecular{0}, denominator{1};  //分子，分母
    bool positive = 1;                       //是否正数
    Fraction(string, bool *check = nullptr); // string构造函数
    Fraction(bool, long long, long long);    //是否正数，分子，分母
    Fraction(long long);
    Fraction();
    Fraction(const Fraction &); //拷贝构造函数
    string display();
    friend double calculate(Fraction); //计算具体值
    friend Fraction operator+(const Fraction &, const Fraction &);
    friend Fraction operator-(const Fraction &, const Fraction &);
    friend Fraction operator*(const Fraction &, const Fraction &);
    friend Fraction operator/(const Fraction &, const Fraction &);
    friend bool operator>(const Fraction &, const Fraction &);
    friend bool operator<(const Fraction &, const Fraction &);
    friend bool operator>=(const Fraction &, const Fraction &);
    friend bool operator<=(const Fraction &, const Fraction &);
    friend bool operator==(const Fraction &, const Fraction &);
    friend bool operator!=(const Fraction &, const Fraction &);
    Fraction &operator+=(const Fraction &);
    Fraction &operator-=(const Fraction &);
    Fraction &operator*=(const Fraction &);
    Fraction &operator/=(const Fraction &);
    ~Fraction();
};
string TurnIntToStr(long long);                        //将整数转化为string
long long GreatestCommonDivisor(long long, long long); //求最大公约数
Fraction operator+(const Fraction &, const Fraction &);
Fraction operator-(const Fraction &, const Fraction &);
Fraction operator*(const Fraction &, const Fraction &);
Fraction operator/(const Fraction &, const Fraction &);
bool operator>(const Fraction &, const Fraction &);
bool operator<(const Fraction &, const Fraction &);
bool operator>=(const Fraction &, const Fraction &);
bool operator<=(const Fraction &, const Fraction &);
bool operator==(const Fraction &, const Fraction &);
bool operator!=(const Fraction &, const Fraction &);
#endif // FRACTION_H
