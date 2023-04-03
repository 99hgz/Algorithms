#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

ll n, cases, x, y, id, a, b, cnt, cnt2, l, r;
char opt[10], ch[10];
ll st[400010], ed[400010], ans[400010];
struct QUERY
{
    ll id, t, a, b;
    double xl;
} qry[400010];
struct Node
{
    ll x, y;
} vec[400010];

bool cmp(Node a, Node b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool cmp2(Node a, Node b)
{
    if (a.x == b.x)
        return a.y > b.y;
    return a.x < b.x;
}

double xl(Node a, Node b)
{
    if (a.x == b.x)
        return (double)1e18;
    return (double)(b.y - a.y) / (double)(b.x - a.x);
}

double xl1(Node a, Node b)
{
    if (a.x == b.x)
        return (double)-1e18;
    return (double)(b.y - a.y) / (double)(b.x - a.x);
}

struct SS
{
    vector<Node> queue[2];
    int tail[2];
    SS() : tail{-1, -1} {}
    void insert(Node a)
    {
        int fx = 0;
        while (tail[fx] > 0 && xl(queue[fx][tail[fx] - 1], queue[fx][tail[fx]]) < xl(queue[fx][tail[fx]], a))
            queue[fx].pop_back(), tail[fx]--;
        queue[fx].push_back(a);
        tail[fx]++;

        fx = 1;
        while (tail[fx] > 0 && xl1(queue[fx][tail[fx] - 1], queue[fx][tail[fx]]) > xl1(queue[fx][tail[fx]], a))
            queue[fx].pop_back(), tail[fx]--;
        queue[fx].push_back(a);
        tail[fx]++;
    }
    void insert(int fx, Node a)
    {
        if (fx == 0)
        {
            while (tail[fx] > 0 && xl(queue[fx][tail[fx] - 1], queue[fx][tail[fx]]) < xl(queue[fx][tail[fx]], a))
                queue[fx].pop_back(), tail[fx]--;
            queue[fx].push_back(a);
            tail[fx]++;
        }
        else
        {
            while (tail[fx] > 0 && xl1(queue[fx][tail[fx] - 1], queue[fx][tail[fx]]) > xl1(queue[fx][tail[fx]], a))
                queue[fx].pop_back(), tail[fx]--;
            queue[fx].push_back(a);
            tail[fx]++;
        }
    }

    ll query(ll a, ll b)
    {
        if (b > 0)
        {
            if (tail[0] == -1)
                return -0x3f3f3f3f3f3f3f3f;
            /*printf("tail[0]=%d inqueue:\n", tail[0]);
            for (auto y : queue[0])
                printf("%lld %lld\n", y.x, y.y);
            printf("-------\n");*/
            int l = 1, r = tail[0], ans = 0;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (xl(queue[0][mid - 1], queue[0][mid]) > ((double)a / (double)-b))
                    l = mid + 1, ans = mid;
                else
                    r = mid - 1;
            }
            return a * queue[0][ans].x + b * queue[0][ans].y;
        }
        else if (b == 0)
        {
            if (tail[1] == -1)
                return -0x3f3f3f3f3f3f3f3f;
            return a * queue[1][tail[1]].x;
        }
        else
        {
            if (tail[1] == -1)
                return -0x3f3f3f3f3f3f3f3f;
            int l = 1, r = tail[1], ans = 0;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (xl1(queue[1][mid - 1], queue[1][mid]) < ((double)a / (double)-b))
                    l = mid + 1, ans = mid;
                else
                    r = mid - 1;
            }
            return a * queue[1][ans].x + b * queue[1][ans].y;
        }
    }
} Tree[200010 * 4];

void up(int rt)
{
    vector<Node>::iterator st1 = Tree[rt * 2].queue[0].begin(), ed1 = Tree[rt * 2].queue[0].end();
    vector<Node>::iterator st2 = Tree[rt * 2 + 1].queue[0].begin(), ed2 = Tree[rt * 2 + 1].queue[0].end();
    while (1)
    {
        if (st1 == ed1 && st2 == ed2)
            break;
        if (st1 == ed1)
            Tree[rt].insert(0, *st2), st2++;
        else if (st2 == ed2)
            Tree[rt].insert(0, *st1), st1++;
        else if (cmp(*st1, *st2))
            Tree[rt].insert(0, *st1), st1++;
        else
            Tree[rt].insert(0, *st2), st2++;
    }

    st1 = Tree[rt * 2].queue[1].begin(), ed1 = Tree[rt * 2].queue[1].end();
    st2 = Tree[rt * 2 + 1].queue[1].begin(), ed2 = Tree[rt * 2 + 1].queue[1].end();
    while (1)
    {
        if (st1 == ed1 && st2 == ed2)
            break;
        if (st1 == ed1)
            Tree[rt].insert(1, *st2), st2++;
        else if (st2 == ed2)
            Tree[rt].insert(1, *st1), st1++;
        else if (cmp2(*st1, *st2))
            Tree[rt].insert(1, *st1), st1++;
        else
            Tree[rt].insert(1, *st2), st2++;
    }
}

void insert(int rt, int l, int r, int pos, Node a)
{
    if (l == r)
    {
        Tree[rt].insert(a);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        insert(rt * 2, l, mid, pos, a);
    else
        insert(rt * 2 + 1, mid + 1, r, pos, a);
    if (pos == r)
        up(rt);
}

ll query(int rt, int l, int r, int L, int R, ll a, ll b)
{
    if (l > R || r < L)
        return -0x3f3f3f3f3f3f3f3f;
    if (L <= l && r <= R)
        return Tree[rt].query(a, b);
    int mid = (l + r) >> 1;
    return max(query(rt * 2, l, mid, L, R, a, b), query(rt * 2 + 1, mid + 1, r, L, R, a, b));
}

inline ll decode(ll x, ll lastans)
{
    return x ^ (lastans & 0x7fffffff);
}

int main()
{
    scanf("%lld%s", &n, ch);
    bool nd = (ch[0] != 'E');
    ll lastans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", opt);
        if (opt[0] == 'A')
        {
            scanf("%lld%lld", &x, &y);
            if (nd)
                x = decode(x, lastans), y = decode(y, lastans);
            insert(1, 1, n, ++cnt2, (Node){x, y});
        }
        else
        {
            scanf("%lld%lld%lld%lld", &x, &y, &l, &r);
            if (nd)
                x = decode(x, lastans), y = decode(y, lastans), l = decode(l, lastans), r = decode(r, lastans);
            lastans = query(1, 1, n, l, r, x, y);
            printf("%lld\n", lastans);
        }
    }
    system("pause");
}