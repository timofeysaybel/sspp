#include <mpi.h>
#include <cmath>
#include <fstream>

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

vector<int> Primary::parallelFindPrimaries(string filename,string allName,string maxName)
{
    int rank, commSize;
    vector<int> primaries;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);

    int childStart = sqrt(last) > first ? sqrt(last) : first;
    int childSize = (last - childStart) / (commSize - 1);
    MPI_Status status;

    if (rank == 0)
    {
        cout << endl;
        double start = MPI_Wtime();
        int l = commSize == 1 ? last : sqrt(last) + 1;

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

        int sz = primaries.size();

        for (int i = 1; i < commSize; i++)
            MPI_Send(toIntArr(primaries), primaries.size(), MPI_INT, i, 0, MPI_COMM_WORLD);

        double time = 0.0, max = 0.0;
        for (int i = 1; i < commSize; i++)
        {
            int *buffer = new int[childSize];
            MPI_Recv(buffer, childSize, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            vector<int> tmp = toVector(buffer, childSize);
            for (auto e : tmp)
            {
                if (e != NOT_PRIMARY)
                    primaries.push_back(e);
            }
            delete[] buffer;
            tmp.clear();
            MPI_Recv(&time,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,&status);
            if (time > max)
                max = time;
        }

        for (int i = 0; i < primaries.size(); i++)
        {
            if (primaries[i] < first)
            {
                primaries.erase(primaries.begin() + i);
                i--;
            }
        }
        double stop = MPI_Wtime();

        if (commSize == 1)
        {
            max = stop - start;
        }

        ofstream all(allName,ios_base::app);
        ofstream maximum(maxName ,ios_base::app);
        all << commSize << "\t" << stop - start << endl;
        maximum << commSize << "\t" << max << endl;

        all.close();
        maximum.close();
        save(primaries,filename);
        cout << "Количество простых чисел: " <<  primaries.size() << endl;
    }
    else
    {
        double time = MPI_Wtime();
        int n;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &n);
        
        int *arr = new int[n];

        MPI_Recv(arr, n, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        vector<int> pr = toVector(arr, n);

        int start = childStart + 1 + (rank - 1) * childSize, stop = childStart + 1 + rank * childSize;

        for (int i = 0; i < pr.size(); i++)
            fill(pr[i], stop, start);

        vector<int> childPrimaries(childSize, NOT_PRIMARY);

        for (int i = start, j = 0; i < stop; j++, i++)
        {
            if (numbers[i] == PRIMARY)
            {
                if (i >= first)
                    childPrimaries[j] = i;
            }
        }
        delete[] arr;
        pr.clear();
        MPI_Send(toIntArr(childPrimaries), childSize, MPI_INT, 0, 0, MPI_COMM_WORLD);
        childPrimaries.clear();
        time = MPI_Wtime() - time;
        MPI_Send(&time,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
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

void Primary::save(vector<int> numbers, string filename)
{
    ofstream file(filename);

    for (auto e : numbers)
        file << e << " ";
    file.close();
}

void Primary::print(vector<int> numbers)
{
    for (auto e : numbers)
        cout << e << " ";
    cout << endl;
}