#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;

struct Node
{
    int l, mid, r, val;
    friend bool operator<(const Node &a, const Node &b)
    {
        return a.val > b.val;
    }
};

priority_queue<Node> Q;
int n, k, L, RR, a[300010], pre[300010];
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
                    DP[i][j] = (pre[DP[i][j - 1]] > pre[DP[i + (1 << (j - 1))][j - 1]]) ? DP[i][j - 1] : DP[i + (1 << (j - 1))][j - 1];
    }
    int Maximun(int L, int H)
    {
        int k = (int)(log((double)H - L + 1) / log(2.0));
        return (pre[DP[L][k]] > pre[DP[H - (1 << k) + 1][k]]) ? DP[L][k] : DP[H - (1 << k) + 1][k];
    }

  private:
    int DP[300010][20];
};

int ans;
int main()
{
    scanf("%d%d%d%d", &n, &k, &L, &RR);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        pre[i] += pre[i - 1] + a[i];
    }
    RMQ R;
    R.rmq();
    for (int i = 1; i <= n; i++)
    {
        if (i + L - 1 > n)
            break;
        int tmp = R.Maximun(i + L - 1, min(i + RR - 1, n));
        Q.push((Node){i, tmp, min(i + RR - 1, n), pre[tmp]});
    }
    for (int i = 1; i <= k; i++)
    {
        Node tmp = Q.top();
        ans += tmp.val;
        Q.pop();
        if (tmp.mid > tmp.l)
        {
            int kk = R.Maximun(tmp.l, tmp.mid - 1);
            Q.push((Node){tmp.l, kk, tmp.mid - 1, pre[kk]});
        }
        if (tmp.r > tmp.mid)
        {
            int kk = R.Maximun(tmp.mid + 1, tmp.r);
            Q.push((Node){tmp.mid + 1, kk, tmp.r, pre[kk]});
        }
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}