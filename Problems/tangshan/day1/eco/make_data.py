import numpy as np

n=10
m=2000
C=100
tot=0
print(n,m,C)
for i in range(n):
        tot=tot+(np.random.randint(-18,21 + 1))
        if (tot<0):
            tot=0
        print(tot,(np.random.randint(0,9)))
for i in range(100):
    print(np.random.randint(30,40 + 1),np.random.randint(1,17 + 1))
for i in range(1900):
    print(np.random.randint(1000,3000 + 1),np.random.randint(1,3 + 1))