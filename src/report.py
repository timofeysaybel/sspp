import os
from random import shuffle

file = open('xyzt.map', 'w')

xyzt = []
for x in range(8):
    for y in range(8):
        for z in range(8):
            xyzt.append('%s %s %s 0\n' % (x, y, z))

shuffle(xyzt)

for item in xyzt:
    file.write(item)

file.close()

time = " -w 00:05:00 "

print("Started...")

procs = ["1", "32", "64", "128", "256", "512"]

for proc in procs:
    os.system(
        "mpisubmit.bg -n " + proc + time + " multiply.out matrix/A0 matrix/b0 matrix/c0 report/time0.dat report/speedup0.dat report/efficiency0.dat")
    os.system(
        "mpisubmit.bg -n " + proc + time + " multiply.out matrix/A1 matrix/b1 matrix/c1 report/time1.dat report/speedup1.dat report/efficiency1.dat")
    os.system(
        "mpisubmit.bg -n " + proc + time + " multiply.out matrix/A2 matrix/b2 matrix/c2 report/time2.dat report/speedup2.dat report/efficiency2.dat")

os.system("llsubmit jcf/Map0.jcf")
os.system("llsubmit jcf/Map1.jcf")
os.system("llsubmit jcf/Map2.jcf")

print("Successfully finished")
