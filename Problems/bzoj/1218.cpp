#include <cstdio>
#include <cstring>
#include <queue>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, R;

struct Node
{
    int x, y, w;
} point[10010];
bool cmp(Node a, Node b)
{
    return a.y < b.y;
};
queue<Node> Q;
int ans, MAX;

int main()
{
    scanf("%d%d", &n, &R);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &point[i].x, &point[i].y, &point[i].w);
    }
    sort(point + 1, point + 1 + n, cmp);
    int MAX = 0;
    for (int i = 0; i <= 5000; i++)
    {
        while (!Q.empty())
        {
            Q.pop();
        }
        int ans = 0;
        for (int head = 1; head <= n; head++)
        {
            int r = point[head].y;
            int l = r - R;
            if (point[head].x >= i && point[head].x < (i + R))
            {
                ans += point[head].w;
                Q.push(point[head]);
            }
            while (!Q.empty() && Q.front().y <= l)
            {
                ans -= Q.front().w;
                Q.pop();
            }
            if (ans > MAX)
                MAX = ans;
        }
    }
    printf("%d\n", MAX);
    system("pause");
    return 0;
}