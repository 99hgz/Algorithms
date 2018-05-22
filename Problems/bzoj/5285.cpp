#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long ll;
ll MOD=1000000007;
int n,m,q,id[5010];
bool st[5010][1010];
bool bs[5010][1010];
bool stq[5010];
ll val[5010],rk[5010],base[5010];
bool cmp(int a,int b){
    for(int i=n-1;i>=0;i--)
        if(bs[a][i]<bs[b][i]) 
            return true;
        else if(bs[a][i]>bs[b][i])
            return false;
    return false;
}

inline void Get(bool *val){
	int cnt=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))val[++cnt]=ch-'0',ch=getchar();
}

int main() {
    scanf("%d%d%d", &n,&m,&q);
    for (int i = 1; i <= n; i++) {
        Get(st[i]);
        for(int j=1;j<=m;j++)
            bs[j][i-1]=st[i][j];
    }
    
    for(int i=1;i<=m;i++)id[i]=i;
    sort(id+1,id+1+m,cmp);
    for(int i=1;i<=m;i++)rk[id[i]]=i;
    rk[m+1]=m+1;
    base[0]=1;
    for(int i=1;i<=n;i++)base[i]=base[i-1]*2%MOD;
    val[m+1]=base[n];
    for(int i=1;i<=m;i++)
        for(int j=0;j<n;j++)
            (val[i]+=bs[i][j]*base[j])%=MOD;
    for(int i=1;i<=q;i++){
        Get(stq);
        ll mx=m+1,mn=0;
        for(int j=1;j<=m;j++)
            if(stq[j]){
                if(rk[j]<rk[mx])
                    mx=j;
            }
            else
                if(rk[j]>rk[mn])
                    mn=j;
        
        if(rk[mn]>rk[mx])
            printf("0\n");
        else
            printf("%lld\n",(val[mx]-val[mn]+MOD)%MOD);
    }
    //system("pause");
    return 0;
}