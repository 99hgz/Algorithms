#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int sa[200010], a[200010], n, k, Hash[200010], b[200010], c[200010], upper[200010], cnt;

void add(int x, int d)
{
    for (; x <= n; x += x & (-x))
        sa[x] += d;
}
int query(int x)
{
    int ans = 0;
    for (; x; x -= x & (-x))
        ans += sa[x];
    return ans;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        Hash[i] = a[i];
    }
    sort(Hash + 1, Hash + 1 + n);
    int tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(Hash + 1, Hash + 1 + tn, a[i]) - Hash;
    for (int i = 1; i <= n; i++)
    {
        add(a[i], 1);
        upper[i] = i - query(a[i]);
    }
    for (int i = 1; i <= n; i++)
        if (upper[i] > k)
            b[i - k] = a[i];
        else
            c[++cnt] = a[i];

    sort(c + 1, c + 1 + cnt);
    cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!b[i])
            b[i] = c[++cnt];
        printf("%d\n", Hash[b[i]]);
    }
    system("pause");
    return 0;
}