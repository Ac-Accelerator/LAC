#include "calculate.h"
map<string, int> order;
int PM = 0;
Matix LM[400];
bool sign_of_digit = 0;

Matix expression_value(string a, int &p)
{
    Matix result = term_value(a, p);
    while (true)
    {
        if (p != a.length() && (a[p] == '+' || a[p] == '-'))
        {
            char op = a[p];
            p++;
            Matix value = term_value(a, p);
            if (op == '+')
                result += value;
            else
                result -= value;
        }
        else
            break;
    }
    return result;
}
Matix term_value(string a, int &p)
{
    Matix result = factor_value(a, p);
    while (true)
    {
        if (p != a.length() && a[p] == '*')
        {
            char op = a[p];
            p++;
            Matix value = factor_value(a, p);
            if (op == '*')
            {
                if (value.m_m == value.m_n && value.m_m == 1)
                    result = result * value.map[1][1];
                else
                    result *= value;
            }
        }
        else
            break;
    }
    return result;
}
Matix factor_value(string a, int &p)
{
    string na;
    Matix result("null", 1, 0);
    if (p != a.length() && a[p] == '(')
    {
        p++;
        Matix result = expression_value(a, p);
        p++;
    }
    else
    {
        while (p != a.length() && a[p] != '+' && a[p] != '-' && a[p] != '*' && a[p] != ')' && a[p] != '\'')
        {
            na += a[p++];
        }
        if (!order.count(na))
        {
            //            cout << "未找到使用此名字的变量:" << na << endl;
            bool digit = 1;
            Fraction f(na, &digit);
            if (digit)
                return Matix(na, 1, f);
            else
                return Matix("null", 1, 0);
        }
#if 0
        if (order[na].first != "Matix")
        {
            cout << "使用该名称的变量不属于矩阵:" << na << endl;
            return Matix("null", 1, 0);
        }

        result = LM[cache[na].second];
        if (a[p] == '\'')
        {
            p++;
            if (a[p] == 'I' || a[p] == 'i')
            {
                result = result.inverse();
            }
            else if (a[p] == 'T' || a[p] == 't')
            {
                result.transpose();
            }
            else if (a[p] == 'A' || a[p] == 'a')
            {
                result = result.adjoint();
            }
            else
            {
                cout << "不合法的操作： \'" << a[p] << endl;
                return Matix("null", 1, 0);
            }
            p++;
        }

#endif
#if 1
        result = LM[order[na]];
#endif

        return result;
    }
}
