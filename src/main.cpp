#include <fstream>

#include "../inc/primary.h"

int main(int argc,char **argv)
{
    if (argc != 6)
    {
        cerr << "Неверные параметры командной строки" << endl;
        return -1;
    }
    int first = stoi(string(argv[1])), last = stoi(string(argv[2]));

    Primary primary(first,last);
    primary.parallelFindPrimaries(string(argv[3]),string(argv[4]),string(argv[5]));
    return 0;
}