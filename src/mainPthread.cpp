#include "../inc/primary.h"

int main(int argc,char **argv)
{
    if (argc != 7)
    {
        cerr << "Неверные параметры командной строки" << endl;
        return -1;
    }

    int first = stoi(string(argv[1])), last = stoi(string(argv[2]));
    int threadNum = stoi(string(argv[6]));

    Primary primary(first,last);
    primary.pthreadFindPrimaries(string(argv[3]),string(argv[4]),string(argv[5]),threadNum);
    return 0;
}