#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;

int n, m;
int f[2][2];
map<int, int> use;
int now;
void jump(int bg, int ed)
{
    if (ed < bg)
        return;
    now = now ^ 1;
    f[now][0] = min(f[1 ^ now][1], f[1 ^ now][0]);
    f[now][1] = min(f[1 ^ now][1] + 1, f[1 ^ now][0] + 1);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int pos, num;
        scanf("%d%d", &pos, &num);
        use[pos] = num;
    }
    ll ANS = 0;

    for (int bit = 1; bit <= 31; bit++)
    {
        now = 0;
        f[now][0] = 0;
        f[now][1] = 0x3f3f3f3f;
        int head = 0;
        map<int, int>::iterator it = use.begin();
        for (int i = 1; i <= m; i++)
        {
            jump(head + 1, (it->first) - 1);
            head = it->first;
            now = now ^ 1;
            if (((it->second) >> (bit - 1)) & 1)
                f[now][1] = f[1 ^ now][0] + 1, f[now][0] = f[1 ^ now][1];
            else
                f[now][1] = f[1 ^ now][1] + 1, f[now][0] = f[1 ^ now][0];
            it++;
        }
        //printf("%d %d %d\n", bit, f[n][1], f[n][0]);
        ANS += (1LL << (bit - 1)) * (ll)min(f[now][1], f[now][0]);
    }
    printf("%lld\n", ANS);
    system("pause");
    return 0;
}