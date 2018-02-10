#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <set>
#define ll long long
using namespace std;
const int N = 800100, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m, r, K;
ll X[N], Y[N];
map<ll, bool> M;
multiset<pair<ll, int>> S;
struct node
{
    int x, y;
} Q[N];
int main()
{
    scanf("%d%d%d%d", &n, &m, &r, &K);
    for (int i = 1; i <= min((n + 1) >> 1, r); i++)
        X[i] = i;
    for (int i = n; i >= n - min((n + 1) >> 1, r) + 1; i--)
        X[i] = n - i + 1;
    int last = 1;
    for (int i = 1; i <= n; i++)
        if (X[i] == 0)
            X[i] = last;
        else
            last = X[i];
    for (int i = 1; i <= min((m + 1) >> 1, r); i++)
        Y[i] = i;
    for (int i = m; i >= m - min((m + 1) >> 1, r) + 1; i--)
        Y[i] = m - i + 1;
    for (int i = 1; i <= m; i++)
        if (Y[i] == 0)
            Y[i] = last;
        else
            last = Y[i];
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", X[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", Y[i]);
    }
    int x = (n + 1) >> 1, y = (m + 1) >> 1, t = 0;
    Q[1] = (node){x, y};
    M[(ll)x * (m + 1) + y] = 1;
    S.insert(make_pair(X[x] * Y[y], 1));
    ll ans = 0;
    while (K--)
    {
        multiset<pair<ll, int>>::iterator it = S.end();
        it--;
        ans += X[Q[(*it).second].x] * Y[Q[(*it).second].y];
        x = Q[(*it).second].x, y = Q[(*it).second].y;
        S.erase(it);
        cout << x << ' ' << y << ' ' << X[x] * Y[y] << endl;
        for (int i = 0; i < 4; i++)
        {
            int x1 = x + dx[i], y1 = y + dy[i];
            if (!M[(ll)x1 * (max(n, m) + 1) + y1])
            {
                M[(ll)x1 * (m + 1) + y1] = 1;
                S.insert(make_pair(X[x1] * Y[y1], ++t));
                Q[t] = (node){x1, y1};
            }
        }
    }
    cout << ans << endl;
    printf("%.10lf", (double)ans / ((double)(n - r + 1) * (m - r + 1)));
    system("pause");
    return 0;
}
