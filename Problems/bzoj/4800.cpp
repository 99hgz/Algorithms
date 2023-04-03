#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
ll m,a[50];
ll f[2000000],tot;

void dfs(int l,int r,ll sum){
    if(sum>m)return;
    if(l>r){
        f[++tot]=sum;
        return;
    }
    dfs(l+1,r,sum);
    dfs(l+1,r,sum+a[l]);
}

int main() {
    scanf("%d%lld", &n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld", &a[i]);
    int mid=n/2;
    dfs(1,mid,0);
    sort(f+1,f+1+tot);
    ll ans=0;
    for(int i=0;i<(1<<(n-mid));i++){
        ll sum=0;
        for(int j=mid+1,tmp=i;j<=n;j++,tmp>>=1)
            if(tmp&1)
                sum+=a[j];
        //ans+=mp[m-sum];
        int pos=upper_bound(f+1,f+1+tot,m-sum)-f;
        if(pos>tot||f[pos]>m-sum)pos--;
        ans+=pos;
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}