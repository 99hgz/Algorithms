import math
import numpy as np
def func_get_prime(n):
    return filter(lambda x: not [x%i for i in range(2, int(math.sqrt(x))+1) if x%i ==0], range(2,n+1))

pr=[x for x in func_get_prime(300)]
tot=len(pr)
n1=20
n2=480
n3=500
n=n1+n2+n3
prc=[]
allc=[]
print(n)
for i in range(n1):
    c=pr[np.random.random_integers(0,tot-1)]
    prc.append(c)
    allc.append(c)

for i in range(n2):
    c1=prc[np.random.random_integers(0,n1-1)]
    c2=prc[np.random.random_integers(0,n1-1)]
    allc.append(c1*c2)

for i in range(n3):
    allc.append(np.random.random_integers(1,100000))

for x in allc:
    print(x,end=' ')