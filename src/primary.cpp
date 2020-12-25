#include "../inc/primary.h"

#define RESET "\033[0m"
#define RED "\033[1;31m"

void Primary::mainPrimaries(int first,int last)
{
    int *primaries = NULL;
    int procNum, rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    primaries = new int[((last - first) / procNum + 1) * procNum];

    MPI_Bcast(&first, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&last, 1, MPI_INT, 0, MPI_COMM_WORLD);

    findPrimaries(primaries, first, last, procNum, rank);

    MPI_Finalize();

    if (rank == 0)
    {
        int result = count(primaries, &primaries[last - first], 1);
        cout << result << endl;        
    }
    delete[] primaries;
}

void Primary::findPrimaries(int *primaries, int first, int last, int procNum, int rank)
{
    int len = ((last - first) / procNum + 1) * procNum;
    int l = sqrt(last);
    int *subPrimaries = new int[l + 1];

    subPrimaries[0] = 0;
    subPrimaries[1] = 0;
    for (int i = 2; i <= l; ++i)
    {
        subPrimaries[i] = 1;
    }

    for (int i = 2; i <= l; ++i)
    {
        if (subPrimaries[i])
        {
            for (int j = i * i; j <= l; j += i)
            {
                subPrimaries[j] = 0;
            }
        }
    }

    int partSize = ((last - first) / procNum + 1);
    int start = rank * partSize;
    int stop = rank == procNum - 1 ? len - 1 : start + partSize - 1;
    int *buffer = new int[partSize];

    for (int i = 0; i < partSize; ++i)
    {
        buffer[i] = 1;
    }

    for (int i = 2; i <= l; ++i)
    {
        if (subPrimaries[i])
        {
            int a = ceil((start + first - i * i) * 1.0 / i) < 0 ? 0 : ceil((start + first - i * i) * 1.0 / i);
            
            for (int j = i * i + a * i; j <= stop + first; j += i)
            {
                buffer[j - start - first] = 0;
            }
        }
    }

    MPI_Gather(buffer, partSize, MPI_INT, primaries, partSize, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0 && first == 1)
    {
        primaries[0] = 0;
    }

    delete[] subPrimaries;
    delete[] buffer;
}