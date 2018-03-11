#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
typedef long long ll;
typedef double ld;
#define eps 1e-10
int n, l, m, _p, _q, pos[110], never;
char st[110][110];
double p[110];
double f[110][110];

namespace ac
{
int root, cnt, ch[110][12], post[110];
bool danger[110];
void init()
{
    root = cnt = 0;
}
int insert(int id)
{
    int cur = root;
    int len = strlen(st[id] + 1);
    for (int i = 1; i <= len; i++)
    {
        if (!ch[cur][st[id][i] - 'A'])
            ch[cur][st[id][i] - 'A'] = ++cnt;
        cur = ch[cur][st[id][i] - 'A'];
    }
    danger[cur] = true;
    return cur;
}
void build()
{
    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < m; i++)
        {
            int v = ch[cur][i];
            if (v)
            {
                q.push(v);
                if (cur != 0)
                    post[v] = ch[post[cur]][i];
                danger[v] |= danger[post[v]];
            }
            else
                ch[cur][i] = ch[post[cur]][i];
        }
    }
}
void equ()
{
    cnt++;
    f[1][cnt + 1] = -1.0;
    for (int i = 1; i <= cnt; i++)
    {
        f[i][i] = -1.0;
        if (danger[i - 1])
            continue;
        for (int j = 0; j < m; j++)
            f[ch[i - 1][j] + 1][i] += p[j];
    }
}
}

void solve(int n)
{
    for (int i = 1; i <= n; i++)
    {
        int t = i;
        for (int j = i; j <= n; j++)
            if (fabs(f[j][i]) > eps)
                t = j;
        for (int j = 1; j <= n + 1; j++)
            swap(f[i][j], f[t][j]);
        for (int j = 1; j <= n; j++)
            if (j != i && fabs(f[j][i]) > eps)
            {
                ld bs = f[j][i] / f[i][i];
                for (int k = 1; k <= n + 1; k++)
                    f[j][k] -= f[i][k] * bs;
            }
    }
    for (int i = 1; i <= n; i++)
        f[i][i] = f[i][n + 1] / f[i][i];
}

int main()
{
    ac::init();
    scanf("%d%d%d", &n, &l, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &_p, &_q);
        p[i] = (double)_p / _q;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", st[i] + 1);
        for (int j = 1; j <= l; j++)
            if (fabs(p[st[i][j] - 'A']) < eps)
            {
                never++;
                break;
            }
        pos[i] = ac::insert(i) + 1;
        printf("pos=%d\n", pos[i]);
    }
    if (never == n)
    {
        for (int i = 1; i <= n; i++)
            printf("0.00\n");
        return 0;
    }
    ac::build();
    ac::equ();
    solve(ac::cnt);
    for (int i = 1; i <= n; i++)
        printf("%.2lf\n", f[pos[i]][pos[i]] + eps);
    system("pause");
    return 0;
}