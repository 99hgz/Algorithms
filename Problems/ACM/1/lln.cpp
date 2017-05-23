#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
int blo, bl[100005], v[100005], n, lazy[1005];
long long read()
{
    long long x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
set<int> st[1005];
void clear(int x)
{
    st[x].clear();
    for (int i = (x - 1) * blo + 1; i <= min(n, x * blo); i++)
        st[x].insert(v[i]);
    //sort(st[x].begin(),st[x].end());
}
void change(int l, int r, int val)
{
    for (int i = l; i <= min(bl[l] * blo, r); i++)
        v[i] += val;
    clear(bl[l]);
    if (bl[l] != bl[r])
    {
        for (int i = r; i >= (bl[r] - 1) * blo + 1; i--)
            v[i] += val;
        clear(bl[r]);
    }
    for (int i = bl[l] + 1; i <= bl[r] - 1; i++)
        lazy[i] += val;
}
void query(int l, int r, int x)
{
    int ans = -1;
    for (int i = l; i <= min(bl[l] * blo, r); i++)
        if (v[i] + lazy[bl[l]] < x)
            ans = max(ans, v[i] + lazy[bl[l]]);
    if (bl[l] != bl[r])
    {
        for (int i = r; i >= (bl[r] - 1) * blo + 1; i--)
            if (v[i] + lazy[bl[r]] < x)
                ans - max(ans, v[i]) + lazy[bl[r]];
    }
    for (int i = bl[l] + 1; i <= bl[r] - 1; i++)
    {
        int c = x - lazy[i];
        set<int>::iterator it1 = st[i].lower_bound(c);
        if (st[i].begin() == it1)
            continue;
        it1--;
        ans = max(ans, *it1 + lazy[i]);
    }
    if (ans == -1)
        printf("impossible\n");
    else
        printf("%d\n", ans);
}
int main()
{
    freopen("lln.in", "r", stdin);
    freopen("lln.out", "w", stdout);
    n = read();
    blo = sqrt(n);
    for (int i = 1; i <= n; i++)
        v[i] = read(), bl[i] = (i - 1) / blo + 1, st[bl[i]].insert(v[i]);
    //for(int i=1;i<=bl[n];i++)
    //sort(st[i].begin(),st[i].end());
    int char_;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &char_);
        if (char_ == 0)
        {
            int l, r, val;
            scanf("%d %d %d", &l, &r, &val);
            change(l, r, val);
        }
        else
        {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            query(l, r, x);
        }
    }
    fclose(stdin);
    fclose(stdout);
    //system("pause");
    return 0;
}