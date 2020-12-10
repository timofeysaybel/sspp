#include "../inc/matrix.h"
#include <mpi.h>

#define COMMON_TIME 1

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

vector<double> Matrix::parallelMultiply(const vector<double> &b,string fileC,string fileTime,string speedUp,string efficiency,int mode) const
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

            time = MPI_Wtime() - time;

            for (int i = 1; i < commSize; i++)
            {
                int size = 0;
                MPI_Probe(i, 0, MPI_COMM_WORLD, &status);
                MPI_Get_count(&status, MPI_DOUBLE, &size);
                double *arr = new double[size];
                MPI_Recv(arr,size,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
                for (int j = 0; j < size; j++)
                    c[j + i * offset] = arr [j];
                delete [] arr;
                double t = 0.0;
                MPI_Recv(&t,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
                if (t > time)
                    time = t;
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

            time = MPI_Wtime() - time;

            for (int i = 1; i < commSize; i++)
            {
                double *arr = new double[n];
                MPI_Recv(arr,n,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
                for (int j = 0; j < n; j++)
                    c[j] += arr [j];
                delete [] arr;
                double t = 0.0;
                MPI_Recv(&t,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
                if (t > time)
                    time = t;
            }
        }
        ofstream C(fileC.c_str(),ios_base::app), Time(fileTime.c_str(),ios_base::app),SpeedUp(speedUp.c_str(),ios_base::app),Efficiency(efficiency.c_str(),ios_base::app);
        double cTime = 0.0;
        if (commSize == 1)
            cTime = time;
        else
            cTime = Matrix::getCommonTime(fileTime);
        
        for (int i = 0; i < c.size(); i++)
            C << c[i] << endl;

        Time << (mode == 0 ? commSize : commSize + 100) << "\t" << time << endl;
        SpeedUp << (mode == 0 ? commSize : commSize + 100) << "\t" << cTime / time << endl;
        Efficiency << (mode == 0 ? commSize : commSize + 100) << "\t" << (cTime / time) / commSize << endl;
    }
    else
    {

        if (n >= m)
        {
            double time = MPI_Wtime();
            vector<double> res(stop - start);

            for (int i = start; i < stop; i++)
            {
                res[i - start] = 0;
                for (int j = 0; j < m; j++)
                    res[i - start] += mat[i][j] * b[j];
            }
            time = MPI_Wtime() - time;

            MPI_Send(Matrix::toArr(res), stop - start, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
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
            time = MPI_Wtime() - time;

            MPI_Send(Matrix::toArr(res), n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            res.clear();
            MPI_Send(&time,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();

    return c;
}

double Matrix::getCommonTime(string filename)
{
    ifstream file(filename.c_str());
    double res = 0.0;

    file >> res;
    file >> res;

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
    ifstream file(filename.c_str());

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
    ifstream file(filename.c_str());

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