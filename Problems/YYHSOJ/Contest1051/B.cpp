#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, m, a, b;
char ch;
int p[1000];

int Findset(int x)
{
    if (x == p[x])
        return x;
    int tmp = Findset(p[x]);
    value[x] += value[p[x]];
    if (value[x] >= 3)
        value[x] -= 3;
    return p[x] = tmp;
}

void merge(int x, int y, int val)
{
    int fx = Findset(x), fy = Findset(y);
    p[fx] = fy;
    value[fx] = (value[y] + del - value[x] + 3) % 3;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%c%d", &cases[i].a, &ch, &cases[i].b);
        if (ch == '=')
            cases[i].value = 0;
        else if (ch == '>')
            cases[i].value = 1;
        else
            cases[i].value = 2;
    }
    memset(errors,0,sizeof(errors));
}
system("pause");
return 0;
}