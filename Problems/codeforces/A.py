a=[0]
nk=raw_input().split()  
n=int(nk[0])
k=int(nk[1])
now=0
unused=0  
for x in raw_input().split():  
    a.append(int(x))
flag=False
for i in range(1,n+1):
    unused+=a[i]
    if unused>8:
        unused-=8
        now+=8
    else:
        now+=unused
        unused=0
    if now>=k:
        print i
        flag=True
        break
if flag==False:
    print -1