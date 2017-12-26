#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

struct Node
{
    int id, l, r;
};
vector<Node> vec[100000];
bool cmp(Node a, Node b)
{
    return a.r < b.r;
}

int n, q, x[100010], l, r, cnt[100010], Hash[100010];
ll MAX, ans[100010];
ll dobl(int l, int r)
{
    ll m = MAX;
    for (int k = l; k <= r; k++)
        cnt[x[k]]++, m = max(m, (ll)cnt[x[k]] * Hash[x[k]]);
    for (int k = l; k <= r; k++)
        cnt[x[k]]--;
    return m;
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x[i]);
        Hash[i] = x[i];
    }

    sort(Hash + 1, Hash + 1 + n);
    int tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;

    for (int i = 1; i <= n; i++)
        x[i] = lower_bound(Hash + 1, Hash + 1 + tn, x[i]) - Hash;

    int block = sqrt(n), blocknum = (n / block) + 1;
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d", &l, &r);
        vec[l / block].push_back((Node){i, l, r});
    }
    for (int i = 0; i <= blocknum; i++)
    {
        int R = (i + 1) * block - 1, r = R;
        memset(cnt, 0, sizeof cnt);
        MAX = 0;
        sort(vec[i].begin(), vec[i].end(), cmp);
        for (int j = 0; j < vec[i].size(); j++)
        {
            Node tmp = vec[i][j];
            if (tmp.r <= R)
                ans[tmp.id] = dobl(tmp.l, tmp.r);
            else
            {
                for (int k = r; k <= tmp.r; k++)
                    cnt[x[k]]++, MAX = max(MAX, (ll)cnt[x[k]] * Hash[x[k]]);
                ans[tmp.id] = dobl(tmp.l, R - 1);
                r = tmp.r + 1;
            }
        }
    }

    for (int i = 1; i <= q; i++)
        printf("%lld\n", ans[i]);

    system("pause");
    return 0;
}