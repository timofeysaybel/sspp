#include <vector>

struct Result
{
    std::vector<int> primaries;
    std::vector<int> childPrimaries;
    int last,first;
    double threadTime;
    int threadNum;
    int amountOfThreads;
};
