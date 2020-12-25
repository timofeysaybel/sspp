#include <vector>

struct Result
{
    std::vector<int> numbers;
    int *childPrimaries;
    int size;
    int last,first;
    int threadNum;
    int amountOfThreads;
};