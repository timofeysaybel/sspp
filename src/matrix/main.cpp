#include "../../inc/matrix.h"

int main(int argc,char **argv)
{
    if (argc != 6)
    {
        cerr << "Неверные параметры комадной строки" << endl;
        return -1;
    }
    string fileA = string(argv[1]);
    string fileB = string(argv[2]);
    string fileC = string(argv[3]);
    int blockSize = stoi(string(argv[4]));
    int mode = stoi(string(argv[5]));
    Matrix A = Matrix::getFromFile(fileA);
    Matrix B = Matrix::getFromFile(fileB);
    if (mode == 0)
    {
        Matrix C = A.blockMultiply(B,blockSize);
        C.saveMatrix(fileC);
    }
    else
    {
        Matrix C = A.ikj(B,blockSize);
        C.saveMatrix(fileC);
    }

    return 0;
}