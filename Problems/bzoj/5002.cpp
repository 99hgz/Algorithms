#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;

int n, m, S, tot, Next[110000], head[1100], tree[110000], val[110000],
    dis[1100], a[1100], last[1100], flag[1100], x[500000], s, t, u, v, w, cxtime[1100][2], r[1100], rc[1100];
bool visit[1100];
bool reg = false, regg = false;
void getnextcolor(int x, int nowtime, int &thiscolor, int &changetime)
{
    if (nowtime < r[x])
    {
        thiscolor = rc[x];
        changetime = r[x];
        return;
    }
    int thisturnusedtime = (nowtime - r[x]) % (cxtime[u][0] + cxtime[u][1]);
    int resttime = nowtime - thisturnusedtime;
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

int calcwaittime(int u, int v, int nowtime, int firstdg)
{
    int thiscoloru, thiscolorv, changetimeu, changetimev;
    getnextcolor(u, nowtime, thiscoloru, changetimeu);
    getnextcolor(v, nowtime, thiscolorv, changetimev);
    if (thiscoloru == thiscolorv)
        return nowtime;
    if (changetimeu == changetimev)
    {
        if (firstdg == 0 || nowtime <= r[u] || nowtime <= r[v])
            return calcwaittime(u, v, changetimeu, 1);
        else
            return 1 << 30;
    }
    return min(changetimeu, changetimev);
}

void add(int x, int y, int z)
{
    tot++;
    Next[tot] = head[x];
    head[x] = tot;
    tree[tot] = y;
    val[tot] = z;
}
int spfa(int s)
{
    for (int i = 1; i <= n; i++)
        dis[i] = 1 << 30, visit[i] = false, flag[i] = 0;
    int t = 0, w = 1;
    x[1] = s;
    dis[s] = 0;
    visit[s] = true;
    flag[s] = 1;
    while (t < w)
    {
        t++;
        int u = x[t];
        visit[u] = false;
        for (int i = head[u]; i; i = Next[i])
        {
            int v = tree[i];
            int tmp = calcwaittime(u, v, dis[u], 0);

            if (tmp + val[i] < dis[v])
            {
                last[v] = u;
                dis[v] = tmp + val[i];
                if (!visit[v])
                {
                    x[++w] = v, visit[v] = true;
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d", &s, &t);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        char A[10];
        scanf("%s%d%d%d", A, &r[i], &cxtime[i][0], &cxtime[i][1]);
        rc[i] = A[0] == 'B' ? 0 : 1;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
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

        int SS[1010];
        int len = 0;
        int it = last[t];
        SS[++len] = t;
        while (it != 0)
        {
            SS[++len] = it;
            it = last[it];
        }
        printf("%d\n", dis[t]);
        //SS.push(s);
        for (; len >= 1; len--)
        {
            int tmp = SS[len];
            if (tmp == t)
                break;
            printf("%d ", tmp);
        }
        printf("%d\n", t);

        //while()
    }
    system("pause");
    return 0;
}