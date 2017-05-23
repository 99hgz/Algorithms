import os
import time
while 1:
    os.system('gen.cpp.exe')
    f = open('lln.in', 'r')
    print ("data size: %s " %(f.readline()))
    f.close()
    start = time.clock()
    os.system('lln.cpp.exe')
    end = time.clock()
    print ("read: %f s" % (end - start))
    start = time.clock()
    os.system('hzwer.cpp.exe')
    end = time.clock()
    print ("read: %f s" % (end - start))
    time.sleep(2)
