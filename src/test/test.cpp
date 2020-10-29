#include "../../inc/matrix.h"
#include <cmath>

#define FILES 3

using namespace std;

int main()
{
    string A("matrix/tA");
    string B("matrix/tB");
    for (int i = 0; i < FILES; i++)
        system((string("./multiply.out ") + A + to_string(i) + string(" ") + B + to_string(i) + " " + to_string(32)).c_str());
    return 0;
}