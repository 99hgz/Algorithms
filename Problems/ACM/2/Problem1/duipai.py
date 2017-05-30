import os
import random
import time
datasize = [1000, 2000, 5000, 10000, 15000]
for i in range(5):
    print("data %d %d " % (i, datasize[i]))
    os.system('gen.cpp.exe ' + str(random.randint(545412, 2561540)) + ' ' +
              str(datasize[i]) + ' ' + str(datasize[i]))
    os.system('copy lln.in hk.in')
    f = open('lln.in', 'r')
    print("data size: %s " % (f.readline()), end='')
    f.close()
    start = time.clock()
    os.system('lln.cpp.exe')
    end = time.clock()
    print("program1--lln.cpp.exe time= %f s" % (end - start))
    start = time.clock()
    os.system('hk.cpp.exe')
    end = time.clock()
    print("program2--hk.cpp.exe time= %f s" % (end - start))
    print()
    '''
    os.system('copy lln.in problem' + str(i) + '.in')
    os.system('copy lln.out problem' + str(i) + '.out')
    '''
    os.system('fc lln.out hk.out')
    '''os.system('pause')'''
os.system('pause')