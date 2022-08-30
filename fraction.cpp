#include "fraction.h"

Fraction::Fraction() {}
Fraction::Fraction(const Fraction &a) //拷贝构造函数
{
    denominator = a.denominator;
    molecular = a.molecular;
    positive = a.positive;
}
Fraction::Fraction(string a, bool *check) //按照小数，分数格式传入，若检测到小数点，则按小数处理,不合法的分数自动转换为1并且报错。
{
    molecular = 0;
    denominator = 1;
    positive = 1;
    size_t i, len = a.length(); //指针
    string::size_type po = a.find(".");
    if (po != string::npos)
    {
        if (a[0] == '-')
        {
            positive = 0;
        }
        for (size_t i = 0; i < po; i++)
        {
            if (isalpha(a[i]) && check != nullptr)
                *check = 0;
            if (isdigit(a[i]))
                molecular = molecular * 10 + a[i] - '0';
        }
        for (size_t i = po + 1; i < len; i++)
        {
            if (isalpha(a[i]) && check != nullptr)
                *check = 0;
            if (isdigit(a[i]))
            {
                molecular = molecular * 10 + a[i] - '0';
                denominator *= 10;
            }
        }
    }
    else
    {
        for (i = 0; i < len; i++) //读取分子
        {
            if (isalpha(a[i]) && check != nullptr)
                *check = 0;
            if (isdigit(a[i]))
                molecular = molecular * 10 + a[i] - '0';
            else if (a[i] == '-')
            {
                positive = !positive;
            }
            else if (a[i] == '/')
                break;
        }
        if (i != len) //如果有分母
        {
            denominator = 0;
            for (; i < len; i++)
            {
                if (isalpha(a[i]) && check != nullptr)
                    *check = 0;
                if (isdigit(a[i]))
                    denominator = denominator * 10 + a[i] - '0';
                else if (a[i] == '-')
                    positive = !positive;
            }
        }
    }
    if (denominator != 0) //如果分母不等于0,约分
    {
        long long GCD = GreatestCommonDivisor(molecular, denominator);
        if (GCD != 1)
        {
            molecular /= GCD;
            denominator /= GCD;
        }
    }
    else
    {
        clog << "A fraction with a denominator of 0 exists! Please check the input. Or you will get a wrong answer.\n";
        denominator = 1;
        molecular = 1;
    }
}

Fraction::Fraction(bool p, long long m = 0, long long d = 1) //分子，分母，正负号
{
    positive = p;
    if (m * d < 0) //负的
    {
        positive = !positive;
    }
    molecular = abs(m);
    denominator = abs(d);
    if (denominator != 0) //如果分母不等于0,约分
    {
        long long GCD = GreatestCommonDivisor(molecular, denominator);
        if (GCD != 1)
        {
            molecular /= GCD;
            denominator /= GCD;
        }
    }
    else
    {
        clog << "A fraction with a denominator of 0 exists! Please check the input. Or you will get a wrong answer.\n";
        denominator = 1;
        molecular = 1;
    }
}

Fraction::Fraction(long long a)
{
    positive = 1;
    if (a < 0)
        positive = 0;
    denominator = 1;
    molecular = abs(a);
}
double calculate(Fraction a)
{
    double t = double(a.molecular) / double(a.denominator);
    if (!a.positive)
    {
        t *= -1;
    }
    return t;
}

Fraction::~Fraction()
{
}

string Fraction::display()
{
    string ans = "";
    if ((!this->positive) && molecular != 0)
    {
        ans += '-';
    }
    ans += TurnIntToStr(this->molecular);
    if (this->denominator != 1 && molecular != 0)
    {
        ans += '/';
        ans += TurnIntToStr(this->denominator);
    }
    return ans;
}

Fraction operator+(const Fraction &a, const Fraction &b)
{
    long long LCM = a.denominator * b.denominator / GreatestCommonDivisor(a.denominator, b.denominator); //算最小公倍数
    long long m1 = LCM / a.denominator * a.molecular, m2 = LCM / b.denominator * b.molecular;            //通分
    if (a.positive == 0)                                                                                 //正负号转换到分子上
    {
        m1 = -m1;
    }
    if (b.positive == 0)
    {
        m2 = -m2;
    }
    bool p = 1;
    if (m1 + m2 < 0) //如果是负的
    {
        p = 0;
    }
    Fraction B(p, abs(m1 + m2), LCM);
    return B;
}

Fraction operator-(const Fraction &a, const Fraction &b)
{
    long long LCM = a.denominator * b.denominator / GreatestCommonDivisor(a.denominator, b.denominator);
    long long m1 = LCM / a.denominator * a.molecular, m2 = LCM / b.denominator * b.molecular;
    if (a.positive == 0)
    {
        m1 = -m1;
    }
    if (b.positive == 0)
    {
        m2 = -m2;
    }
    bool p = 1;
    if (m1 - m2 < 0)
    {
        p = 0;
    }
    Fraction B(p, abs(m1 - m2), LCM);
    return B;
}

Fraction operator*(const Fraction &a, const Fraction &b)
{
    bool p = 1;
    if (a.positive != b.positive) //不等，相乘为负数
    {
        p = 0;
    }
    Fraction B(p, a.molecular * b.molecular, a.denominator * b.denominator);
    return B;
}

Fraction operator/(const Fraction &a, const Fraction &b)
{
    bool p = 1;
    if (a.positive != b.positive) //不等，相乘为负数
    {
        p = 0;
    }
    Fraction B(p, a.molecular * b.denominator, a.denominator * b.molecular);
    return B;
}

Fraction &Fraction::operator+=(const Fraction &a)
{
    *this = *this + a;
    return *this;
}

Fraction &Fraction::operator-=(const Fraction &a)
{
    *this = *this - a;
    return *this;
}

Fraction &Fraction::operator*=(const Fraction &a)
{
    *this = *this * a;
    return *this;
}

Fraction &Fraction::operator/=(const Fraction &a)
{
    *this = *this / a;
    return *this;
}

long long GreatestCommonDivisor(long long a, long long b)
{
    if (a == 0 || b == 0)
        return 1;
    long long tmp;
    while (a % b != 0)
    {
        tmp = a;
        a = b;
        b = tmp % b;
    }
    return b;
}

string TurnIntToStr(long long a)
{
    if (a == 0)
    {
        return "0";
    }
    string d = "";
    while (a != 0)
    {
        d += (a % 10) + '0';
        a /= 10;
    }
    reverse(d.begin(), d.end());
    return d;
}

bool operator>(const Fraction &a, const Fraction &b)
{
    long long LCM = a.denominator * b.denominator / GreatestCommonDivisor(a.denominator, b.denominator);
    long long m1 = LCM / a.denominator * a.molecular, m2 = LCM / b.denominator * b.molecular;
    if (a.positive == 0) //正负号转换到分子上
    {
        m1 = -m1;
    }
    if (b.positive == 0)
    {
        m2 = -m2;
    }
    return m1 > m2;
}
bool operator<(const Fraction &a, const Fraction &b)
{
    long long LCM = a.denominator * b.denominator / GreatestCommonDivisor(a.denominator, b.denominator);
    long long m1 = LCM / a.denominator * a.molecular, m2 = LCM / b.denominator * b.molecular;
    if (a.positive == 0) //正负号转换到分子上
    {
        m1 = -m1;
    }
    if (b.positive == 0)
    {
        m2 = -m2;
    }
    return m1 < m2;
}
bool operator>=(const Fraction &a, const Fraction &b)
{
    long long LCM = a.denominator * b.denominator / GreatestCommonDivisor(a.denominator, b.denominator);
    long long m1 = LCM / a.denominator * a.molecular, m2 = LCM / b.denominator * b.molecular;
    if (a.positive == 0) //正负号转换到分子上
    {
        m1 = -m1;
    }
    if (b.positive == 0)
    {
        m2 = -m2;
    }
    return m1 >= m2;
}
bool operator<=(const Fraction &a, const Fraction &b)
{
    long long LCM = a.denominator * b.denominator / GreatestCommonDivisor(a.denominator, b.denominator);
    long long m1 = LCM / a.denominator * a.molecular, m2 = LCM / b.denominator * b.molecular;
    if (a.positive == 0) //正负号转换到分子上
    {
        m1 = -m1;
    }
    if (b.positive == 0)
    {
        m2 = -m2;
    }
    return m1 <= m2;
}

bool operator==(const Fraction &a, const Fraction &b)
{
    return calculate(a) == calculate(b);
}

bool operator!=(const Fraction &a, const Fraction &b)
{
    return calculate(a) != calculate(b);
}
