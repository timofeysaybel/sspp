#include <chrono>

#include "../../inc/matrix/multiplier.h"

#define N 10

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

    return typeA == 'f' ? 0 : 1;
}


int main(int argc, char **argv)
{
    if (argc != 5)
    {
        cerr << "Неверные аргменты командной строки" << endl;
        return -1;
    }
    string args[] = {string(argv[1]),string(argv[2]),string(argv[3]),string(argv[4])};
    int mode = findType(args[0],args[1]);
    clock_t sum = clock();
    try
    {
        if (mode == 0)
        {
            for (int i = 0; i < N; i++)
            {
                Multiplier<float> mltplr(args);
                mltplr.multiply();
            }
        }
        else
        {
            for (int i = 0; i < N; i++)
            {
                Multiplier<double> mltplr(args);
                mltplr.multiply();
            }
        }
    }
    catch (int)
    {
        return -1;
    }

    sum = clock() - sum;
    cout << args[3] << "\t" << static_cast<double>(static_cast<double>(sum/N)/CLOCKS_PER_SEC) << endl;

    return 0;
}
