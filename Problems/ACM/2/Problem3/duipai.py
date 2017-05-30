import os
import random
import time
datasize = [10]
for i in range(1):
    print("data %d %d " % (i,datasize[i]))
    os.system('gen.cpp.exe ' + str(random.randint(545412, 2561540)) +' '+ str(datasize[i]))
    os.system('copy lln.in cjy.in')
    f = open('lln.in', 'r')
    print("data size: %s " % (f.readline()),end='')
    f.close()
    start = time.clock()
    os.system('lln.exe')
    end = time.clock()
    print("read: %f s" % (end - start))
    start = time.clock()
    os.system('cjy.exe')
    end = time.clock()
    print("read: %f s" % (end - start))
    print()
    '''os.system('copy lln.in problem' + str(i) + '.in')
    os.system('copy lln.out problem' + str(i) + '.out')'''
    os.system('fc lln.out cjy.out')
    os.system('pause')
