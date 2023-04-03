import numpy as np
n1=5000
print(n1)
pre=np.random.permutation(n1)+1
for x in pre:
    print(x,end=' ')
