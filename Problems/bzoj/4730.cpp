#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
#define M 2000010
#define N 100010
int cnt, lson[M], rson[M], tag[M], rt[N], tot[M], SG[N];
int n, m, Head[N], Next[N * 2], To[N * 2], _tot, x, y;

void addedge(int u, int v)
{
    _tot++;
    Next[_tot] = Head[u];
    Head[u] = _tot;
    To[_tot] = v;
}

void ins(int &rt, int num, int dep)
{
    rt = ++cnt;
    tot[rt] = 1;
    lson[rt] = rson[rt] = tag[rt] = 0;
    if (!~dep)
        return;
    if (num >> dep & 1)
        ins(rson[rt], num, dep - 1);
    else
        ins(lson[rt], num, dep - 1);
}

void push_down(int rt, int dep)
{
    if (!tag[rt])
        return;
    if (tag[rt] >> dep & 1)
        swap(lson[rt], rson[rt]);
    tag[lson[rt]] ^= tag[rt];
    tag[rson[rt]] ^= tag[rt];
    tag[rt] = 0;
}

void Merge(int &rt, int rt2, int dep)
{
    if (!rt || !rt2)
    {
        rt |= rt2;
        return;
    }
    push_down(rt, dep);
    push_down(rt2, dep);
    Merge(lson[rt], lson[rt2], dep - 1);
    Merge(rson[rt], rson[rt2], dep - 1);
    tot[rt] = tot[lson[rt]] + tot[rson[rt]] + (dep == -1);
}

void calc(int x, int fa)
{
    //printf("calc:%d %d\n", x, fa);
    int sum = 0;
    for (int i = Head[x]; i; i = Next[i])
    {
        int v = To[i];
        if (v != fa)
        {
            calc(v, x);
            sum ^= SG[v];
        }
    }
    ins(rt[x], sum, 15);
    for (int i = Head[x]; i; i = Next[i])
    {
        int v = To[i];
        if (v != fa)
        {
            tag[rt[v]] ^= sum ^ SG[v];
            Merge(rt[x], rt[v], 15);
        }
    }
    SG[x] = 0;
    for (int d = 15, cur = rt[x]; ~d; --d)
    {
        push_down(cur, d);
        if (tot[lson[cur]] == (1 << d))
            cur = rson[cur], SG[x] |= 1 << d;
        else
            cur = lson[cur];
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    //T = 1;
    while (T--)
    {
        memset(Head, 0, sizeof Head);
        memset(Next, 0, sizeof Next);
        memset(rt, 0, sizeof rt);
        cnt = _tot = 0;

        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &x, &y);
            addedge(x, y);
            addedge(y, x);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
            if (!rt[i])
                cnt = 0, calc(i, -1), ans ^= SG[i];
        printf("%s\n", ans ? "Alice" : "Bob");
    }
    system("pause");
    return 0;
}