#include "../../inc/matrix.h"

int main(int argc,char **argv)
{
    if (argc != 4)
    {
        cerr << "Неверные параметры комадной строки" << endl;
        return -1;
    }
    string fileA = string(argv[1]);
    string fileB = string(argv[2]);
    int blockSize = stoi(string(argv[3]));
    Matrix A = Matrix::getFromFile(fileA);
    Matrix B = Matrix::getFromFile(fileB);
    Matrix C = A*B;
    Matrix C1 = A.blockMultiply(B,blockSize);
    if (!(C == C1))
    {
        cerr << "Умножение некорректно" << endl;
        return -1;
    }
    cout << "Умножение корректно" << endl;
    return 0;
}