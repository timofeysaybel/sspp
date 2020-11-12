#include <iostream>
#include <unistd.h>

#define PROC_NUM 20

using namespace std;

int main()
{
	for (int i = 1; i <= PROC_NUM; i*=2)
	{
		string cmd = string("mpisubmi.pl -p ") + to_string(i) + (" primary.out 1 1000000 result.txt report/all.dat report/max.dat");
		system(cmd.c_str());
	}

	return 0;
}
