#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pr;
#define mp make_pair

priority_queue<pr> q;
ll n,k,a[100010],Next[200010],Last[200010],val[200010],tot,ans;
bool del[200010];
ll block[200010],cnt;

bool cmp(ll a,ll b){
    return a>b;
}

int main() {
    scanf("%lld%lld", &n,&k);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (ll i = 1; i <= n; i++)
        if (a[i]!=0) a[++cnt]=a[i];
    n=cnt;

    ll start=1;
    while(a[start]<0)start++;
    ll ed=n;
    while(a[ed]<0)ed--;
    cnt=0;
    for(ll i=start;i<=ed;i++)
        a[++cnt]=a[i];
    n=cnt;
    cnt=0;
    for (ll i = 1; i <= n; i++)
        if (i==1||(a[i]>0)!=(a[i-1]>0))
            block[++cnt]=a[i];
        else
            block[cnt]+=a[i];
    n=cnt;
    cnt=0;
    for (ll i = 1; i <= n; i++){
        if (block[i]>0){
            ans+=block[i];
            cnt++;
        }
        val[i]=abs(block[i]);
        q.push(mp(-abs(block[i]),i));
    }

    if (cnt<=k){
        sort(block+1,block+1+n,cmp);
        ans=0;
        for (ll i = 1; i <= cnt; i++)
            ans+=block[i];
        printf("%lld\n", ans);
        //system("pause");
        return 0;
    }

    for (ll i = 1; i <= n; i++)
        Next[i]=i+1,Last[i]=i-1;
    Next[n]=Last[1]=0;
    tot=n;
    k=cnt-k;
    while(k--){
        while(del[q.top().second])q.pop();
        pr tmp=q.top();
        q.pop();
        ans-=val[tmp.second];
        ll u=tmp.second;
        del[Next[u]]=del[u]=del[Last[u]]=1;
        Last[Next[u]]=Next[Last[u]]=0;
        if (!Last[u]) Last[Next[Next[u]]]=0;
        else if (!Next[u]) Next[Last[Last[u]]]=0;
        else{
            tot++;
            val[tot]=val[Last[u]]+val[Next[u]]-val[u];
            Next[tot]=Next[Next[u]];
            Last[tot]=Last[Last[u]];
            if (Last[tot]) Next[Last[tot]]=tot;
            if (Next[tot]) Last[Next[tot]]=tot;
            q.push(mp(-val[tot],tot));
        }
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}