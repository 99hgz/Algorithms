#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll pre[1000020],nxt[1000020],ed[1000020],a[1000020],n,ans;
bool marked[1000020];

void solve(ll x){
    ll r=n;
    for (ll i = x+1;a[i]!=1 && i <= n; i++)
        if (!marked[a[i]])
            marked[a[i]]=true;
        else{
            r=i;
            break;
        }
    //printf("%lld\n", r);
    ll mx=0;
    for (ll i = x-1; i; i--){
        if (a[i]==1) break;
        r=min(r,nxt[i]);
        mx=max(mx,a[i]);
        if (i+mx-1<r&&i+mx-1>=x&&(pre[i+mx-1]-pre[i-1])*2LL==mx*(mx+1))
            ans=max(ans,mx);
    }
    for (ll i = x+1; a[i]!=1&&i<=n; i++)
        marked[a[i]]=false;
}

void work(){
    memset(pre,0,sizeof pre);
    memset(nxt,0,sizeof nxt);
    memset(ed,0,sizeof ed);
    for (ll i = 1; i <= n; i++){
        pre[i]=pre[i-1]+a[i];
        nxt[ed[a[i]]]=i;
        ed[a[i]]=i;
    }
    for (ll i = 1; i <= n; i++)
        if (ed[i])
            nxt[ed[i]]=0x3f3f3f3f;
    for (ll i = 1; i <= n; i++)
        if (a[i]==1)
            solve(i);
}

int main() {
    ans=1;
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    work();
    for (ll i = 1; i <= n/2; i++)
        swap(a[i],a[n-i+1]);
    work();
    printf("%lld\n", ans);
    system("pause");
    return 0;
}