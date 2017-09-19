#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int tree1[500020], tree2[10010], sta[500020], sta_xx[10010], n, presum,
    c[10010], start1[10010], end1[10010], belong[500020], ss, X, Y, dx, cases,
    m;
int xx_start[10010], xx_end[10010];
int x, y;
int lowbit(int x) { return x & (-x); }
void add(int x, int del)
{
    for (; x <= 500010; x += lowbit(x))
    {
        tree1[x] += del;
    }
}
void add_xx(int x, int del)
{
    for (; x <= n; x += lowbit(x))
    {
        tree2[x] += del;
    }
}
int sum(int x)
{
    int res = 0;
    for (; x; x -= lowbit(x))
    {
        res += tree1[x];
    }
    return res;
}
int sum_xx(int x)
{
    int res = 0;
    for (; x; x -= lowbit(x))
    {
        res += tree2[x];
    }
    return res;
}

bool cango(int x, int y)
{
    if (x > y)
        swap(x, y);
    //printf("cango:%d %d %d %d\n", x, y, sum(y), sum(x - 1));
    if ((sum(y) - sum(x - 1)) == (y - x + 1))
    {
        //printf("true\n");
        return true;
    }
    else
    {
        if ((sum(xx_end[belong[x]]) - sum(y - 1) + sum(x) -
             sum(xx_start[belong[x]] - 1)) == (c[belong[x]] - (y - x - 1)))
        {
            //printf("true\n");
            return true;
        }
    }
    //printf("false\n");
    return false;
}

bool canthroughzx(int x, int y)
{
    if (x == y)
        return true;
    if (sum_xx(y - 1) - sum_xx(x) == (y - x - 1))
    {
        return true;
    }
    return false;
}

bool canthroughfx(int x, int y)
{
    //printf("canthroughfx:%d %d\n", x, y);
    /*for (int i = 1; i <= n; i++)
    {
        printf("%d ", sta_xx[i]);
    }
    printf("\n");*/
    if (sum_xx(n) - sum_xx(y) + sum_xx(x - 1) == (n - (y - x + 1)))
    {
        return true;
    }
    return false;
}

void update_xx(int x)
{
    if (cango(start1[x], end1[x]))
    {
        if (sta_xx[x] == 0)
        {
            add_xx(x, 1);
        }
        sta_xx[x] = 1;
    }
    else
    {
        if (sta_xx[x] == 1)
        {
            add_xx(x, -1);
        }
        sta_xx[x] = 0;
    }
}

int main()
{
    //freopen("E:\\kepler\\kepler7.in", "r", stdin);
    //freopen("E:\kepler\kepler1.out", "w", stdout);

    scanf("%d", &n);
    presum = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
        for (int j = 1; j <= c[i]; j++)
        {
            scanf("%d", &ss);
            sta[presum + j] = ss;
            belong[presum + j] = i;
            /*if (ss == 0)
                printf("%d\n", j);*/
            add(presum + j, ss);
        }
        xx_start[i] = presum + 1;
        xx_end[i] = presum + c[i];
        scanf("%d%d", &x, &y);
        start1[i] = presum + x;
        end1[i] = presum + y;
        presum += c[i];
        update_xx(i);
    }
    scanf("%d", &m);
    /*for (int i = 1; i <= n; i++)
    {
        printf("%d :%d\n", i, sta_xx[i]);
    }*/
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &cases);
        if (cases == 1)
        {
            scanf("%d", &dx);
            if (sta[dx] == 1)
            {
                add(dx, -1);
                sta[dx] = 0;
            }
            else
            {
                add(dx, 1);
                sta[dx] = 1;
            }
            update_xx(belong[dx]);
        }
        else
        {
            scanf("%d%d", &X, &Y);

            if (X > Y)
                swap(X, Y);
            //printf("belong %d %d begin:%d\n", belong[X], belong[Y], start1[belong[X]]);
            if (belong[X] == belong[Y])
            {
                if (n == 1)
                {
                    if (cango(X, Y) || ((cango(X, end1[belong[X]]) && cango(start1[belong[Y]], Y))) || ((cango(X, start1[belong[X]]) && cango(end1[belong[Y]], Y))))
                    {
                        printf("Yes\n");
                    }
                    else
                    {
                        printf("No\n");
                    }
                }
                else
                {
                    if (cango(X, Y) || ((cango(X, end1[belong[X]]) && canthroughfx(belong[X], belong[Y]) &&
                                         cango(start1[belong[Y]], Y)) ||
                                        (cango(X, start1[belong[X]]) &&
                                         canthroughfx(belong[X], belong[Y]) && cango(end1[belong[Y]], Y))))
                    {
                        printf("Yes\n");
                    }
                    else
                    {
                        printf("No\n");
                    }
                }
            }
            else
            {

                if ((cango(X, end1[belong[X]]) && canthroughzx(belong[X], belong[Y]) &&
                     cango(start1[belong[Y]], Y)) ||
                    (cango(X, start1[belong[X]]) &&
                     canthroughfx(belong[X], belong[Y]) && cango(end1[belong[Y]], Y)))
                {
                    printf("Yes\n");
                }
                else
                {
                    printf("No\n");
                }
            }
        }
    }
    //system("pause");
}