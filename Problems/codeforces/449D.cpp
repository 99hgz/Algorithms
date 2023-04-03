#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
const ll Mod=1000000007;
ll f[2000005],bin[2000005];
int n;
int read(){
    int t=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while ('0'<=ch&&ch<='9'){t=t*10+ch-'0';ch=getchar();}
    return t*f;
}
void solve(){
   for (int j=0;j<20;j++)
    for (int i=0;i<=1000000;i++)
        if ((1<<j)&i) (f[i^(1<<j)]+=f[i])%=Mod;
    ll ans=0;        
    for (int i=0;i<=1000000;i++){
        int cnt=1;
        for (int j=0;j<20;j++)
            if ((1<<j)&i) cnt=-cnt;
        ans=((ans+(cnt*(bin[f[i]]-1)%Mod))%Mod+Mod)%Mod;        
    }        
    printf("%I64d\n",ans);
}
int main(){
    n=read();
    bin[0]=1;
    for (int i=1;i<=1000000;i++) bin[i]=(bin[i-1]*2)%Mod;
    for (int i=1;i<=n;i++) f[read()]++;
    solve();
}