#include "matrix.h"

template <typename T>
class Multiplier
{
    Matrix<T> a,b;
    string cname;
    int mode;

public:

    Multiplier(string args[]);

    void multiply();
};

