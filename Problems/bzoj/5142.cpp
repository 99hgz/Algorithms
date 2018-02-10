#include <cstdio>
#include <set>
#include <queue>
using namespace std;
typedef long long ll;
queue<int> q;
multiset<int, greater<int>> st;
int n, s[100010], f[100010];
ll m;
int main()
{
    scanf("%d%lld", &n, &m);
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &f[i], &s[i]);
    ll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += f[i];
        q.push(i);
        st.insert(s[i]);
        while (!q.empty() && sum - f[q.front()] >= m)
        {
            int tmp = q.front();
            st.erase(st.find(s[tmp]));
            q.pop();
            sum -= f[tmp];
        }
        if (!q.empty() && sum >= m)
            ans = min(ans, *st.begin());
    }
    printf("%d", ans);
    while (1)
    {
    }
}