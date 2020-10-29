#include <iostream>
#include <fstream>
#include <cmath>

#include "papi.h"
#include "../../inc/matrix.h"

#define EVENT_COUNT 4
#define CACHE 65536

using namespace std;

int events[] = {PAPI_TOT_CYC,PAPI_L1_DCM,PAPI_L2_DCM,PAPI_FP_OPS};
long long values[EVENT_COUNT] = {0,0,0,0};

void save(string filename,int arr[3]);
int execute(string fileA,string fileB,int mode);
int block_size(int c);

int main(int argc,char **argv)
{
    if (argc != 3)
    {
	cerr << "Неверные параметры командной строки" << endl;
	return -1;
    }
	
    ofstream l1("report/l1.dat"),l2("report/l2.dat"),cyc("report/cyc.dat"),flop("report/flop.dat");   
 
    if (PAPI_VER_CURRENT != PAPI_library_init(PAPI_VER_CURRENT))
    {
        cerr << "PAPI_library_init error" << endl;
        return -1;
    }
    
    for (int i = 0; i < 3; i++)
    {
	values[0] = 0;
	values[1] = 0;
	values[2] = 0;
	values[3] = 0;
        PAPI_start_counters(events,EVENT_COUNT);
        execute(string(argv[1]),string(argv[2]),i);
	PAPI_stop_counters(values,EVENT_COUNT);	
	cyc << i << "\t" << values[0] << endl;
	l1 << i << "\t" << values[1] << endl;
	l2 << i << "\t" << values[2] << endl;
	flop << i << "\t" << values[3] << endl;
    }
    
    return 0;
}

void save(string filename,int arr[3])
{
    ofstream file(filename);

    for (int i = 0; i < 3; i++)
        file << i << "\t" << arr[i] << endl;
}

int execute(string fileA,string fileB,int mode)
{
    Matrix A = Matrix::getFromFile(fileA);
    Matrix B = Matrix::getFromFile(fileB);

    Matrix C;
    switch(mode)
    {
        case 0:
            C = A.blockMultiply(B,32);
            break;
        case 1:
            C = A.ikj(B,32);
            break;
        case 2:
            C = A.ikj(B,block_size(CACHE));
            break;
        default:
            cerr << "Неверные параметры комадной строки" << endl;
            return -1;
    }
    return 0;
}

int block_size(int c)
{
	return sqrt(c/3);
}
