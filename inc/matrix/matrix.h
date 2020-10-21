#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template<typename T>
class Matrix
{
    vector<vector<T> > mat;
    size_t n,m;

public:

    Matrix<T>() : n(0),m(0),mat() {}

    Matrix<T>(string filename);

    Matrix<T>(const Matrix<T> &another);

    Matrix<T> operator=(const Matrix<T> &another);

    ~Matrix<T>();

    Matrix<T> ijk(const Matrix<T> &another) const;

    Matrix<T> jik(const Matrix<T> &another) const;

    Matrix<T> ikj(const Matrix<T> &another) const;

    Matrix<T> kij(const Matrix<T> &another) const;

    Matrix<T> jki(const Matrix<T> &another) const;

    Matrix<T> kji(const Matrix<T> &another) const;

    void print(ostream &stream) const;

    void saveMatrix(string filename,char mode) const;

    bool cmpMatrix(const Matrix<T> &another) const;
};
