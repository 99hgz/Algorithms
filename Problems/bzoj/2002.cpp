#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, block_size, a[200010], times[200010], next1[200010], tmp_block_num, block_num;

int main()
{
    scanf("%d", &n);
    block_size = (int)sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = n; i >= 1; i--)
    {
        int tmp = i + a[i], block_num = (i - 1) / block_size + 1, tmp_block_num = (tmp - 1) / block_size + 1;
        if (tmp > n)
        {
            times[i] = 1;
            next1[i] = -1;
        }
        else if (tmp_block_num != block_num)
        {
            times[i] = 1;
            next1[i] = tmp;
        }
        else
        {
            times[i] = times[tmp] + 1;
            next1[i] = next1[tmp];
        }
    }
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int ans, cases;
        scanf("%d", &cases);
        if (cases == 1)
        {
            int now;
            scanf("%d", &now);
            now++;
            ans = 0;
            while (now != -1)
            {
                ans += times[now];
                now = next1[now];
            }
            printf("%d\n", ans);
        }
        else
        {
            int j, k;
            scanf("%d%d", &j, &k);
            j++;
            a[j] = k;
            int block_num1 = (j - 1) / block_size + 1;
            for (int i = j; i >= (block_num1 - 1) * block_size + 1; i--)
            {
                //printf("update:%d\n", i);
                int tmp = i + a[i], block_num = (i - 1) / block_size + 1, tmp_block_num = (tmp - 1) / block_size + 1;
                if (tmp > n)
                {
                    times[i] = 1;
                    next1[i] = -1;
                }
                else if (tmp_block_num != block_num)
                {
                    times[i] = 1;
                    next1[i] = tmp;
                }
                else
                {
                    times[i] = times[tmp] + 1;
                    next1[i] = next1[tmp];
                }
            }
        }
    }
    system("pause");
    return 0;
}