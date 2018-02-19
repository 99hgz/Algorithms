#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Node
{
    int pos, val;
};

int a, b, n, f[1010][1010], ans;

struct PQ
{
    PQ() : head(0), tail(0) {}
    int head, tail;
    Node q[1010];
    void insert(int op, int num, int val)
    {
        while (head < tail && num - q[head].pos >= n)
            head++;
        if (op == 1)
            while (head < tail && q[tail - 1].val <= val)
                tail--;
        else
            while (head < tail && q[tail - 1].val >= val)
                tail--;
        q[tail++] = (Node){num, val};
    }
    int val()
    {
        return q[head].val;
    }
} pq[1010], pq2[1010], row[1010], row2[1010];

int main()
{
    scanf("%d%d%d", &a, &b, &n);
    for (int i = 1; i <= a; i++)
        for (int j = 1; j <= b; j++)
        {
            scanf("%d", &f[i][j]);
        }
    ans = 0x3f3f3f3f;
    for (int i = 1; i <= a; i++)
        for (int j = 1; j <= b; j++)
        {
            pq[j].insert(1, i, f[i][j]);
            pq2[j].insert(2, i, f[i][j]);
            row[i].insert(1, j, pq[j].val());
            row2[i].insert(2, j, pq2[j].val());
            //printf("%d %d val=%d\n", i, j, row[i].val() - row2[i].val());
            if (i >= n && j >= n)
                ans = min(ans, row[i].val() - row2[i].val());
        }
    printf("%d\n", ans);
    system("pause");
    return 0;
}