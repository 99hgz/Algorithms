n=input()
f=[]
f.append(0)
f.append(1)
f.append(5)
for i in range(3,n+1):
    f.append(f[i-1]*3-f[i-2]+2)
print f[n]
