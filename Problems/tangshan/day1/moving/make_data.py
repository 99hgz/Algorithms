import numpy as np
n=1000
m=1000
print(n,m)
for i in range(n):
    print(np.random.randint(0,100000 + 1),end=' ')
print()
for i in range(m):
    if(np.random.randint(0,10 + 1)>6):
        l=np.random.randint(1,n + 1)
        r=np.random.randint(l,n + 1)
        print(1,l,r,np.random.randint(2,(10000 if(np.random.randint(0,100 + 1)>6) else 10)  + 1))
    else:
        l=np.random.randint(1,n + 1)
        r=np.random.randint(l,n + 1)
        print(2,l,r)