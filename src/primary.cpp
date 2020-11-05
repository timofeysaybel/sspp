#include <mpi.h>
#include <cmath>

#include "../inc/primary.h"

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
    fill(2);
    fill(3);

    for (int i = 4; i < numbers.size(); i++)
    {
        if (numbers[i] == PRIMARY)
        {
            if (i >= first)
                primaries.push_back(i);
            fill(i);
        }
    }

    return primaries;
}

void Primary::fill(int index,int stop,int start)
{
    if (start == -1)
        start = index + 1;
    if (stop == -1)
        stop = numbers.size();

    for (int i = start; i < stop; i++)
    {
        if (i % index == 0)
            numbers[i] = NOT_PRIMARY;
    }
}

vector<int> Primary::parallelFindPrimaries()
{
    int rank, commSize;
    vector<int> primaries;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    int childSize = (last - sqrt(last)) / commSize;
    MPI_Status status;

    if (rank == 0)
    {
        vector<int> rootPrimaries;
        int l = sqrt(last) + 1;

        if (l < 4)
        {
            if (first <= 3)
            {
                rootPrimaries.push_back(2);
                primaries.push_back(3);
            } else
            {
                if (first <= 2)
                    rootPrimaries.push_back(2);
            }

        } else
        {
            if (first <= 3)
            {
                rootPrimaries.push_back(2);
                rootPrimaries.push_back(3);
            }
            fill(2, l);
            fill(3, l);

            for (int i = 4; i < l; i++)
            {
                if (numbers[i] == PRIMARY)
                {
                    if (i >= first)
                        rootPrimaries.push_back(i);
                    fill(i, l);
                }
            }
        }
        for (int i = 1; i < commSize; i++)
            MPI_Send(&rootPrimaries[0], l, MPI_INT, i, 0, MPI_COMM_WORLD);

        primaries.insert(primaries.end(), rootPrimaries.begin(), rootPrimaries.end());

        for (int i = 1; i < commSize; i++)
        {
            int *buffer = new int[childSize];
            MPI_Recv(&buffer, childSize, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            vector<int> tmp = toVector(buffer, childSize);
            for (auto e : tmp)
            {
                if (e != NOT_PRIMARY)
                    primaries.push_back(e);
            }

            delete[] buffer;
            tmp.clear();
        }
    } else
    {
        int n;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &n);

        int *arr = new int[n];

        MPI_Recv(arr, n, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        vector<int> pr = toVector(arr, n);

        int start = sqrt(last) + 1 + (rank - 1) * childSize, stop = sqrt(last) + 1 + rank * childSize;

        for (int i = 0; i < pr.size(); i++)
            fill(pr[i], stop, start);

        vector<int> childPrimaries(childSize,NOT_PRIMARY);

        for (int i = start, j = 0; j < childSize, i < stop; j++, i++)
        {
            if (numbers[i] == PRIMARY)
            {
                if (i >= first)
                    childPrimaries[j] = i;
            }
        }
        delete [] arr;
        pr.clear();
        MPI_Send(&childPrimaries[0], childSize, MPI_INT, 0, 0, MPI_COMM_WORLD);
        childPrimaries.clear();
    }
    MPI_Finalize();

    return primaries;
}

int* Primary::toIntArr(const vector<int> &v)
{
    int *res = new int[v.size()];

    for (int i = 0; i < v.size(); i++)
        res[i] = v[i];

    return res;
}

vector<int> Primary::toVector(int* arr,int n)
{
    vector<int> res(n);

    for (int i = 0; i < n; i++)
        res[i] = arr[i];

    return res;
}