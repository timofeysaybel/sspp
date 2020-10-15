#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    for (int i = 0; i < 6; i++)
    {
        string cmd = "./multiply.out matrix/mA matrix/mB matrix/res ";
        cmd = cmd + to_string(i);
        system(cmd.c_str());
    }
    return 0;
}
