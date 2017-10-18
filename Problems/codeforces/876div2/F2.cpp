#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll ans;
int n, f[200005][20], a[200005][31];
int x[200005], pre[200005][31], Next[200005][31];
void zh(int i, int x)
{
    int len = 0;
    while (x)
    {
        a[i][++len] = x & 1;
        x >>= 1;
    }
    while (len < 30)
        a[i][++len] = 0;
}
int MAX(int L, int R)
{
    int k = (double)log(R - L + 1) / (double)log(2);
    if (x[f[L][k]] > x[f[R - (1 << k) + 1][k]])
        return f[L][k];
    else
        return f[R - (1 << k) + 1][k];
}
void solve(ll L, ll R)
{
    if (L > R)
        return;
    int m = MAX(L, R);
    ll l = L - 1, r = R + 1;
    for (int i = 1; i <= 30; i++)
        if (!(x[m] & (1 << (30 - i))))
            l = max(l, (ll)pre[m][31 - i]), r = min(r, (ll)Next[m][31 - i]);
    ans += (l - L + 1) * (R - m + 1) + (R - r + 1) * (m - L + 1) - (l - L + 1) * (R - r + 1);
    cout << L << ' ' << R << ' ' << m << ' ' << l << ' ' << r << ' ' << ans << endl;
    //4 68 54 85 65
    solve(L, m - 1);
    solve(m + 1, R);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x[i]);
        f[i][0] = i;
        zh(i, x[i]);
    }
    int last[35];
    memset(last, 0, sizeof(last));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 30; j++)
        {
            pre[i][j] = last[j];
            if (a[i][j] == 1)
                last[j] = i;
        }
    for (int i = 1; i <= 30; i++)
        last[i] = n + 1;
    for (int i = n; i; i--)
        for (int j = 1; j <= 30; j++)
        {
            Next[i][j] = last[j];
            if (a[i][j] == 1)
                last[j] = i;
        }
    for (int j = 1; j <= 30; j++)
        for (int i = 1; i <= n; i++)
            if (i + (1 << j) - 1 > n)
                break;
            else
            {
                if (x[f[i][j - 1]] > x[f[i + (1 << (j - 1))][j - 1]])
                    f[i][j] = f[i][j - 1];
                else
                    f[i][j] = f[i + (1 << (j - 1))][j - 1];
            }
    ans = 0LL;
    solve(1, n);
    cout << ans << endl;
    system("pause");
    return 0;
}