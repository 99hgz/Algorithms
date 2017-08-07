#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Node
{
    ll size, dep;
};
priority_queue<Node> Q;
ll n, k, a[100010], push_more_num, ans;

bool operator<(Node a, Node b)
{
    if (a.size != b.size)
        return a.size > b.size;
    else
        return a.dep > b.dep;
}

int main()
{
    scanf("%lld%lld", &n, &k);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        Q.push((Node){a[i], 1});
    }
    if ((n - 1) % (k - 1) != 0)
        push_more_num = k - 1 - (n - 1) % (k - 1);
    n += push_more_num;
    for (ll i = 1; i <= push_more_num; i++)
    {
        Q.push((Node){0, 1});
    }
    while (n != 1)
    {
        ll combinenum = 0, dep = 0;
        for (ll i = 1; i <= k; i++)
        {
            Node tmp = Q.top();
            //printf("pop:%d %d\n", tmp.size, tmp.dep);
            Q.pop();
            combinenum += tmp.size;
            dep = max(dep, tmp.dep);
        }
        ans += combinenum;
        Node tmp1;
        tmp1.size = combinenum;
        tmp1.dep = dep + 1;
        //printf("push:%d %d\n", tmp1.size, tmp1.dep);
        Q.push(tmp1);
        n -= k - 1;
    }
    Node tmp2 = Q.top();
    printf("%lld\n%ll'd\n", ans, tmp2.dep - 1);
    system("pause");
    return 0;
}