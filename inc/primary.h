#include <iostream>
#include <mpi.h>
#include <cmath>
#include <algorithm>

#define PRIMARY 0
#define NOT_PRIMARY 1

using namespace std;

class Primary
{
    static void findPrimaries(int *totalPrimes, int first, int last, int procNum, int rank);

public:

    static void mainPrimaries(int first,int last);
};
