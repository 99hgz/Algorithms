/*
 * @key word:线段树，懒惰标记
 * @已测试:POJ - 3468
 * @Author: hgz 
 * @Date: 2017-04-24 19:26:27 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-24 19:26:51
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100005
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ll long long
ll sum[N * 4];
int visit[N * 4];
void pushUp(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void build(int l, int r, int rt)
{
    visit[rt] = 0;
    if (l == r)
    {
        scanf("%lld", &sum[rt]);
        return;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    pushUp(rt);
}
void pushDown(int rt, int d)
{
    if (visit[rt] != 0)
    {
        visit[rt << 1] += visit[rt];
        visit[rt << 1 | 1] += visit[rt];
        sum[rt << 1 | 1] += (ll)(d >> 1) * visit[rt]; //注意后边乘可能超整形，强制类型转换（ll），即AC
        sum[rt << 1] += (ll)(d - (d >> 1)) * visit[rt];
        visit[rt] = 0;
    }
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        visit[rt] += c;
        sum[rt] += (r - l + 1) * c;
        return;
    }
    pushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m)
        update(L, R, c, lson);
    if (R > m)
        update(L, R, c, rson);
    pushUp(rt);
}
ll query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        return sum[rt];
    }
    pushDown(rt, r - l + 1);
    int m = (l + r) >> 1;
    ll ret = 0;
    if (L <= m)
        ret += query(L, R, lson);
    if (R > m)
        ret += query(L, R, rson);
    return ret;
}
int main()
{
    int n, q, a, b, c;
    char s[3];
    scanf("%d%d", &n, &q);
    build(1, n, 1);
    while (q--)
    {
        scanf("%s", s);
        if (s[0] == 'C')
        {
            scanf("%d%d%d", &a, &b, &c);
            update(a, b, c, 1, n, 1);
        }
        else if (s[0] == 'Q')
        {
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(a, b, 1, n, 1));
        }
    }
    system("pause");
    return 0;
}
