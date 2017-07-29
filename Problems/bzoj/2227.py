def gcd(a,b):
    if a % b==0:
        return b
    else:
        return gcd(b, a % b)
t = int(raw_input())
while (t>0):
    t-=1
    num=raw_input().split()
    n=int(num[0])
    k=int(num[1])
    ans=pow(k+1,n-1)*(k+1-n)
    ans2=pow(k,n)
    gcd1=gcd(ans,ans2)
    print ans//gcd1,ans2//gcd1