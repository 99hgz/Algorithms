#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int x[5010 * 5010], pos[5010 * 5010], left[5010], right[5010], n, m, q, x0, x1;
ll a, b, c, d;
int cnt;
int main()
{
    scanf("%d%lld%lld%lld%lld", &x0, &a, &b, &c, &d);
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n * m; i++)
        x[i] = i;
    for (int i = 1; i <= n * m; i++)
        x1 = (x0 * (a * x0 + b) + c) % d, swap(x[i], x[x1 % i + 1]), x0 = x1;
    for (int i = 1; i <= q; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        swap(x[a], x[b]);
    }
    for (int i = 1; i <= n * m; i++)
        pos[x[i]] = i;
    for (int i = 1; i <= n; i++)
        left[i] = 1, right[i] = m;
    for (int i = 1; i <= n * m; i++)
    {
        int py = (pos[i] - 1) % m + 1, px = (pos[i] - py) / m + 1;
        //printf("%d %d %d\n", i, px, py);
        if (py < left[px] || py > right[px])
            continue;
        //printf("ans=%d\n", i);
        cnt++;
        printf("%d%c", i, cnt == n + m - 1 ? '\n' : ' ');
        for (int j = 1; j <= px - 1; j++)
            if (right[j] > py)
                right[j] = py;
        for (int j = px + 1; j <= n; j++)
            if (left[j] < py)
                left[j] = py;
    }
    system("pause");
    return 0;
}