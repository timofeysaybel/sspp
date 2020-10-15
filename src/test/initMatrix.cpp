#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
	int n = atoi(argv[2]), m = atoi(argv[3]);
	ofstream file(argv[1]);
	file << argv[4] << endl << n << endl << m << endl;
	srand(0);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			file << rand()%10 << " ";
		file << endl;
	}

	return 0;
}
