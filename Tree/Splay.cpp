#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int opt, n, x;
int ch[100010][2], cnt[100010], size[100010], fa[100010], key[100010], Root, sz;

void clear(int x)
{
    ch[x][0] = ch[x][1] = cnt[x] = size[x] = fa[x] = key[x] = 0;
}

int get(int x)
{
    return ch[fa[x]][1] == x;
}

void update(int x)
{
    if (x)
    {
        size[x] = cnt[x];
        if (ch[x][0])
            size[x] += size[ch[x][0]];
        if (ch[x][1])
            size[x] += size[ch[x][1]];
    }
}

void rotate(int x)
{
    int old = fa[x], oldf = fa[old], which = get(x);
    ch[old][which] = ch[x][which ^ 1];
    fa[ch[old][which]] = old;
    fa[old] = x;
    ch[x][which ^ 1] = old;
    fa[x] = oldf;
    if (oldf)
        ch[oldf][ch[oldf][1] == old] = x;
    update(old), update(x);
}

void splay(int x)
{
    for (int father; (father = fa[x]); rotate(x))
        if (fa[father])
            rotate((get(x) == get(father) ? father : x));
    Root = x;
}

void insert(int x)
{
    if (Root == 0)
    {
        sz++, key[sz] = x, cnt[sz] = 1, size[sz] = 1, Root = sz;
        return;
    }
    int now = Root, father = 0;
    while (1)
    {
        if (key[now] == x)
        {
            cnt[now]++;
            update(now);
            update(father);
            splay(now);
            return;
        }
        father = now;
        now = ch[now][key[now] < x];
        //printf("now=%d\n", now);
        if (now == 0)
        {
            sz++;
            key[sz] = x;
            size[sz] = cnt[sz] = 1;
            fa[sz] = father;
            ch[father][key[father] < x] = sz;
            update(father);
            splay(sz);
            return;
        }
    }
}

int getrank(int x)
{
    int res = 0, now = Root;
    while (1)
    {
        if (x < key[now])
            now = ch[now][0];
        else
        {
            res += (ch[now][0] ? size[ch[now][0]] : 0);
            if (x == key[now])
            {
                splay(now);
                return res + 1;
            }
            res += cnt[now];
            now = ch[now][1];
        }
    }
}

int findkth(int x)
{
    int now = Root;
    while (1)
    {
        if (ch[now][0] && x <= size[ch[now][0]])
            now = ch[now][0];
        else
        {
            int tmp = (ch[now][0] ? size[ch[now][0]] : 0) + cnt[now];
            if (x <= tmp)
                return key[now];
            x -= tmp;
            now = ch[now][1];
        }
    }
}

int suc()
{
    int now = ch[Root][0];
    while (ch[now][1])
        now = ch[now][1];
    return now;
}

int pre()
{
    int now = ch[Root][1];
    while (ch[now][0])
        now = ch[now][0];
    return now;
}

void del(int x)
{
    int DOSPLAY = getrank(x);
    //printf("getrank\n");
    if (cnt[Root] > 1)
    {
        cnt[Root]--;
        return;
    }
    if (!ch[Root][0] && !ch[Root][1])
    {
        clear(Root), Root = 0;
        return;
    }
    if (!ch[Root][0])
    {
        int old = Root;
        Root = ch[old][1];
        fa[Root] = 0;
        clear(old);
        return;
    }
    else if (!ch[Root][1])
    {
        int old = Root;
        Root = ch[old][0];
        fa[Root] = 0;
        clear(old);
        return;
    }
    int leftbig = pre(), old = Root;
    splay(leftbig);
    fa[ch[old][1]] = Root;
    ch[Root][1] = ch[old][1];
    clear(old);
    update(Root);
    return;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            insert(x);
        else if (opt == 2)
            del(x);
        else if (opt == 3)
            printf("%d\n", getrank(x));
        else if (opt == 4)
            printf("%d\n", findkth(x));
        else if (opt == 5)
        {
            insert(x);
            printf("%d\n", key[suc()]);
            del(x);
        }
        else
        {
            insert(x);
            printf("%d\n", key[pre()]);
            del(x);
        }
    }
    system("pause");
    return 0;
}