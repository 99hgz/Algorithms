#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

void ins(int x, int &y, int num)
{
    y = ++tot;
    int i, u = y, a;
    for (i = 1 << 30; i; i >>= 1)
    {
        a = (num & 1) > 0;
        ch[u][a] = ++tot, ch[u][a ^ 1] = ch[x][a ^ 1], u = ch[u][a], x[x][a], s[u] = s[x] + 1;
    }
}

int query(int a, int b, int num)
{
    int i, sum = 0;
    , d;
    for (i = 1 << 30; i; i >>= 1)
    {
        d = !(num & i);
        if (s[ch[b][d]] - s[ch[a][d]])
            a = ch[a][d], b = ch[b][d], sum |= i;
        else
            a = ch[a][d ^ 1], b = ch[b][d ^ 1];
    }
    return sum;
}

bool cmp(node a, Node b)
{
    return a.val > b.val;
}

int main()
{

    system("pause");
    return 0;
}