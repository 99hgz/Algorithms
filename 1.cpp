//  Created by Sengxian on 3/30/16.
//  Copyright (c) 2016年 Sengxian. All rights reserved.
//  BZOJ 3110 树套树
#include <algorithm>
#include <iostream>
#include <cctype>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

inline int ReadInt()
{
    int ch = getchar(), n = 0;
    bool flag = false;
    while (!isdigit(ch))
        flag |= ch == '-', ch = getchar();
    while (isdigit(ch))
        n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return flag ? -n : n;
}

typedef long long ll;

int n, m, vn, a, b, v;
#define mid ((l + r) / 2)
struct SegNode *null;
struct SegNode
{
    SegNode *ls, *rs;
    ll sum, addv;
    SegNode() : ls(null), rs(null), sum(0), addv(0) {}
    inline void plus(int len, int x) { sum += len * x, addv += x; }
    inline void pushdown(int l, int r)
    {
        if (addv)
            ls->plus(mid - l, addv), rs->plus(r - mid, addv), addv = 0;
    }
    inline void pushup() { sum = ls->sum + rs->sum; }
    inline void maintain(int l, int r)
    {
        if (r - l == 1)
            sum = addv;
        else
            sum = ls->sum + rs->sum + addv * (r - l);
    }
};

void modify1D(SegNode *&o, int l, int r)
{
    if (l >= b || r <= a)
        return;
    if (o == null)
        o = new SegNode();
    if (l >= a && r <= b)
        o->addv++;
    else
        modify1D(o->ls, l, mid), modify1D(o->rs, mid, r);
    o->maintain(l, r);
}

ll query1D(SegNode *&o, int l, int r, ll add = 0)
{
    if (l >= b || r <= a)
        return 0;
    if (l >= a && r <= b)
        return o->sum + add * (r - l);
    return query1D(o->ls, l, mid, add + o->addv) + query1D(o->rs, mid, r, add + o->addv);
}

void build1D(SegNode *&o, int l, int r)
{
    o = new SegNode();
    if (r - l > 1)
        build1D(o->ls, l, mid), build1D(o->rs, mid, r);
}

struct SegNode2D *null2D;
struct SegNode2D
{
    SegNode2D *ls, *rs;
    SegNode *val;
    SegNode2D() : ls(null2D), rs(null2D), val(null) {}
} * root;

void modify2D(SegNode2D *&o, int l, int r)
{
    if (o == null2D)
        o = new SegNode2D();
    if (r - l > 1)
    {
        if (v < mid)
            modify2D(o->ls, l, mid);
        else
            modify2D(o->rs, mid, r);
    }
    modify1D(o->val, 0, n);
}

ll Query2D(SegNode2D *o, int l, int r, int k)
{
    if (r - l == 1)
        return l;
    ll s = query1D(o->rs->val, 0, n);
    if (k <= s)
        return Query2D(o->rs, mid, r, k);
    else
        return Query2D(o->ls, l, mid, k - s);
}

void init_null()
{
    null = new SegNode(), null->ls = null, null->rs = null, null->sum = null->addv = 0;
    null2D = new SegNode2D(), null2D->ls = null2D, null2D->rs = null2D, null2D->val = null;
    root = null2D;
}

const int maxm = 50000 + 3;
vector<int> cs;
int opers[maxm], as[maxm], bs[maxm], vs[maxm];

int compress()
{
    for (int i = 0; i < m; ++i)
    {
        opers[i] = ReadInt(), as[i] = ReadInt(), bs[i] = ReadInt(), vs[i] = ReadInt();
        if (opers[i] == 1)
            cs.push_back(vs[i]);
    }
    sort(cs.begin(), cs.end());
    cs.erase(unique(cs.begin(), cs.end()), cs.end());
    for (int i = 0; i < m; ++i)
        if (opers[i] == 1)
            vs[i] = lower_bound(cs.begin(), cs.end(), vs[i]) - cs.begin();
    return cs.size();
}

int main()
{
    freopen("d:/tmp/ex_data.in", "r", stdin);
    freopen("d:/tmp/ex_data.out", "w", stdout);

    init_null();
    n = ReadInt(), m = ReadInt();
    vn = compress();
    for (int i = 0; i < m; ++i)
    {
        int oper = opers[i];
        a = as[i] - 1, b = bs[i], v = vs[i];
        if (oper == 1)
        {
            modify2D(root, 0, vn);
        }
        else if (oper == 2)
        {
            printf("%d\n", cs[Query2D(root, 0, vn, v)]);
        }
        else
            assert(false);
    }
    return 0;
}
