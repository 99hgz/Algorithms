#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pr;
#define mp make_pair

priority_queue<pr> q;
ll n,k,a[100010],Next[200010],Last[200010],val[200010],tot,ans;
bool del[200010];

int main() {
    scanf("%lld%lld", &n,&k);
    for (ll i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        if (i>1){
            val[i-1]=a[i]-a[i-1];
            q.push(mp(-val[i-1],i-1));
        }
    }
    for (ll i = 1; i <= n-1; i++)
        Next[i]=i+1,Last[i]=i-1;
    Next[n-1]=Last[1]=0;
    tot=n;
    while(k--){
        while(del[q.top().second])q.pop();
        pr tmp=q.top();
        q.pop();
        ans+=val[tmp.second];
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