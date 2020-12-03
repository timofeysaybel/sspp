#include <cmath>
#include <fstream>
#include <chrono>
#include <algorithm>

#include <pthread.h>

#include "../inc/primary.h"

#define RESET "\033[0m"
#define RED "\033[1;31m"

Primary::Primary(const Primary &another)
{
    first = another.first;
    last = another.last;
    numbers.resize(another.numbers.size());
    for (int i = 0; i < numbers.size(); i++)
        numbers[i] = another.numbers[i];
}

Primary::Primary(int f, int l)
{
    first = f;
    last = l;
    numbers.resize(last + 1);
    for (int i = 0; i < numbers.size(); i++)
        numbers[i] = PRIMARY;
}

Primary::~Primary()
{
    numbers.clear();
}

Primary Primary::operator=(const Primary &another)
{
    first = another.first;
    last = another.last;
    numbers.resize(another.numbers.size());
    for (int i = 0; i < numbers.size(); i++)
        numbers[i] = another.numbers[i];
    return *this;
}

vector<int> Primary::findPrimaries()
{
    vector<int> primaries;
    if (last < 2)
    {
        return primaries;
    }
    if (last < 3)
    {
        if (first <= 2)
            primaries.push_back(2);
        return primaries;
    }
    if (last < 4)
    {
        if (first <= 3)
        {
            primaries.push_back(2);
            primaries.push_back(3);
        }
        return primaries;
    }
    if (first <= 3)
    {
        primaries.push_back(2);
        primaries.push_back(3);
    }
    fill(2,last + 1);
    fill(3,last + 1);

    for (int i = 4; i < numbers.size(); i++)
    {
        if (numbers[i] == PRIMARY)
        {
            if (i >= first)
                primaries.push_back(i);
            fill(i,last + 1);
        }
    }
    return primaries;
}

void Primary::fill(int index,int stop,int start)
{
    start = index + index;

    for (int i = start; i < stop; i+=index)
        numbers[i] = NOT_PRIMARY;
}

vector<int> Primary::pthreadFindPrimaries(string filename, string allName, string maxName,int threadNum)
{
    vector<int> primaries;
    vector<double> time;
    double start = clock();
    int l = threadNum == 1 ? last : sqrt(last) + 1;
    if (l < 4)
    {
        if (l <= 3)
        {
            primaries.push_back(2);
            primaries.push_back(3);
        } else
        {
            if (l <= 2)
                primaries.push_back(2);
        }
    }
    else
    {
        primaries.push_back(2);
        primaries.push_back(3);
        fill(2, l);
        fill(3, l);

        for (int i = 4; i < l; i++)
        {
            if (numbers[i] == PRIMARY)
            {
                primaries.push_back(i);
                fill(i, l);
            }
        }
    }

    double stop = clock();
    time.push_back((stop - start)/CLOCKS_PER_SEC);

    vector<pthread_t> pthreads(threadNum - 1);

    for (int i = 0; i < pthreads.size(); i++)
    {
        Result res;
        res.first = first;
        res.last = last;
        res.threadNum = i + 1;
        res.amountOfThreads = threadNum;
        if (pthread_create(&pthreads[i],NULL,pthreadCount,&res))
        {
            cerr << "Не удалось создать новый поток" << endl;
            return primaries;
        }
        pthread_join(pthreads[i],NULL);
        time.push_back(res.threadTime);

        for (int i = 0; i < res.childPrimaries.size(); i++)
            primaries.push_back(res.childPrimaries[i]);
    }

    for (int i = 0; i < primaries.size(); i++)
    {
        if (primaries[i] < first)
        {
            primaries.erase(primaries.begin() + i);
            i--;
        }
    }
    /*
    ofstream all(allName,ios_base::app);
    ofstream maximum(maxName ,ios_base::app);
    all << threadNum << "\t" << sum(time) << endl;
    maximum << threadNum << "\t" << findMax(time) << endl;

    all.close();
    maximum.close();
    save(primaries,filename);*/
    cout << "Количество простых чисел: " <<  primaries.size() << endl;

    return primaries;
}

void* Primary::pthreadCount(void *res)
{
    double begin = clock();
    Result *result = (Result*)res;
    int last = result->last,first = result->first;
    int childStart = sqrt(last) > first ? sqrt(last) : first;
    int childSize = (last - childStart) / (result->amountOfThreads - 1);
    int start = result->threadNum - 1 == 0 ? childStart + 1 : childStart + 2 + (result->threadNum - 1) * childSize;
    int stop = result->threadNum != result->amountOfThreads - 1 ? childStart + 1 + result->threadNum * childSize : last;

    Primary nums(start,stop);
    vector<int> pr = nums.findPrimaries();

    (result->childPrimaries).resize(pr.size());

    for (int i = 0; i < pr.size(); i++)
        result->childPrimaries[i] = pr[i];

    double end = clock();
    result->threadTime = (end - begin)/CLOCKS_PER_SEC;

    return NULL;
}

void Primary::save(vector<int> numbers, string filename)
{
    ofstream file(filename);

    for (auto e : numbers)
        file << e << " ";
    file.close();
}

double Primary::findMax(vector<double> v)
{
    double max = 0.0;

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] > max)
            max = v[i];
    }
    return max;
}

double Primary::sum(vector<double> v)
{
    double res = 0.0;

    for (int i = 0; i < v.size(); i++)
        res += v[i];
    return res;
}