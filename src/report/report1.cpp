#include <iostream>

using namespace std;

int main()
{
	int start = 10;
	int stop = 1e8;
	for (int i = start; i <= stop; i*=10)
	{
		string cmd = string("mpirun primary.out 1 ") + to_string(i) + string(" result.txt");
		system(cmd.c_str());
	}
	return 0;
}
