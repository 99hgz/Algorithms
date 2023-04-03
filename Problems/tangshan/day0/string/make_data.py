import numpy as np
n=np.random.random_integers(1,10000)
print(n)
for i in range(n):
    if (np.random.random_integers(0,1)>0):
        print(np.random.random_integers(0,9),end='')
    else:
        print(chr(ord('a')+np.random.random_integers(0,25)),end='')