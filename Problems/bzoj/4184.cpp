#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
vector<ll> vec[500010 * 4];

struct LB
{
    ll f[34];
    LB()
    {
        memset(f, 0, sizeof(f));
    }
    bool insert(ll val)
    {
        for (int i = 31; i >= 0; i--)
        {
            if ((val & (1LL << i)))
            {
                if ((!f[i]))
                {
                    f[i] = val;
                    break;
                }
                val ^= (f[i]);
            }
        }
        return val > 0;
    }
    ll max()
    {
        ll res = 0;
        for (int i = 31; i >= 0; i--)
        {
            if ((res ^ f[i]) > res)
            {
                res = (res ^ f[i]);
            }
        }
        return res;
    }
} t;

int n, val[500010];
map<int, int> fr;
void insert(int rt, int l, int r, int L, int R, ll val)
{
    if (L <= l && r <= R)
    {
        //printf("%d %d %d %d %d %lld\n", rt, l, r, L, R, val);
        vec[rt].push_back(val);
        return;
    }
    if (l > R || r < L)
        return;
    int mid = (l + r) >> 1;
    insert(rt * 2, l, mid, L, R, val);
    insert(rt * 2 + 1, mid + 1, r, L, R, val);
}

void dfs(int rt, int l, int r, LB k)
{
    for (int i = 0; i < vec[rt].size(); i++)
        k.insert(vec[rt][i]);
    if (l == r)
    {
        printf("%lld\n", k.max());
        return;
    }
    int mid = (l + r) >> 1;
    dfs(rt * 2, l, mid, k);
    dfs(rt * 2 + 1, mid + 1, r, k);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        if (val[i] > 0)
            fr[val[i]] = i;
        else
        {
            insert(1, 1, n, fr[-val[i]], i - 1, -val[i]);
            fr[-val[i]] = 0;
        }
    }
    map<int, int>::iterator it = fr.begin();
    while (it != fr.end())
    {
        if (it->second != 0)
            insert(1, 1, n, it->second, n, it->first);
        it++;
    }
    dfs(1, 1, n, t);
    system("pause");
}