a=[]
  
for x in raw_input().split():  
    a.append(int(x))
n=a[0]
d=a[1]
dp[0]=1;
for i in range(1,d+1):
    dp[i]=pow(dp[i-1],n)+1
if d>0 :
    ans=dp[d]-dp[d-1]
else :
    ans=dp[d]
print ans