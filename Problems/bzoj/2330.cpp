#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

bool visit[110000];
ll dis[110000];
int n, m, mina, ans, X, a, b, Next[410000], head[110000], tree[410000], val[410000], tot, flag[410000], x[220000];
bool reg;
void add(int x, int y, int z)
{
    //printf("%d%d%d\n", x, y, z);
    tot++;
    Next[tot] = head[x];
    head[x] = tot;
    tree[tot] = y;
    val[tot] = z;
}

int spfa(int s)
{
    int t = 0, w = 1;
    x[1] = s;
    dis[s] = 0;
    visit[s] = true;
    flag[s] = 1;

    while (t != w)
    {
        t++;
        if (t == 210000)
            t = 0;
        int u = x[t];
        visit[u] = false;

        for (int i = head[u]; i; i = Next[i])
        {
            int v = tree[i];
            if (dis[u] + val[i] > dis[v])
            {
                dis[v] = dis[u] + val[i];
                if (!visit[v])
                {
                    w++;
                    if (w == 210000)
                        w = 0;
                    x[w] = v, visit[v] = true;

                    flag[v]++;
                    if (flag[v] >= n)
                    {
                        reg = true;
                        return 0;
                    }
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &X, &a, &b);
        //printf("%d\n", X);
        switch (X)
        {
        case 1:
            add(a, b, 0);
            add(b, a, 0);
            break;
        case 2:
            if (a == b)
            {
                printf("-1");
                return 0;
            }
            add(a, b, 1);
            break;
        case 3:
            add(b, a, 0);
            break;
        case 4:
            if (a == b)
            {
                printf("-1");
                return 0;
            }
            add(b, a, 1);
            break;
        case 5:
            add(a, b, 0);
            break;
        }
    }
    for (int i = n; i >= 1; i--)
    {
        add(0, i, 1);
        //pathq.push_back((Node){0, i, 0});
    }
    spfa(0);
    if (reg)
    {
        printf("-1\n");
    }
    else
    {

        ll ans = 0;

        for (int i = 1; i <= n; i++)
        {
            //dis[i] -= mina;
            //printf("%d\n", dis[i]);
            ans += (ll)dis[i];
        }
        printf("%lld\n", ans);
    }
    system("pause");
    return 0;
}