import os
import random
import time
datasize = [100, 200, 1000, 5000, 10000, 10000, 50000, 100000, 100000, 150000]
for i in range(10):
    print("data %d %d " % (i,datasize[i]))
    os.system('gen.cpp.exe ' + str(random.randint(545412, 2561540)) +' '+ str(datasize[i]))
    f = open('lln.in', 'r')
    print("data size: %s " % (f.readline()))
    f.close()
    os.system('copy lln.in problem' + str(i) + '.in')
    '''
    start = time.clock()
    os.system('hzwer.cpp.exe')
    end = time.clock()
    print("read: %f s" % (end - start))
    '''