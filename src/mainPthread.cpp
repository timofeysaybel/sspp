#include "../inc/primary.h"

using namespace std;

int *subPrimaries;
int *primaries;
int l;
int first, last;

void *threadFunction(void *args);

void mainPrimaries(int threadNum);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << "Неверные аргументы командной строки" << endl;
        return -1;
    }

    first = atoi(argv[1]);
    last = atoi(argv[2]);
    int threadNum = atoi(argv[3]);
    
    mainPrimaries(threadNum);
    
    return 0;
}

void mainPrimaries(int threadNum)
{
    int len = last - first;
    l = sqrt(last);

    subPrimaries = new int[l + 1];

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

    int partSize = (last - first) / threadNum + 1;

    pthread_t threads[threadNum];
    pthread_attr_t threadAttributes;

    pthread_attr_init(&threadAttributes);

    primaries = new int[(((last - first) / threadNum + 1) * threadNum)];

    for (int i = 0; i < threadNum; i++)
    {
        int *boundaries = new int[2];
        boundaries[0] = i * partSize + first;
        boundaries[1] = i == threadNum - 1 ? len - 1 + first : boundaries[0] + partSize - 1;
        int res = pthread_create(&threads[i], &threadAttributes, threadFunction, (void *)boundaries);
    }

    for (int i = 0; i < threadNum; i++)
    {
        int res = pthread_join(threads[i], NULL);
    }

    if (first == 1)
    {
        primaries[0] = 0;
    }

    int result = count(primaries, &primaries[last - first], 1);
    cout << result << endl;

    delete[] primaries;
    delete[] subPrimaries;
}

void *threadFunction(void *args)
{
    int *boundaries = ((int *)args);
    int start = boundaries[0];
    int stop = boundaries[1];

    for (int i = start; i <= stop; i++)
    {
        primaries[i - first] = 1;
    }

    for (int i = 2; i <= l; i++)
    {
        if (subPrimaries[i])
        {
            int a = ceil((start - i * i) * 1.0 / i) < 0 ? 0 : ceil((start - i * i) * 1.0 / i);
            for (int j = i * i + a * i; j <= stop; j += i)
            {
                primaries[j - first] = 0;
            }
        }
    }

    pthread_exit(0);
}