import os
import random
import time
datasize = [1000,1000,1000,1000,1000,30000, 30000, 30000, 30000, 30000]
for i in range(10):
    print("data %d %d " % (i,datasize[i]))
    os.system('gen.exe ' + str(random.randint(545412, 2561540)) +' '+ str(datasize[i]))
    f = open('lln.in', 'r')
    print("data size: %s " % (f.readline()),end='')
    f.close()
    start = time.clock()
    os.system('lln.exe')
    end = time.clock()
    print("read: %f s" % (end - start))
    print()
    os.system('copy lln.in problem' + str(i) + '.in')
    os.system('copy lln.out problem' + str(i) + '.out')
