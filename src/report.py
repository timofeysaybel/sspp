import os
import random

mapping = ["XYZT","XYZT","YZXT","YXZT","ZXYT","ZYXT","TXZY","TYZX","TYXZ","TZXY","TZYX"]
time = " -w 00:05:00 "

print("Started...")

procs = ["1","32","64","128","256","512"]

for proc in procs:
    os.system("mpisubmit.bg -n " + proc + time + " multiply.out matrix/A0 matrix/b0 matrix/c0 report/time0.dat report/speedup0.dat report/efficiency0.dat");
    os.system("mpisubmit.bg -n " + proc + time + " multiply.out matrix/A1 matrix/b1 matrix/c1 report/time1.dat report/speedup1.dat report/efficiency1.dat");
    os.system("mpisubmit.bg -n " + proc + time +" multiply.out matrix/A2 matrix/b2 matrix/c2 report/time2.dat report/speedup2.dat report/efficiency2.dat");

map = random.choice(mapping)
os.system("mpisubmit.bg -n " + procs[len(procs)-1] + " -env \"BG_MAPPING=" + map + "\"" + time + " multiply.out matrix/A0 matrix/b0 matrix/c0 report/time0.dat report/speedup0.dat report/efficiency0.dat mode");
os.system("mpisubmit.bg -n " + procs[len(procs)-1] + " -env \"BG_MAPPING=" + map + "\"" + time + " multiply.out matrix/A1 matrix/b1 matrix/c1 report/time1.dat report/speedup1.dat report/efficiency1.dat mode");
os.system("mpisubmit.bg -n " + procs[len(procs)-1] + " -env \"BG_MAPPING=" + map + "\"" + time + " multiply.out matrix/A2 matrix/b2 matrix/c2 report/time2.dat report/speedup2.dat report/efficiency2.dat mode");

print("Successfully finished")
