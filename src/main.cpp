#include <fstream>

#include "../inc/primary.h"

void save(vector<int> numbers, string filename);

void print(vector<int> numbers);

int main(int argc,char **argv)
{
    cout << endl;
    if (argc != 4)
    {
        cerr << "Неверные параметры командной строки" << endl;
        return -1;
    }

    int first = stoi(string(argv[1])), last = stoi(string(argv[2]));
    string filename = string(argv[3]);

    Primary primary(first,last);
    auto p = primary.findPrimaries();
    auto p1 = primary.parallelFindPrimaries();
    //save(p,filename);
    print(p);
    print(p1);
    return 0;
}

void save(vector<int> numbers, string filename)
{
    ofstream file(filename);

    for (auto e : numbers)
        file << e << " ";
}

void print(vector<int> numbers)
{
    for (auto e : numbers)
        cout << e << " ";
    cout << endl;
}