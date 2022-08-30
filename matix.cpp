#include "matix.h"
Matix::Matix(string na, int m, int n, Fraction *list) : Base(na, m, n, list) {}
Matix::Matix() {}
Matix::Matix(string na, int n, Fraction num)
{
    m_m = n, m_n = n;
    m_name = na;
    Fraction temp(0);
    for (int i = 1; i <= m_m; i++)
    {
        for (int j = 1; j <= m_n; j++)
        {
            map[i][j] = temp;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        map[i][i] = num;
    }
}
Matix::Matix(const Matix &a)
{
    m_name = a.m_name, m_m = a.m_m, m_n = a.m_n;
    for (int i = 1; i <= m_m; i++)
    {
        for (int j = 1; j <= m_n; j++)
        {
            map[i][j] = a.map[i][j];
        }
    }
}
Determinant Matix::Det()
{
    if (m_m != m_n)
    {
        Determinant f;
        clog << "This matrix \"" << this->m_name << "\" cannot be converted to a determinant!\n";
        return f;
    }
    Fraction list[m_n * m_m];
    int point = 0;
    for (int i = 1; i <= m_m; i++)
    {
        for (int j = 1; j <= m_n; j++)
        {
            list[point++] = map[i][j];
        }
    }
    Determinant B(m_name + "_det", m_m, list);
    return B;
}

Matix Matix::adjoint()
{
    Matix B("null", 1, 1);
    if (this->m_m != this->m_n)
    {
        clog << "The matrix \"" << this->m_name << "\" does not meet the adjoint conditions, check the input!\n";
        return B;
    }
    B.m_name = this->m_name + "_Adj";
    B.m_m = this->m_m, B.m_n = this->m_n;
    Determinant temp = this->Det();
    for (int i = 1; i <= B.m_m; i++)
    {
        for (int j = 1; j <= B.m_n; j++)
        {
            B.map[j][i] = temp.cofactor(i, j).calculate();
            if ((i + j) % 2)
            {
                B.map[j][i] *= -1;
            }
        }
    }
    return B;
}

Matix Matix::inverse()
{
    Fraction de = this->Det().calculate();
    if (this->m_m != this->m_n || de == 0)
    {
        Matix B("null", 1, 1);
        clog << "The matrix \"" << this->m_name << "\" does not meet the inverse conditions, check the input!\n";
        return B;
    }
    Matix B = this->adjoint();
    Matix t("1/Detv", this->m_n, 1 / de);
    B *= t;
    B.m_name = this->m_name + "_Inv";
    return B;
}

Matix operator+(const Matix &a, const Matix &b)
{
    Matix B("null", 1, 1);
    if ((a.m_m != b.m_m) || (a.m_n != b.m_n))
    {
        clog << "\"" << a.m_name << "\"and \"" << b.m_name << "\" can not operate \"+\", check the input!\n";
        return B;
    }
    B.m_name = "[" + a.m_name + "+" + b.m_name + "]";
    B.m_m = a.m_m, B.m_n = a.m_n;
    for (int i = 1; i <= B.m_m; i++)
    {
        for (int j = 1; j <= B.m_n; j++)
        {
            B.map[i][j] = a.map[i][j] + b.map[i][j];
        }
    }
    return B;
}

Matix operator-(const Matix &a, const Matix &b)
{
    Matix B("null", 1, 1);
    if ((a.m_m != b.m_m) || (a.m_n != b.m_n))
    {
        clog << "\"" << a.m_name << "\"and \"" << b.m_name << "\" can not operate \"-\", check the input!\n";
        return B;
    }
    B.m_name = "[" + a.m_name + "-" + b.m_name + "]";
    B.m_m = a.m_m, B.m_n = a.m_n;
    for (int i = 1; i <= B.m_m; i++)
    {
        for (int j = 1; j <= B.m_n; j++)
        {
            B.map[i][j] = a.map[i][j] - b.map[i][j];
        }
    }
    return B;
}

Matix operator*(const Matix &a, const Matix &b)
{
    Matix B("null", 1, 1);
    if (a.m_n != b.m_m)
    {
        clog << "\"" << a.m_name << "\"and \"" << b.m_name << "\" can not operate \"*\", check the input!\n";
        return B;
    }
    B.m_name = "[" + a.m_name + " X " + b.m_name + "]";
    B.m_m = a.m_m, B.m_n = b.m_n;
    for (int i = 1; i <= B.m_m; i++)
    {
        for (int j = 1; j <= B.m_n; j++)
        {
            Fraction sum(0);
            for (int k = 1; k <= a.m_n; k++)
            {
                sum += a.map[i][k] * b.map[k][j];
            }
            B.map[i][j] = sum;
        }
    }
    return B;
}

Matix operator*(const Matix &a, Fraction &b)
{
    Matix B(a);
    B.m_name = "[" + a.m_name + " X " + b.display() + "]";
    for (int i = 1; i <= a.m_m; i++)
        for (int j = 1; j <= a.m_n; j++)
            B.map[i][j] *= b;
    return B;
}

Matix &Matix::operator+=(const Matix &a)
{
    *this = *this + a;
    return *this;
}

Matix &Matix::operator-=(const Matix &a)
{
    *this = *this - a;
    return *this;
}

Matix &Matix::operator*=(const Matix &a)
{
    *this = *this * a;
    return *this;
}

int Matix::rank()
{ //化为行最简形
    Matix B = *this;
    bool sign[this->m_m + 1] = {0};
    for (int i = 1; i <= this->m_n; i++) //迭代每一列
    {
        for (int j = 1; j <= this->m_m; j++) //迭代每一行找非零主元
        {
            if (B.map[j][i] != 0 && sign[j] != 1) //非零，且该行没有其他非零主元
            {
                sign[j] = 1;                         //标记
                for (int k = 1; k <= this->m_m; k++) //对该列每一行非零元素进行清零
                {
                    if (k != j && B.map[k][i] != 0)
                    {
                        Fraction temp = B.map[k][i] / B.map[j][i];
                        B.RowMultiply(k, B.map[j][i] / B.map[k][i]);
                        B.RowMinus(k, j);
                        B.RowMultiply(k, temp);
                    }
                }
                break;
            }
        }
    }
    //计数
    int rank = B.m_m;
    for (int i = 1; i <= B.m_m; i++)
    {
        int sum = 0;
        for (int j = 1; j <= B.m_n; j++)
        {
            if (B.map[i][j] == 0)
            {
                sum++;
            }
        }
        if (sum == B.m_n)
        {
            rank--;
        }
    }
    return rank;
}
#if 0
double *Matix::eigenvalue(double down, double up, double pr)
{
    double *t = new double[100]{};
    if (this->m_m != this->m_n)
    {
        clog << "矩阵不满足条件，请进行输入检查\n";
        return t;
    }
    int p = 0;
    double copy[this->m_m + 1][this->m_n + 1], temp[this->m_m + 1][this->m_n + 1];
    for (int i = 1; i <= this->m_m; i++)
    {
        for (int j = 1; j <= this->m_n; j++)
        {
            copy[i][j] = calculate(this->map[i][j]);
        }
    }
    double last = 1;
    double point = down;
    while (point <= up)
    {
        for (int i = 1; i <= this->m_m; i++) //拷贝一份
        {
            for (int j = 1; j <= this->m_n; j++)
            {
                temp[i][j] = copy[i][j];
            }
        }
        for (int j = 1; j <= this->m_n; j++) //对角线减去
        {
            temp[j][j] -= point;
        }
        //三角化
        for (int i = 1; i < this->m_m; i++)
        {
            if (temp[i][i] == 0)
            {
                for (int k = i + 1; k <= this->m_m; k++)
                {
                    if (temp[k][i] != 0)
                    {
                        for (int s = 1; s <= this->m_n; s++)
                        {
                            swap(temp[k][s], temp[i][s]);
                        }
                        for (int s = 1; s <= m_n; s++)
                        {
                            temp[k][s] *= -1;
                        }
                    }
                }
            }
            for (int j = i + 1; j <= this->m_m; j++)
            {
                if (temp[j][i] != 0 && temp[i][i] != 0)
                {
                    double nu = temp[j][i] / temp[i][i];
                    double nu2 = temp[i][i] / temp[j][i];
                    for (int s = 1; s <= this->m_n; s++)
                    {
                        temp[j][s] *= nu2;
                    }
                    for (int s = 1; s <= this->m_n; s++)
                    {
                        temp[j][s] -= temp[i][s];
                    }
                    for (int s = 1; s <= this->m_n; s++)
                    {
                        temp[j][s] *= nu;
                    }
                }
            }
        }
        double ans = 1;
        for (int i = 1; i <= this->m_n; i++)
        {
            ans *= temp[i][i];
        }
        if (abs(ans - int(ans)) < 1e-10 && int(ans) == 0)
        {
            t[p++] = point;
            last = 0;
        }
        else if (ans * last < 0 && point != down)
        {
            t[p++] = point - pr / 2;
            last = ans;
        }
        point += pr;
    }
    t[p++] = 114514.114514;
    return t;
}
#endif
eigen Matix::eigenvalue()
{
    double data[m_m * m_n];
    size_t ptr = 0;
    for (int i = 1; i <= m_m; i++)
    {
        for (int j = 1; j <= m_n; ++j, ++ptr)
        {
            data[ptr] = static_cast<double>(map[i][j].molecular) / map[i][j].denominator;
            if (!map[i][j].positive)
            {
                data[ptr] *= -1;
            }
        }
    }
    gsl_matrix_view m = gsl_matrix_view_array(data, m_m, m_n);
    gsl_vector_complex *eval = gsl_vector_complex_alloc(m_m);
    gsl_matrix_complex *evec = gsl_matrix_complex_alloc(m_m, m_m);
    gsl_eigen_nonsymmv_workspace *w = gsl_eigen_nonsymmv_alloc(m_m);
    gsl_eigen_nonsymmv_params(0, w);
    gsl_eigen_nonsymmv(&m.matrix, eval, evec, w);
    gsl_eigen_nonsymmv_free(w);
    for (int j = 0; j < m_n; ++j)
    {
        double min = 1.79769e+307;
        for (int i = 0; i < m_m; ++i)
        {
            gsl_complex element = gsl_matrix_complex_get(evec, i, j);
            if (abs(element.dat[0]) < min && abs(element.dat[0]) >= 1e-10)
                min = abs(element.dat[0]);
        }
        double temp = 1 / min;
        for (int i = 0; i < m_m; ++i)
        {
            gsl_complex element = gsl_matrix_complex_get(evec, i, j);
            element.dat[0] *= temp, element.dat[1] *= temp;
            gsl_matrix_complex_set(evec, i, j, element);
        }
    }
#if 0
    {
        int i;
        for (i = 0; i < m_m; i++)
        {
            cout << "One of the eigenvalue is : " << i + 1;
            gsl_complex eval_i = gsl_vector_complex_get(eval, i);
            cout << eval_i.dat[0] << '\t';
            if (eval_i.dat[1] > 0)
                cout << '+';
            if (eval_i.dat[1] != 0)
                cout << eval_i.dat[1] << "*i";
            cout << endl
                 << "Its corresponding eigenvector is : " << endl;
            for (int j = 0; j < m_m; j++)
            {
                gsl_complex element = gsl_matrix_complex_get(evec, j, i);
                cout << element.dat[0] << '\t';
                if (element.dat[1] > 0)
                    cout << '+';
                if (element.dat[1] != 0)
                    cout << element.dat[1] << "*i";
                cout << endl;
            }
            cout << endl;
        }
    }
#endif
    eigen ans;
    ans.matix = evec, ans.value = eval;
    return ans;
}
bool operator==(const Matix &a, const Matix &b)
{
    Matix c(a), d(b);
    return c.rank() == d.rank();
}

bool Equivalent(const Matix &a, const Matix &b)
{
    return a == b;
}
