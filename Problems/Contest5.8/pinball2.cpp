#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <climits>
const int MAXN = 5;
using namespace std;
typedef long long ll;
int f[MAXN], f2[MAXN], l[MAXN], r[MAXN], m[MAXN], cost[MAXN];
int ans;
const int N=10000;
struct seg{
	ll Min[N*4],a[N];
	void build(int u,int l,int r){
		if(l==r){
			Min[u]=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(u*2,l,mid);
		build(u*2+1,mid+1,r);
		Min[u]=min(Min[u*2],Min[u*2+1]);
	}
	ll find(int u,int l,int r,int x,int y){
		if(x<=l && y>=r)return Min[u];
		if(x>r || y<l)return INF;
		int mid=(l+r)>>1;
		return min(find(u*2,l,mid,x,y),find(u*2+1,mid+1,r,x,y));
	}
	void change(int u,int l,int r,int x,ll w){
		if(l==r){
			Min[u]=min(w,Min[u]);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)change(u*2,l,mid,x,w);
		else change(u*2+1,mid+1,r,x,w);
		Min[u]=min(Min[u*2],Min[u*2+1]);
	}
}tree1;
int main()
{
    int n, m2;
    scanf("%d%d", &n, &m2);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d%d", &l[i], &r[i], &m[i], &cost[i]);
        points.push_back(l[i]);     
        points.push_back(r[i]);  
    }
    sort(points.begin(),points.end());
    buildTree(1,points[points.size()],0);
    int i, j;
    for (i = 0; i < n; i++) {
        updateTree(a, b, 0);
    }
    for (i = 0; i < n; i++)
    {
        f[i] = -1;
        if (l[i] == 1)
        {
            f[i] = cost[i];
        }
        for (j = 0; j < i; j++)
        {
            if ((l[i] <= m[j]) && (m[j] <= r[i]) && (f[j] != -1))
            {
                if ((f[i] == -1))
                {
                    f[i] = f[j] + cost[i];
                }
                else
                {
                    f[i] = min(f[j] + cost[i], f[i]);
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        f2[i] = -1;
        if (r[i] == m2)
        {
            f2[i] = cost[i];
        }
        for (j = 0; j < i; j++)
        {
            if ((l[i] <= m[j]) && (m[j] <= r[i]) && (f2[j] != -1))
            {
                if ((f2[i] == -1))
                {
                    f2[i] = f2[j] + cost[i];
                }
                else
                {
                    f2[i] = min(f2[j] + cost[i], f2[i]);
                }
            }
        }
    }
    ans = INT_MAX;
    bool success = false;
    for (i = 0; i < n; i++)
    {
        if ((f[i] != -1) && (f2[i] != -1))
            ans = min(ans, f[i] + f2[i] - cost[i]), success = true;
    }
    if (success)
        printf("%d\n", ans);
    else
        printf("-1\n");
    system("pause");
    return 0;
}