#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll f[100], k, bit[100], n, ans, last[100], bin[100];

ll dfs(ll tjnum, ll pos, bool limit)
{
  // printf("%lld %lld %d\n", cd, pos, limit);
  if (pos == 1)
  {
    return (!limit) ? 1 : (bit[pos] >= tjnum);
  }
  if (!limit && f[pos] != -1)
    return f[pos];
  ll res = 0;
  ll maxx = (limit ? bit[pos] : 9);
  for (ll i = 0; i <= maxx; i++)
  {

    res += dfs(tjnum, pos - 1, limit && i == bit[pos]);
    /*if (pos == k)
      printf("%lld %lld %lld\n", tjnum, i, res);*/
    if (i == tjnum)
    {
      res += ((limit && i == bit[pos]) ? (last[pos - 1] + 1) : bin[pos - 1]);
    }
    /*if (pos == k)
      printf("%lld %lld %lld\n", tjnum, i, res);*/
    // res %= (ll)10000007;
  }
  if (!limit)
    f[pos] = res;
  return res;
}

int main()
{
  scanf("%lld", &n);
  ll nn = n;
  k = 0;
  bin[0] = 1;
  while (n)
  {
    bit[++k] = n % (ll)10;
    n /= (ll)10;
    bin[k] = bin[k - 1] * 10;
    last[k] = last[k - 1] + bin[k - 1] * bit[k];
    // printf("last[%lld]=%lld\n", k, last[k]);
  }
  ans = 1;

  for (ll i = 0; i <= 9; i++)
  {
    memset(f, -1, sizeof f);
    ll tmp = dfs(i, k, true);
    if (i == 0)
    {
      for (int i = 0; i <= k - 1; i++)
        tmp -= bin[i];
      tmp++;
    }
    printf("%lld\n", tmp);
  }
  // printf("%lld\n", ans);
  system("pause");
  return 0;
}