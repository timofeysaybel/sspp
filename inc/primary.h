#include <iostream>
#include <vector>

#include "res_struct.h"

#define PRIMARY 0
#define NOT_PRIMARY 1

using namespace std;

class Primary
{
    vector<int> numbers;
    int first, last;

    void fill(int index, int stop = -1, int start = -1);

    void save(vector<int> numbers, string filename);

    double findMax(vector<double> v);

    double sum(vector<double> v);

    static void *pthreadCount(void *res);

public:
    Primary()
    {}

    Primary(const Primary &another);

    Primary(int f, int l);

    ~Primary();

    Primary operator=(const Primary &another);

    vector<int> findPrimaries();

    vector<int> pthreadFindPrimaries(string filename,string allName,string maxName,int threadNum);
};
