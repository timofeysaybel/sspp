#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Matrix
{
    vector<vector<float>> mat;
    size_t n,m;

public:

    Matrix() {}

    Matrix(const Matrix &another);

    Matrix(size_t n1,size_t m1);

    ~Matrix();

    static Matrix getFromFile(string filename);

    Matrix operator=(const Matrix &another);

    Matrix operator*(const Matrix &another) const;

    Matrix blockMultiply(const Matrix &another,size_t sizeOfBlock) const;

    void print(ostream &stream = cout) const;

    bool operator==(const Matrix &another) const;
};
