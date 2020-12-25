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

int *Primary::pthreadFindPrimaries(string filename, string allName, string maxName,int threadNum)
{
    int *primaries = new int[last - first];
    int n = 0;
    int l = threadNum == 1 ? last : sqrt(last) + 1;
    if (l < 4)
    {
        if (l <= 3)
        {
            if (first >= 2)
            {
                primaries[n] = 2;
                n++;
            }
            if (first >= 3)
            {
                primaries[n] = 3;
                n++;
            }
        } else
        {
            if (first >= 2)
            {
                primaries[n] = 2;
                n++;
            }
        }
    }
    else
    {
        if (first <= 2)
        {
            primaries[n] = 2;
            n++;
        }
        if (first <= 3)
        {
            primaries[n] = 3;
            n++;
        }
        fill(2, l);
        fill(3, l);

        for (int i = 4; i < l; i++)
        {
            if (numbers[i] == PRIMARY)
            {
                if (i >= first)
                {
                    primaries[n] = i;
                    n++;
                }
                fill(i, l);
            }
        }
    }

    vector<pthread_t> pthreads(threadNum - 1);

    vector<Result> res(pthreads.size());

    for (int i = 0; i < threadNum - 1; i++)
    {
        res[i].first = first;
        res[i].last = last;
        res[i].threadNum = i + 1;
        res[i].amountOfThreads = threadNum;
        res[i].numbers = numbers;
        if (pthread_create(&pthreads[i],NULL,pthreadCount,&(res[i])))
        {
            cerr << "Не удалось создать новый поток" << endl;
            return primaries;
        }
    }
    for (int i = 0; i < threadNum -1 ; i++)
    {
        pthread_join(pthreads[i],NULL);
        for (int j = 0; j < res[i].size; j++)
        {
            if (res[i].childPrimaries[j] >= first)
            {
                primaries[n] = res[i].childPrimaries[j];
                n++;
            }
        }
        delete [] res[i].childPrimaries;
    }
    for (int i = 0; i < n; i++)
        cout << primaries[i] << " ";
    cout << endl;
    cout << n << endl;
    delete [] primaries;
    return primaries;
}

void Primary::fill(vector<int> &numbers, int index, int stop)
{
     for (int i = index + index; i < stop; i+=index)
        numbers[i] = NOT_PRIMARY;
}

void* Primary::pthreadCount(void *res)
{
    Result *result = (Result*)res;
    
    int last = result->last,first = result->first;
    
    int childStart = sqrt(last) > first ? sqrt(last) : first;
    int childSize = (last - childStart) / (result->amountOfThreads - 1);
    
    int start = result->threadNum - 1 == 0 ? childStart + 1 : childStart + 2 + (result->threadNum - 1) * childSize;
    int stop = result->threadNum != result->amountOfThreads - 1 ? childStart + 1 + result->threadNum * childSize : last;
    
    for (int i = 2; i < sqrt(last); i++)
        fill(result->numbers,i,stop);

    result->size = 0;
    result->childPrimaries = new int [stop - start];
    for (int i = start; i < stop; i++)
    {
        if (result->numbers[i] == PRIMARY && i >= first)
        {
            result->childPrimaries[result->size] = i;
            result->size++;
        }
    }
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
