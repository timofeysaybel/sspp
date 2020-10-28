#include "../../inc/matrix.h"

Matrix::Matrix(const Matrix &another)
{
    n = another.n;
    mat.resize(n);
    m = another.m;

    for (int i = 0; i < n; i++)
        mat[i].resize(m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mat[i][j] = another.mat[i][j];
        }
    }
}

Matrix::Matrix(size_t n1, size_t m1)
{
    n = n1;
    m = m1;

    mat.resize(n);
    for (int i = 0; i < n; i++)
    {
        mat[i].resize(m);
        for (int j = 0; j < m; j++)
            mat[i][j] = 0;
    }
}

Matrix Matrix::operator=(const Matrix &another)
{
    n = another.n;
    mat.resize(n);
    m = another.m;
    for (int i = 0; i < n; i++)
        mat[i].resize(m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mat[i][j] = another.mat[i][j];
        }
    }

    return *this;
}


Matrix::~Matrix()
{
    for (int i = 0; i < mat.size(); i++)
        mat[i].clear();
    mat.clear();
}

Matrix Matrix::operator*(const Matrix &another) const
{
    if (m != another.n)
    {
        cerr << "Разный размер матриц при перемножении" << endl;
        cout << m << " " << another.n << endl;
        exit(-1);
    }

    Matrix res(n,another.m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < another.m; j++)
        {
            res.mat[i][j] = 0;
            for (int k = 0; k < m; k++)
            {
                res.mat[i][j] += mat[i][k]*another.mat[k][j];
            }
        }
    }

    return res;
}

void Matrix::print(ostream &stream) const
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            stream << mat[i][j] << " ";
        stream << endl;
    }
    stream << endl;
}

Matrix Matrix::getFromFile(string filename)
{
    ifstream file(filename);

    if (!file.is_open() || file.eof())
    {
        cerr << "Не удалось открыть файл" << endl;
        exit(-1);
    }

    int n,m;
    file >> n >> m;

    if (n < 0 || m < 0)
    {
        cerr << "Неверный формат файла" << endl;
        exit(-1);
    }

    Matrix res(n,m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (file.eof())
            {
                cerr << "Неверный формат файла" << endl;
                exit(-1);
            }
            file >> res.mat[i][j];
        }
    }

    return res;
}

Matrix Matrix::blockMultiply(const Matrix &another, size_t sizeOfBlock) const
{
    if (m != another.n)
    {
        cerr << "Разный размер матриц при перемножении" << endl;
        exit(-1);
    }

    Matrix res(n,another.m);

    int i = 0;
    while (i < n)
    {
        int j = 0;
        int offsetI = sizeOfBlock > n - i ? n - i : sizeOfBlock;
        while (j < another.m)
        {
            int k = 0;
            int offsetJ = sizeOfBlock > another.m - j ? another.m - j : sizeOfBlock;
            while (k < m)
            {
                int offsetK = sizeOfBlock > m - k ? m - k : sizeOfBlock;
                for (int i1 = i; i1 < i + offsetI; i1++)
                {
                    for (int j1 = j; j1 < j + offsetJ; j1++)
                    {
                        for (int k1 = k; k1 < k + offsetK; k1++)
                            res.mat[i1][j1] += mat[i1][k1] * another.mat[k1][j1];
                    }
                }
                k += offsetK;
            }
            j += offsetJ;
        }
        i += offsetI;
    }

    return res;
}

bool Matrix::operator==(const Matrix &another) const
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] != another.mat[i][j])
                return false;
        }
    }
    return true;
}