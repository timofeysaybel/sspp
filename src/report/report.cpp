#include <iostream>
#include <unistd.h>

#define PROC_NUM 20

using namespace std;

int main()
{
    //int n = sysconf(_SC_NPROCESSORS_ONLN);
	for (int i = 1; i <= PROC_NUM; i*=2)
	{
		string cmd = string("mpirun -n ") + to_string(i) + string(" primary.out 1 100000 result.txt report/all.dat report/max.dat");
		system(cmd.c_str());
	}
	return 0;
}
