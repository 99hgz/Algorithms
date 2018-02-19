#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int last, root, cnt, fa[200010], len[200010], a[200010][26], n, k, stlen;
vector<int> vec[200010];
vector<int> _st[100010];
char st[100010];
set<int> size[200010];

void init()
{
    last = root = ++cnt;
}

void extend(int ch, int appear)
{
    int p = last, np = last = ++cnt;
    size[np].insert(appear);
    len[np] = len[p] + 1;
    while (p && !a[p][ch])
        a[p][ch] = np, p = fa[p];
    if (!p)
        fa[np] = root;
    else
    {
        int q = a[p][ch];
        if (len[q] == len[p] + 1)
            fa[np] = q;
        else
        {
            int nq = ++cnt;
            len[nq] = len[p] + 1;
            memcpy(a[nq], a[q], sizeof a[q]);
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while (p && a[p][ch] == q)
                a[p][ch] = nq, p = fa[p];
        }
    }
}

void dfs(int x)
{
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i];
        dfs(v);
        /*if (size[v].size() > size[x].size())
            swap(size[x], size[v]);*/
        for (set<int>::iterator it = size[v].begin(); it != size[v].end(); it++)
            size[x].insert(*it);
    }
}

int main()
{
    scanf("%d%d", &n, &k);
    init();
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", st + 1);
        last = root;
        stlen = strlen(st + 1);
        for (int j = 1; j <= stlen; j++)
        {
            _st[i].push_back(st[j] - 'a');
            extend(st[j] - 'a', i);
        }
    }
    for (int i = 1; i <= cnt; i++)
        if (fa[i])
            vec[fa[i]].push_back(i);
    if (k > n)
    {
        for (int i = 1; i <= n; i++)
        {
            printf("0 ");
        }
        return 0;
    }
    dfs(root);
    for (int i = 1; i <= n; i++)
    {
        int cur = root;
        ll ans = 0;
        stlen = _st[i].size();
        for (int j = 0; j < stlen; j++)
        {
            cur = a[cur][_st[i][j]];
            int k = len[cur];
            while (size[cur].size() == 1)
                cur = fa[cur];
            printf("cur=%d\n", size[cur].size());
            ans += k - len[cur];
        }
        printf("%lld ", ans);
    }
    system("pause");
    return 0;
}