n=int(input())
a=[0]*(n+5)
fac=[0]*(n+5)
fac[0]=1
rest=n-2
cnt=0
st=raw_input().split(' ')
if n==1:
    if (st[0]>0):
        print("0")
        exit()
    else:
        print("1")
        exit()
for i in range(1,n+1): 
    x=int(st[i-1])
    if (x==0):
        print("0")
        exit()
    a[i]=x
    if x==-1 :
        cnt=cnt+1
    else :
        rest=rest-x+1
    fac[i]=fac[i-1]*i
if rest<0 :
    print("0")
    exit()
ans=fac[n-2]
for i in range(1,n+1):
    if a[i]!=-1 :
        ans=ans/fac[a[i]-1]
ans=ans/fac[rest]
for i in range(1,rest+1):
    ans=ans*cnt
print(int(ans))