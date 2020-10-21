#include "../../inc/matrix/multiplier.h"

#define RES_MATRIX "matrix/result"

template class Multiplier<double>;
template class Multiplier<float>;

template <typename T>
Multiplier<T>::Multiplier(string args[]) : a(args[0]),b(args[1])
{
    cname = string(args[2]);
    mode = stoi(args[3]);
}

template<typename T>
void Multiplier<T>::multiply(char m)
{
        if (mode == 0)
        {
            Matrix<T> c(a.ijk(b));
            c.saveMatrix(cname,m);

            return;
        }
        if (mode == 1)
        {
            Matrix<T> c(a.ikj(b));

            c.saveMatrix(cname,m);
            return;
        }
        if (mode == 2)
        {
            Matrix<T> c(a.kij(b));
            c.saveMatrix(cname,m);
            return;
        }
        if (mode == 3)
        {
            Matrix<T> c(a.jik(b));
            c.saveMatrix(cname,m);
            return;
        }
        if (mode == 4)
        {
            Matrix<T> c(a.jki(b));
            c.saveMatrix(cname,m);
            return;
        }
        if (mode == 5)
        {
            Matrix<T> c(a.kji(b));
            c.saveMatrix(cname,m);
            return;
        }
        else
        {
            cerr << "Неверные параметры командной строки" <<endl;
            throw -1;
        }
}