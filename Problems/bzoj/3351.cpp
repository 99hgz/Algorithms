#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

ll pa1[450][25010],pait,block,n,r,q,c[200010],num[25010],mp[25010];
vector<ll>e[200010];
typedef pair<ll,ll>pr;
vector<pr>range[25010];
vector<ll>point[25010];
ll ts,l[200010],tr[200010],r1,r2,fa[200010];
void dfs(ll x){
    ts++;
    l[x]=ts;
    for(vector<ll>::iterator it=e[x].begin();it!=e[x].end();it++)
        dfs(*it);
    tr[x]=ts;
}

void dfs1(ll u,ll r1,ll num){
    pa1[pait][c[u]]+=num;
    if (c[u]==r1) num++; 
    for(vector<ll>::iterator it=e[u].begin();it!=e[u].end();it++)
        dfs1(*it,r1,num);
}
ll dfs2(ll u,ll r2){
    ll cnt=0;
    for(vector<ll>::iterator it=e[u].begin();it!=e[u].end();it++)
        cnt+=dfs2(*it,r2);
    pa1[pait][c[u]]+=cnt;
    if (c[u]==r2) cnt++;
    return cnt;
}

void init(){
    for (ll i = 1; i <= r; i++) 
        if (num[i]>=block){
            pait++;
            mp[i]=pait;
            dfs1(1,i,0);
            //dfs2(1,i);
        }
    dfs(1);
    for (ll i = 1; i <= n; i++) {
        range[c[i]].push_back(make_pair(l[i],1));
        range[c[i]].push_back(make_pair(tr[i]+1,-1));
    }
    for (ll i = 1; i <= r; i++) {
        sort(range[i].begin(),range[i].end());
        sort(point[i].begin(),point[i].end());
    }
}

void init2(){
    memset(pa1,0,sizeof pa1);
    pait=0;
    for (ll i = 1; i <= r; i++) 
        if (num[i]>=block){
            pait++;
            mp[i]=pait;
            //dfs1(1,i,0);
            dfs2(1,i);
        }
}

struct Q{
    ll r1,r2,id;
};
vector<Q>qu;
ll ans[200010];
int main() {
    scanf("%lld%lld%lld", &n,&r,&q);
    scanf("%lld", &c[1]);
    ll block=sqrt(n);
    num[c[1]]++;
    for (ll i = 2; i <= n; i++){ 
        scanf("%lld%lld",&fa[i],&c[i] );
        e[fa[i]].push_back(i);
        num[c[i]]++;
    }
    init();
    for (ll i = 1; i <= q; i++) {
        scanf("%lld%lld", &r1,&r2);//r1 is father
        if (num[r1]>=block)
            ans[i]=pa1[mp[r1]][r2];
        else if (num[r2]>=block)
            //printf("%lld\n", pa2[mp[r2]][r1]);
            qu.push_back((Q){r1,r2,i});
        else{
            vector<pr>::iterator it=range[r1].begin();
            ll ans1=0,cnt=0;
            for(vector<ll>::iterator it2=point[r2].begin();it2!=point[r2].end();it2++){
                while(it!=range[r1].end()&&(*it).first<=(*it2)){
                    ans1+=(*it).second;
                    it++;
                }
                cnt+=ans1;
            }
            ans[i]=cnt;
        }
    }
    init2();
    for(int i=0;i<qu.size();i++)
        ans[qu[i].id]=pa1[mp[qu[i].r2]][qu[i].r1];
    for (int i = 1; i <= q; i++) 
        printf("%lld\n", ans[i]);
    
    system("pause");
    return 0;
}