#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

ll ans;
bool flag[100];
int f[70][70][70];
int sr,sb,sg,m,p,n,Next[70];
ll pow(ll a,int b){
    ll res=1;
    while(b){
        if (b&1) res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}

int calc(){
    vector<int>group;
    memset(flag,0,sizeof flag);
    for (int i = 1; i <= n; i++) {
        int len=0;
        for(int now=i;!flag[now];now=Next[now])
            len++,flag[now]=true;
        if (len) group.push_back(len);
    }
    memset(f,0,sizeof f);
    f[0][0][0]=1;
    for(vector<int>::iterator it=group.begin();it!=group.end();it++){
        for(int i=sr;i>=0;i--)
            for(int j=sb;j>=0;j--)
                for(int k=sg;k>=0;k--){
                    if (i>=*it)f[i][j][k]=(f[i][j][k]+f[i-*it][j][k])%p;
                    if (j>=*it)f[i][j][k]=(f[i][j][k]+f[i][j-*it][k])%p;
                    if (k>=*it)f[i][j][k]=(f[i][j][k]+f[i][j][k-*it])%p;
                }
    }
    return f[sr][sb][sg];
}

int main() {
    scanf("%d%d%d%d%d", &sr,&sb,&sg,&m,&p);
    n=sr+sb+sg;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) scanf("%d", &Next[j]);
        ans=(ans+calc())%p;
    }
    for (int j = 1; j <= n; j++) Next[j]=j;
        ans=(ans+calc())%p;
    
    ans=ans*pow(m+1,p-2)%p;
    printf("%lld\n", ans);
    system("pause");
    return 0;
}