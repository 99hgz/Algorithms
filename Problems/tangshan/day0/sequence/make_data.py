import numpy as np
n1=np.random.random_integers(0,50000)
n2=np.random.random_integers(0,50000)
n=n1+n2
print(n)
pre=np.random.permutation(n1)+1
suc=np.random.permutation(n2)+n1+1
for x in pre:
    print(x,end=' ')
for x in suc:
    print(x,end=' ')
print()
suc=np.random.permutation(n2)+n1+1
for x in pre:
    print(x,end=' ')
for x in suc:
    print(x,end=' ')