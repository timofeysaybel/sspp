#include "../inc/matrix.h"

int main(int argc, char **argv)
{
    try
    {
        if (argc != 4)
        {
            cerr << "Неверные параметры командной строки" << endl;
            return -1;
        }

        const string TIME_FILE = "report/time.dat";

        Matrix matrix = Matrix::getFromFile(string(argv[1]));
        auto b = matrix.getVec(string(argv[2]));
        matrix.parallelMultiply(b, string(argv[3]), TIME_FILE);
        return 0;
    }
    catch (int)
    {
        return -1;
    }
}

