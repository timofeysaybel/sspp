#include "../inc/primary.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cerr << "Неверные параметры командной строки" << endl;
        return -1;
    }
    int first = atoi(argv[1]);
    int last = atoi(argv[2]);
    Primary::mainPrimaries(first,last);
    return 0;
}