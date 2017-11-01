#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;

ll n, m, S, tot, Next[110000], head[1100], tree[110000], val[110000],
    dis[1100], a[1100], last[1100], flag[1100], x[500010], s, t, u, v, w, cxtime[1100][2], r[1100], rc[1100];
bool visit[1100];
bool reg = false, regg = false;
void getnextcolor(ll x, ll nowtime, ll &thiscolor, ll &changetime)
{
    if (nowtime < r[x])
    {
        thiscolor = rc[x];
        changetime = r[x];
        return;
    }
    ll thisturnusedtime = (nowtime - r[x]) % (cxtime[u][0] + cxtime[u][1]);
    ll resttime = nowtime - thisturnusedtime;
    thiscolor = rc[x];
    if (thisturnusedtime < cxtime[x][thiscolor ^ 1])
    {
        thiscolor ^= 1;
        changetime = resttime + cxtime[x][thiscolor];
        return;
    }
    else
    {
        changetime = resttime + cxtime[x][thiscolor] + cxtime[x][thiscolor ^ 1];
        return;
    }
}

ll calcwaittime(ll u, ll v, ll nowtime, ll firstdg, ll deep)
{
    if (deep > 4)
        return 1 << 30;
    ll thiscoloru, thiscolorv, changetimeu, changetimev;
    getnextcolor(u, nowtime, thiscoloru, changetimeu);
    getnextcolor(v, nowtime, thiscolorv, changetimev);
    if (thiscoloru == thiscolorv)
        return nowtime;
    if (changetimeu == changetimev)
    {
        if (firstdg == 0 || nowtime <= r[u] || nowtime <= r[v])
            return calcwaittime(u, v, changetimeu, 1, deep + 1);
        else
            return 1 << 30;
    }
    return min(changetimeu, changetimev);
}

void add(ll x, ll y, ll z)
{
    tot++;
    Next[tot] = head[x];
    head[x] = tot;
    tree[tot] = y;
    val[tot] = z;
}
ll spfa(ll s)
{
    for (ll i = 1; i <= n; i++)
        dis[i] = 1 << 30, visit[i] = false, flag[i] = 0;
    ll t = 0, w = 1;
    x[1] = s;
    dis[s] = 0;
    visit[s] = true;
    flag[s] = 1;
    while (t < w)
    {
        t++;
        if (t == 500000)
            t = 1;
        ll u = x[t];
        visit[u] = false;
        for (ll i = head[u]; i; i = Next[i])
        {
            ll v = tree[i];
            ll tmp = calcwaittime(u, v, dis[u], 0, 0);
            if (tmp >= (1 << 30))
                continue;
            if (tmp < dis[u])
                continue;
            if (tmp + val[i] < dis[v])
            {
                last[v] = u;
                dis[v] = tmp + val[i];
                if (!visit[v])
                {
                    w++;
                    if (w == 500000)
                        w = 1;
                    x[w] = v, visit[v] = true;
                }
            }
        }
    }
}
//stack<ll> SS;
ll SS[1010], top;
int main()
{
    scanf("%lld%lld", &s, &t);
    if (s == t)
    {
        printf("0\n");
        return 0;
    }
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
    {
        char A[10];
        scanf("%s%lld%lld%lld", A, &r[i], &cxtime[i][0], &cxtime[i][1]);
        rc[i] = A[0] == 'B' ? 0 : 1;
    }
    for (ll i = 1; i <= m; i++)
    {
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    spfa(s);

    if (dis[t] == 1 << 30)
    {
        printf("0\n");
    }
    else
    {
        SS[++top] = t;
        //SS.push(t);
        ll it = last[t];
        while (it != 0)
        {
            SS[++top] = it;
            //SS.push(it);
            it = last[it];
        }
        printf("%lld\n", dis[t]);
        //SS.push(s);
        for (;; top--)
        {
            ll tmp = SS[top];
            if (tmp == t)
                break;
            printf("%lld ", tmp);
        }
        printf("%lld\n", t);

        //while()
    }

    return 0;
}