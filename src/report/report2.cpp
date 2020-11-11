#include <iostream>

using namespace std;

int main()
{
	for (int i = 1; i <= 8; i*=2)
	{
		string cmd = string("mpirun -n ") + to_string(i) + string(" primary.out 1 100000000 result.txt");
		system(cmd.c_str());
	}


	return 0;
}
