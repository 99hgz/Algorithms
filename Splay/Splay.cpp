/*
 * @key word:splay,lazy,懒惰标记
 * @未测试
 * @Author: http://hzwer.com/2841.html
 * @Date: 2017-04-24 20:27:23 
 * @Last Modified by: hzwer
 * @Last Modified time: 2017-04-24 20:31:40
 */
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define inf 1000000000
#define N 1000005
using namespace std;
int read()
{
    int x = 0, f = 1;
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
int n, m, rt, cnt;
int a[N], id[N], fa[N], c[N][2];
int sum[N], size[N], v[N], mx[N], lx[N], rx[N];
bool tag[N], rev[N];
queue<int> q;
void update(int x)
{
    int l = c[x][0], r = c[x][1];
    sum[x] = sum[l] + sum[r] + v[x];
    size[x] = size[l] + size[r] + 1;
    mx[x] = max(mx[l], mx[r]);
    mx[x] = max(mx[x], rx[l] + v[x] + lx[r]);
    lx[x] = max(lx[l], sum[l] + v[x] + lx[r]);
    rx[x] = max(rx[r], sum[r] + v[x] + rx[l]);
}
void pushdown(int x)
{
    int l = c[x][0], r = c[x][1];
    if (tag[x])
    {
	rev[x] = tag[x] = 0;
	if (l)
	    tag[l] = 1, v[l] = v[x], sum[l] = v[x] * size[l];
	if (r)
	    tag[r] = 1, v[r] = v[x], sum[r] = v[x] * size[r];
	if (v[x] >= 0)
	{
	    if (l)
		lx[l] = rx[l] = mx[l] = sum[l];
	    if (r)
		lx[r] = rx[r] = mx[r] = sum[r];
	}
	else
	{
	    if (l)
		lx[l] = rx[l] = 0, mx[l] = v[x];
	    if (r)
		lx[r] = rx[r] = 0, mx[r] = v[x];
	}
    }
    if (rev[x])
    {
	rev[x] ^= 1;
	rev[l] ^= 1;
	rev[r] ^= 1;
	swap(lx[l], rx[l]);
	swap(lx[r], rx[r]);
	swap(c[l][0], c[l][1]);
	swap(c[r][0], c[r][1]);
    }
}
void rotate(int x, int &k)
{
    int y = fa[x], z = fa[y], l, r;
    l = (c[y][1] == x);
    r = l ^ 1;
    if (y == k)
	k = x;
    else
	c[z][c[z][1] == y] = x;
    fa[c[x][r]] = y;
    fa[y] = x;
    fa[x] = z;
    c[y][l] = c[x][r];
    c[x][r] = y;
    update(y);
    update(x);
}
void splay(int x, int &k)
{
    while (x != k)
    {
	int y = fa[x], z = fa[y];
	if (y != k)
	{
	    if (c[y][0] == x ^ c[z][0] == y)
		rotate(x, k);
	    else
		rotate(y, k);
	}
	rotate(x, k);
    }
}
int find(int x, int rk)
{
    pushdown(x);
    int l = c[x][0], r = c[x][1];
    if (size[l] + 1 == rk)
	return x;
    if (size[l] >= rk)
	return find(l, rk);
    return find(r, rk - size[l] - 1);
}
void rec(int x)
{
    if (!x)
	return;
    int l = c[x][0], r = c[x][1];
    rec(l);
    rec(r);
    q.push(x);
    fa[x] = c[x][0] = c[x][1] = 0;
    tag[x] = rev[x] = 0;
}
int split(int k, int tot)
{
    int x = find(rt, k), y = find(rt, k + tot + 1);
    splay(x, rt);
    splay(y, c[x][1]);
    return c[y][0];
}
void query(int k, int tot)
{
    int x = split(k, tot);
    printf("%d\n", sum[x]);
}
void modify(int k, int tot, int val)
{
    int x = split(k, tot), y = fa[x];
    v[x] = val;
    tag[x] = 1;
    sum[x] = size[x] * val;
    if (val >= 0)
	lx[x] = rx[x] = mx[x] = sum[x];
    else
	lx[x] = rx[x] = 0, mx[x] = val;
    update(y);
    update(fa[y]);
}
void rever(int k, int tot)
{
    int x = split(k, tot), y = fa[x];
    if (!tag[x])
    {
	rev[x] ^= 1;
	swap(c[x][0], c[x][1]);
	swap(lx[x], rx[x]);
	update(y);
	update(fa[y]);
    }
}
void erase(int k, int tot)
{
    int x = split(k, tot), y = fa[x];
    rec(x);
    c[y][0] = 0;
    update(y);
    update(fa[y]);
}
void build(int l, int r, int f)
{
    if (l > r)
	return;
    int mid = (l + r) >> 1, now = id[mid], last = id[f];
    if (l == r)
    {
	sum[now] = a[l];
	size[now] = 1;
	tag[now] = rev[now] = 0;
	if (a[l] >= 0)
	    lx[now] = rx[now] = mx[now] = a[l];
	else
	    lx[now] = rx[now] = 0, mx[now] = a[l];
    }
    else
	build(l, mid - 1, mid), build(mid + 1, r, mid);
    v[now] = a[mid];
    fa[now] = last;
    update(now);
    c[last][mid >= f] = now;
}
void insert(int k, int tot)
{
    for (int i = 1; i <= tot; i++)
	a[i] = read();
    for (int i = 1; i <= tot; i++)
	if (!q.empty())
	    id[i] = q.front(), q.pop();
	else
	    id[i] = ++cnt;
    build(1, tot, 0);
    int z = id[(1 + tot) >> 1];
    int x = find(rt, k + 1), y = find(rt, k + 2);
    splay(x, rt);
    splay(y, c[x][1]);
    fa[z] = y;
    c[y][0] = z;
    update(y);
    update(x);
}
int main()
{
    n = read();
    m = read();
    mx[0] = a[1] = a[n + 2] = -inf;
    for (int i = 1; i <= n; i++)
	a[i + 1] = read();
    for (int i = 1; i <= n + 2; i++)
	id[i] = i;
    build(1, n + 2, 0);
    rt = (n + 3) >> 1;
    cnt = n + 2;
    int k, tot, val;
    char ch[10];
    while (m--)
    {
	scanf("%s", ch);
	if (ch[0] != 'M' || ch[2] != 'X')
	    k = read(), tot = read();
	if (ch[0] == 'I')
	    insert(k, tot);
	if (ch[0] == 'D')
	    erase(k, tot);
	if (ch[0] == 'M')
	{
	    if (ch[2] == 'X')
		printf("%d\n", mx[rt]);
	    else
		val = read(), modify(k, tot, val);
	}
	if (ch[0] == 'R')
	    rever(k, tot);
	if (ch[0] == 'G')
	    query(k, tot);
    }
    return 0;
}