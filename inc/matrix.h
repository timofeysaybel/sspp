#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Matrix
{
    vector<vector<double> > mat;
    size_t n,m;

    static double* toArr(const vector<double> &v);

    static vector<double> toVector(double* arr,int n);

public:

    Matrix() {}

    Matrix(const Matrix &another);

    Matrix(size_t n1,size_t m1);

    ~Matrix();

    static Matrix getFromFile(string filename);

    Matrix operator=(const Matrix &another);

    Matrix operator*(const Matrix &another) const;

    vector<double> operator*(const vector<double> &vec) const;

    vector<double> parallelMultiply(const vector<double> &b,string fileC,string fileTime) const;

    void print(ostream &stream = cout) const;

    vector<double> getVec(string filename) const;
};
