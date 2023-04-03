import numpy as np
#n1=np.random.random_integers(0,50000)
n1=998
print(n1)
for i in range(n1):
    for j in range(n1):
        print(np.random.random_integers(0,1000),end=' ')
    print()
