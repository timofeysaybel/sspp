#include <iostream>
#include <vector>

#define PRIMARY 0
#define NOT_PRIMARY 1

using namespace std;

class Primary
{
    vector<int> numbers;
    int first, last;

    void fill(int index, int stop = -1, int start = -1);

    int *toIntArr(const vector<int> &v);

    vector<int> toVector(int* arr, int);

    void print(vector<int> numbers);

    void save(vector<int> numbers, string filename);

public:
    Primary()
    {}

    Primary(const Primary &another);

    Primary(int f, int l);

    ~Primary();

    Primary operator=(const Primary &another);

    vector<int> findPrimaries();

    vector<int> parallelFindPrimaries();
};
