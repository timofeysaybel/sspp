#include "../inc/matrix.h"

int main(int argc, char **argv)
{
    try
    {
        if (argc < 7)
        {
            cerr << "Неверные параметры командной строки" << endl;
            return -1;
        }
        int mode = 0;
        if (argc == 8)
            mode = 1;
        const string TIME_FILE = string(argv[4]);
        const string SPEED_UP_FILE = string(argv[5]);
        const string EFFICIENCY_FILE = string(argv[6]);

        Matrix matrix = Matrix::getFromFile(string(argv[1]));
        vector<double> b = matrix.getVec(string(argv[2]));
        matrix.parallelMultiply(b, string(argv[3]), TIME_FILE,SPEED_UP_FILE,EFFICIENCY_FILE,mode);
        return 0;
    }
    catch (int)
    {
        return -1;
    }
}

