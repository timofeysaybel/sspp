#include "../../inc/matrix.h"
#include <cmath>

#define FILES 3

using namespace std;

double getOptimal()
{
    system("lscpu | grep L1d cache > tmp.txt");
    ifstream file("tmp.txt");
    int cache = 0;
    file >> cache;
    file.close();

    double res = static_cast<double>(cache);
    return res;
}


int main()
{
    string A("matrix/tA");
    string B("matrix/tB");
    for (int i = 0; i < FILES; i++)
        system((string("./multiply.out ") + A + to_string(i) + string(" ") + B + to_string(i) + " " + to_string(10)).c_str());
    return 0;
}