#include "determinant.h"
Determinant::Determinant(/* args */)
{
}

Determinant::Determinant(const Determinant &a)
{
    m_name = a.m_name;
    m_rank = a.m_rank;
    m_m = m_rank, m_n = m_rank;
    for (int i = 1; i <= m_rank; i++)
    {
        for (int j = 1; j <= m_rank; j++)
        {
            map[i][j] = a.map[i][j];
        }
    }
}

Determinant::Determinant(string na, int n, Fraction *list) : Base(na, n, n, list), m_rank(n) {}

Determinant Determinant::cofactor(int x = 0, int y = 0)
{
    if (x > this->m_m || y > this->m_n || x < 1 || y < 1)
    {
        Determinant t(*this);
        return t;
    }
    Determinant B;
    char a = x + '0', b = y + '0';
    B.m_name = this->m_name + "_co_" + a + '&' + b;
    B.m_m = this->m_m - 1, B.m_n = this->m_n - 1, B.m_rank = this->m_rank - 1;
    int px = 1;
    for (int i = 1; i <= m_rank; i++)
    {
        if (x == i)
            continue;
        int py = 1;
        for (int j = 1; j <= m_rank; j++)
        {
            if (y == j)
                continue;
            B.map[px][py] = this->map[i][j];
            py++;
        }
        px++;
    }
    return B;
}

Determinant Determinant::triangular()
{
    Determinant B(*this);
    for (int i = 1; i < m_rank; i++)
    {
        if (B.map[i][i] == 0)
        {
            for (int k = i + 1; k <= m_rank; k++)
            {
                if (B.map[k][i] != 0)
                {
                    B.RowSwap(k, i);
                    B.RowMultiply(k, -1);
                }
            }
        }
        for (int j = i + 1; j <= m_rank; j++)
        {
            if (B.map[j][i] != 0 && B.map[i][i] != 0)
            {
                Fraction temp = B.map[j][i] / B.map[i][i];
                B.RowMultiply(j, B.map[i][i] / B.map[j][i]);
                B.RowMinus(j, i);
                B.RowMultiply(j, temp);
            }
        }
    }
    return B;
}

Fraction Determinant::calculate()
{
    Determinant B(this->triangular());
    Fraction a(1);
    for (int i = 1; i <= m_rank; i++)
    {
        a *= B.map[i][i];
    }
    return a;
}

Determinant::~Determinant()
{
}
