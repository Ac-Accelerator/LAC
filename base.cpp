#include "base.h"

Base::Base(/* args */)
{
}

Base::Base(const Base &a) //拷贝构造函数
{
    m_name = a.m_name;
    m_m = a.m_m, m_n = a.m_n;
    for (int i = 1; i <= m_m; i++)
    {
        for (int j = 1; j <= m_n; j++)
        {
            map[i][j] = a.map[i][j];
        }
    }
}

Base::Base(string na, int m, int n, Fraction *a)
{
    m_m = m, m_n = n;
    m_name = na;
    size_t point = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            map[i][j] = a[point++];
        }
    }
}

void Base::RowSwap(int a, int b)
{
    if (a > m_m || b > m_m || a < 1 || b < 1)
    {
        clog << "The operation \"swap\" is out of range, operation have not performed.\n";
        return;
    }
    for (int i = 1; i <= m_n; i++)
    {
        swap(this->map[a][i], this->map[b][i]);
    }
}

void Base::RowAdd(int a, int b)
{
    if (a > m_m || b > m_m || a < 1 || b < 1)
    {
        clog << "The operation \"swap\" is out of range, operation have not performed.\n";
        return;
    }

    for (int i = 1; i <= m_n; i++)
    {
        this->map[a][i] += this->map[b][i];
    }
}

void Base::RowMinus(int a, int b)
{
    if (a > m_m || b > m_m || a < 1 || b < 1)
    {
        clog << "The operation \"swap\" is out of range, operation have not performed.\n";
        return;
    }
    for (int i = 1; i <= m_n; i++)
    {
        this->map[a][i] -= this->map[b][i];
    }
}

void Base::RowMultiply(int a, Fraction b)
{
    if (a > m_m || a < 1)
    {
        clog << "The operation \"swap\" is out of range, operation have not performed.\n";
        return;
    }

    for (int i = 1; i <= m_n; i++)
    {
        this->map[a][i] *= b;
    }
}
void Base::ColumSwap(int a, int b)
{
    if (a > m_n || b > m_n || a < 1 || b < 1)
    {
        clog << "The operation \"swap\" is out of range, operation have not performed.\n";
        return;
    }
    for (int i = 1; i <= m_m; i++)
    {
        swap(this->map[i][a], this->map[i][b]);
    }
}
void Base::ColumAdd(int a, int b)
{
    if (a > m_n || b > m_n || a < 1 || b < 1)
    {
        clog << "The operation \"swap\" is out of range, operation have not performed.\n";
        return;
    }
    for (int i = 1; i <= m_m; i++)
    {
        this->map[i][a] += this->map[i][b];
    }
}
void Base::ColumMinus(int a, int b)
{
    if (a > m_n || b > m_n || a < 1 || b < 1)
    {
        clog << "The operation \"swap\" is out of range, operation have not performed.\n";
        return;
    }
    for (int i = 1; i <= m_m; i++)
    {
        this->map[i][a] -= this->map[i][b];
    }
}
void Base::ColumMultiply(int a, Fraction b)
{
    if (a > m_n || a < 1)
    {
        clog << "The operation \"swap\" is out of range, operation have not performed.\n";
        return;
    }
    for (int i = 1; i <= m_m; i++)
    {
        this->map[i][a] *= b;
    }
}
void Base::transpose()
{
    int max_ = max(m_m, m_n);
    for (int i = 1; i < max_; i++)
    {
        for (int j = i + 1; j <= max_; j++)
        {
            swap(this->map[i][j], this->map[j][i]);
        }
    }
    swap(this->m_m, this->m_n);
}

void Base::display()
{
    cout << "名称:" << left << setw(5) << this->m_name << "大小:" << this->m_m << 'X' << this->m_n << endl;
    for (int i = 1; i <= m_m; i++)
    {
        for (int j = 1; j <= m_n; j++)
        {
            cout << left << setw(7) << map[i][j].display();
        }
        cout << endl;
    }
}

Base::~Base()
{
}
