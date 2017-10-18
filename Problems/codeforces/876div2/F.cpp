#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long long ll1;
int n, a[200010], l[200010], r[200010];
ll ans;
class RMQ
{
  public:
    void rmq()
    {
        int temp = (int)(log((double)n) / log(2.0));
        for (int i = 1; i <= n; i++)
            DP[i][0] = i;
        for (int j = 1; j <= temp; j++)
            for (int i = 1; i <= n; i++)
                if (i + (1 << (j - 1)) <= n)
                    DP[i][j] = (a[DP[i][j - 1]] > a[DP[i + (1 << (j - 1))][j - 1]]) ? DP[i][j - 1] : DP[i + (1 << (j - 1))][j - 1];
    }
    int Maximun(int L, int H)
    {
        int k = (int)(log((double)H - L + 1) / log(2.0));
        return (a[DP[L][k]] > a[DP[H - (1 << k) + 1][k]]) ? DP[L][k] : DP[H - (1 << k) + 1][k];
    }

  private:
    int DP[200010][20];
};
RMQ R;

/*void check(int l, int r, int mid)
{
    if (a[mid] != a[R.Maximun(l, r)])
    {
        printf("error1\n");
    }
    int res = 0;
    for (int i = l; i <= r; i++)
    {
        res |= a[i];
    }
    if (res <= a[mid])
    {
        printf("error2\n");
    }
    else
    {
        printf("%d %d\n", l, r);
    }
}*/

bool check(int l, int r)
{
    int mid = R.Maximun(l, r);
    int res = 0;
    for (int i = l; i <= r; i++)
    {
        res |= a[i];
    }
    if (res > a[mid])
    {
        return true;
    }
    return false;
}

void erfen(int ll, int rr)
{
    if (ll >= rr)
        return;
    int mid = R.Maximun(ll, rr);
    int rangel = max(l[mid], ll - 1), ranger = min(rr + 1, r[mid]);
    //printf("ef:%d %d %d\n", ll, rr, mid);
    ans += (ll1)(rangel - ll + 1) * (ll1)(rr - mid + 1) + (ll1)(rr - ranger + 1) * (ll1)(mid - ll + 1) - (ll1)(rangel - ll + 1) * (ll1)(rr - ranger + 1);
    erfen(ll, mid - 1);
    erfen(mid + 1, rr);
}

int main()
{
    //freopen("F.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    R.rmq();
    int cd = 30, prepos;
    for (int i = 0; i <= cd; i++)
    {
        prepos = 0;
        for (int j = 1; j <= n; j++)
        {

            if (!(a[j] & (1 << i)))
            {
                l[j] = max(l[j], prepos);
            }
            else
            {
                prepos = j;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        r[i] = n + 1;
    }
    for (int i = 0; i <= cd; i++)
    {
        prepos = n + 1;
        for (int j = n; j >= 1; j--)
        {

            if ((a[j] & (1 << i)))
            {
                prepos = j;
            }
            else
            {
                r[j] = min(r[j], prepos);
            }
        }
    }
    /*for (int i = 1; i <= n; i++)
    {
        printf("%d %d\n", l[i], r[i]);
    }*/
    erfen(1, n);
    /*for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (check(i, j))
            {
                printf("%d %d\n", i, j);
            }
        }
    }*/
    printf("%lld\n", ans);
    //system("pause");
    return 0;
}