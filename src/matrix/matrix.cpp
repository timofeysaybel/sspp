#include "../../inc/matrix/matrix.h"

template class Matrix<double>;
template class Matrix<float>;

template<typename T>
Matrix<T>::Matrix(string filename)
{
    ifstream file(filename);

    if (!file.is_open() || file.eof())
    {
        cerr << "Не удалось открыть файл" << endl;
        exit(-1);
    }

    char t;
    file >> t;

    if (file.eof())
    {
        cerr << "Неверный формат файла" << endl;
        exit(-1);
    }

    file >> n >> m;

    if (n < 0 || m < 0)
    {
        cerr << "Неверный формат файла" << endl;
        exit(-1);
    }

    mat.resize(n);
    for (int i = 0; i < n; i++)
    {
        mat[i].resize(m);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (file.eof())
            {
                cerr << "Неверный формат файла" << endl;
                exit(-1);
            }
            file >> mat[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &another)
{
    n=another.n;
    m=another.m;

    mat.resize(n);
    for (auto v : mat)
    {
        v.resize(m);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            mat[i][j]=another.mat[i][j];
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &another)
{
    n=another.n;
    m=another.m;

    mat.resize(n);
    for (int i = 0; i < n; i++)
    {
        mat[i].resize(m);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            mat[i][j]=another.mat[i][j];
    }

    return *this;
}

template<typename T>
Matrix<T>::~Matrix<T>()
{
    for (auto v : mat)
    {
        v.clear();
    }
    mat.clear();
}

template<typename T>
void Matrix<T>::print(ostream &stream) const
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

template<typename T>
Matrix<T> Matrix<T>::ijk(const Matrix<T> &another) const
{
    if (m != another.n || m < 0 || n < 0 || another.m <0)
    {
        cerr << "Неверные размеры матриц" << endl;
        throw -1;
    }

    Matrix<T> res;

    res.mat.resize(n);
    for (int i=0;i<n;i++)
    {
        res.mat[i].resize(another.m);
        for (int j = 0; j < m; j++)
            res.mat[i][j]=0;
    }

    for (int i=0;i<n;i++)
    {
        for (int j=0;j<another.m;j++)
        {
            for (int k=0;k<m;k++)
            {
                res.mat[i][j]+=mat[i][k]*another.mat[k][j];
            }
        }
    }

    res.n=n;
    res.m=another.m;
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::jik(const Matrix<T> &another) const
{
    if (m != another.n || m < 0 || n < 0 || another.m <0)
    {
        cerr << "Неверные размеры матриц" << endl;
        throw -1;
    }

    Matrix<T> res;

    res.mat.resize(n);
    for (int i=0;i<n;i++)
    {
        res.mat[i].resize(another.m);
        for (int j = 0; j < m; j++)
            res.mat[i][j]=0;
    }

    for (int j=0;j<another.m;j++)
    {
        for (int i=0;i<n;i++)
        {
            for (int k=0;k<m;k++)
            {
                res.mat[i][j]+=mat[i][k]*another.mat[k][j];
            }
        }
    }
    res.n=n;
    res.m=another.m;
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::ikj(const Matrix<T> &another) const
{
    if (m != another.n || m < 0 || n < 0 || another.m <0)
    {
        cerr << "Неверные размеры матриц" << endl;
        throw -1;
    }

    Matrix<T> res;

    res.mat.resize(n);
    for (int i=0;i<n;i++)
    {
        res.mat[i].resize(another.m);
        for (int j = 0; j < m; j++)
            res.mat[i][j]=0;
    }

    for (int i=0;i<n;i++)
    {
        for (int k=0;k<m;k++)
        {
            for (int j=0;j<another.m;j++)
                res.mat[i][j]+=mat[i][k]*another.mat[k][j];
        }
    }
    res.n=n;
    res.m=another.m;
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::kij(const Matrix<T> &another) const
{
    if (m != another.n || m < 0 || n < 0 || another.m <0)
    {
        cerr << "Неверные размеры матриц" << endl;
        throw -1;
    }

    Matrix<T> res;

    res.mat.resize(n);
    for (int i=0;i<n;i++)
    {
        res.mat[i].resize(another.m);
        for (int j = 0; j < m; j++)
            res.mat[i][j]=0;
    }

    for (int k=0;k<m;k++)
    {
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<another.m;j++)
                res.mat[i][j]+=mat[i][k]*another.mat[k][j];
        }
    }
    res.n=n;
    res.m=another.m;
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::jki(const Matrix<T> &another) const
{
    if (m != another.n || m < 0 || n < 0 || another.m <0)
    {
        cerr << "Неверные размеры матриц" << endl;
        throw -1;
    }

    Matrix<T> res;

    res.mat.resize(n);
    for (int i=0;i<n;i++)
    {
        res.mat[i].resize(another.m);
        for (int j = 0; j < m; j++)
            res.mat[i][j]=0;
    }

    for (int j=0;j<another.m;j++)
    {
        for (int k=0;k<m;k++)
        {
            for (int i=0;i<n;i++)    
                res.mat[i][j]+=mat[i][k]*another.mat[k][j];
        }
    }
    res.n=n;
    res.m=another.m;
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::kji(const Matrix<T> &another) const
{
    if (m != another.n || m < 0 || n < 0 || another.m <0)
    {
        cerr << "Неверные размеры матриц" << endl;
        throw -1;
    }

    Matrix<T> res;

    res.mat.resize(n);
    for (int i=0;i<n;i++)
    {
        res.mat[i].resize(another.m);
        for (int j = 0; j < m; j++)
            res.mat[i][j]=0;
    }

    for (int k=0;k<m;k++)
    {
        for (int j=0;j<another.m;j++)
        {
            for (int i=0;i<n;i++)    
                res.mat[i][j]+=another.mat[i][k]*mat[k][j];
        }
    }
    res.n=n;
    res.m=another.m;
    return res;
}

template <typename T>
void Matrix<T>::saveMatrix(string filename,char mode) const
{
    ofstream file(filename);

    file << mode << endl << n << endl << m << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            file << mat[i][j] << " ";
        file << endl;
    }
}

template<typename T>
bool Matrix<T>::cmpMatrix(const Matrix<T> &another) const
{
    if (n != another.n || m != another.m)
        return false;
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
