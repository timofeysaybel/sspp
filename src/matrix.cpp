#include "../inc/matrix.h"
#include <mpi.h>

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
        throw -1;
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

vector<double> Matrix::operator*(const vector<double> &vec) const
{
    if (m != vec.size())
    {
        cerr << "Разные размеры матрицы и вектора" << endl;
        throw -1;
    }

    vector<double> res(n);

    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < m; j++)
        {
            res[i] += mat[i][j]*vec[j];
        }
    }

    return res;
}

vector<double> Matrix::parallelMultiply(const vector<double> &b,string fileC,string fileTime) const
{
    int rank, commSize;
    vector<double> c(n);

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Status status;

    int offset = 0;
    if (n >= m)
        offset = n / commSize;
    else
        offset = m / commSize;

    int start = rank * offset, stop = rank == (commSize - 1) ? (n >= m ? n : m) : (rank + 1) * offset;

    if (rank == 0)
    {
        cout << endl;
        double time = MPI_Wtime();

        if (n >= m)
        {
            for (int i = start; i < stop; i++)
            {
                c[i] = 0;
                for (int j = 0; j < m; j++)
                    c[i] += mat[i][j] * b[j];
            }

            time -= MPI_Wtime() - time;

            for (int i = 1; i < commSize; i++)
            {
                double *arr = new double[offset];
                MPI_Recv(arr,offset,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
                for (int j = i * offset; j < (i + 1) * offset; j++)
                    c[j] = arr [j - i * offset];
                delete [] arr;
                double t = 0.0;
                MPI_Recv(&t,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
                time += t;
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                c[i] = 0;
                for (int j = start; j < stop; j++)
                    c[i] += mat[i][j] * b[j];
            }

            time -= MPI_Wtime() - time;

            for (int i = 1; i < commSize; i++)
            {
                double *arr = new double[n];
                MPI_Recv(arr,n,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
                for (int j = 0; j < n; j++)
                    c[j] += arr [j];
                delete [] arr;
                double t = 0.0;
                MPI_Recv(&t,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
                time += t;
            }
        }
        ofstream C(fileC), Time(fileTime);

        for (int i = 0; i < c.size(); i++)
            C << c[i] << endl;

        Time << time << endl;
    }
    else
    {
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

        if (n >= m)
        {
            double time = MPI_Wtime();
            vector<double> res(offset);

            for (int i = start; i < stop; i++)
            {
                res[i - start] = 0;
                for (int j = 0; j < m; j++)
                    res[i - start] += mat[i][j] * b[j];
            }
            time -= MPI_Wtime() - time;

            MPI_Send(Matrix::toArr(res), offset, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            res.clear();
            MPI_Send(&time,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
        }
        else
        {
            double time = MPI_Wtime();
            vector<double> res(n);

            for (int i = 0; i < n; i++)
            {
                res[i] = 0;
                for (int j = start; j < stop; j++)
                    res[i] += mat[i][j] * b[j];
            }
            time -= MPI_Wtime() - time;

            MPI_Send(Matrix::toArr(res), offset, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            res.clear();
            MPI_Send(&time,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();

    return c;
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
       throw -1;
    }

    int n,m;
    file >> n >> m;

    if (n < 0 || m < 0)
    {
        cerr << "Неверный формат файла" << endl;
        throw -1;
    }

    Matrix res(n,m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (file.eof())
            {
                cerr << "Неверный формат файла" << endl;
                throw -1;
            }
            file >> res.mat[i][j];
        }
    }

    return res;
}

double* Matrix::toArr(const vector<double> &v)
{
    double *res = new double[v.size()];

    for (int i = 0; i < v.size(); i++)
        res[i] = v[i];

    return res;
}

vector<double> Matrix::toVector(double* arr,int n)
{
    vector<double> res(n);

    for (int i = 0; i < n; i++)
        res[i] = arr[i];

    return res;
}

vector<double> Matrix::getVec(string filename) const
{
    ifstream file(filename);

    if (!file.is_open() || file.eof())
    {
        cerr << "Не удалось открыть файл" << endl;
        throw -1;
    }

    vector<double> res(m);

    for (int i = 0; i < m; i++)
    {
        if (file.eof())
        {
            cerr << "Неверный формат файла" << endl;
            throw -1;
        }
        file >> res[i];
    }

    return res;
}