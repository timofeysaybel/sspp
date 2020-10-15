#include "../../inc/matrix/matrix.h"

using namespace std;

int findType(string fileA,string fileB)
{
    ifstream fa(fileA), fb(fileB);

    if (!fa.is_open() || !fb.is_open())
    {
        cerr << "Не удалось открыть файлы" << endl;
        throw -1;
    }

    char typeA, typeB;
    fa >> typeA;
    fb >> typeB;

    if (typeA != typeB || typeA != 'f' && typeA != 'd')
    {
        cerr << "Разные типы элементов матриц" << endl;
        throw -1;
    }
    fa.close();
    fb.close();
    return typeA == 'f' ? 0 : 1;
}

bool cmp(string mul,string res)
{
    if (findType(mul,res) == 0)
    {
        Matrix<float> m1(mul),m2(res);

        return m1.cmpMatrix(m2);
    }
    if (findType(mul,res) == 1)
    {
        Matrix<double> m1(mul),m2(res);

        return m1.cmpMatrix(m2);
    }

    return true;
}

int main()
{
    for (int i = 0; i < 6; i++)
    {
        string cmd = "./multiply.out matrix/tA matrix/tB matrix/tres ";
        string cmdf = "./multiply.out matrix/ftA matrix/ftB matrix/ftres ";
        cmd = cmd + to_string(i);
        cmdf = cmdf + to_string(i);
        system(cmd.c_str());
        system(cmdf.c_str());
        if (!cmp("matrix/tres","matrix/tresult") || !cmp("matrix/ftres","matrix/tfresult"))
        {
            cerr << "Умножение некорректно" << endl;
        }
    }
    cout << "Умножение корректно" << endl;
    return 0;
}

