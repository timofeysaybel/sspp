#include "../inc/primary.h"

int main(int argc,char **argv)
{
    if (argc != 5)
    {
        cerr << "Неверные параметры командной строки" << endl;
        return -1;
    }

    int first = stoi(string(argv[1])), last = stoi(string(argv[2]));
    int threadNum = stoi(string(argv[4]));

    Primary primary(first,last);
    primary.pthreadFindPrimaries(string(argv[3]),string(""),string(""),threadNum);
    return 0;
}