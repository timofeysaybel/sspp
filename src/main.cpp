#include <fstream>

#include "../inc/primary.h"

int main(int argc,char **argv)
{
    cout << endl;
    if (argc != 4)
    {
        cerr << "Неверные параметры командной строки" << endl;
        return -1;
    }

    int first = stoi(string(argv[1])), last = stoi(string(argv[2]));

    Primary primary(first,last);
    auto p1 = primary.parallelFindPrimaries();
    return 0;
}