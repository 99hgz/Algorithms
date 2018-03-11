#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int last, root, cnt, size[900020], len[900020], a[900020][26], fa[900020], tree[1000020 * 2], b[900020 * 2], k[900020 * 2], c[500020], pos[900020], sznum;
char st[500020];
void init()
{
    last = root = ++cnt;
}

void extend(int ch)
{
    int p = last, np = last = ++cnt;
    size[np] = 1;
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

bool pd(int x, int y, int pos)
{
    return b[x] + k[x] * pos < b[y] + k[y] * pos;
}

int calc(int x, int pos)
{
    return b[x] + k[x] * pos;
}

void insert(int rt, int l, int r, int L, int R, int id)
{
    if (L > R)
        return;
    //printf("%d %d %d %d %d %d\n", rt, l, r, L, R, id);
    if (L <= l && r <= R)
    {
        if (l == r)
        {
            if (pd(id, tree[rt], l))
                tree[rt] = id;
            return;
        }
        int mid = (l + r) >> 1;
        if (k[id] > k[tree[rt]])
        {
            if (pd(id, tree[rt], mid))
                insert(rt * 2 + 1, mid + 1, r, L, R, tree[rt]), tree[rt] = id;
            else
                insert(rt * 2, l, mid, L, R, id);
        }
        else
        {
            if (pd(id, tree[rt], mid))
                insert(rt * 2, l, mid, L, R, tree[rt]), tree[rt] = id;
            else
                insert(rt * 2 + 1, mid + 1, r, L, R, id);
        }
        return;
    }
    if (l > R || r < L)
        return;
    int mid = (l + r) >> 1;
    insert(rt * 2, l, mid, L, R, id), insert(rt * 2 + 1, mid + 1, r, L, R, id);
}

int query(int rt, int l, int r, int pos)
{
    if (l == r)
        return calc(tree[rt], pos);
    int res = calc(tree[rt], pos);
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return min(res, query(rt * 2, l, mid, pos));
    else
        return min(res, query(rt * 2 + 1, mid + 1, r, pos));
}

int main()
{
    init();
    scanf("%s", st + 1);
    int stlen = strlen(st + 1);
    for (int i = 1; i <= stlen; i++)
        extend(st[i] - 'a');
    for (int i = 1; i <= cnt; i++)
        c[len[i]]++;
    for (int i = 1; i <= stlen; i++)
        c[i] += c[i - 1];
    for (int i = 1; i <= cnt; i++)
        pos[c[len[i]]--] = i;
    b[0] = 0x3f3f3f3f;
    sznum = 0;
    for (int i = cnt; i >= 1; i--)
    {
        int cur = pos[i], minlen = len[fa[cur]] + 1;
        size[fa[cur]] += size[cur];
        if (size[cur] == 1)
        {
            b[++sznum] = minlen;
            insert(1, 1, stlen, len[cur] - minlen + 1, len[cur], sznum);
            k[++sznum] = -1;
            b[sznum] = len[cur] + 1;
            //printf("%d %d\n", len[fa[cur]] + 1, len[cur]);
            //printf("added:%d %d %d %d\n", len[cur] - minlen + 1, len[cur], 0, b[sznum - 1]);
            //printf("added:%d %d %d %d\n", 1, len[cur] - minlen, k[sznum], b[sznum]);
            insert(1, 1, stlen, 1, len[cur] - minlen, sznum);
        }
    }
    for (int i = 1; i <= stlen; i++)
        printf("%d\n", query(1, 1, stlen, i));
    system("pause");
    return 0;
}