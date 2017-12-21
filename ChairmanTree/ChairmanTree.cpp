
void modify(ll &rt, ll l, ll r, ll x, ll base)
{
    ll thisrt = ++tot;
    Tree[thisrt] = Tree[rt];
    rt = thisrt;
    ll mid = (l + r) >> 1;
    Tree[thisrt].num += base, Tree[thisrt].sum += x * base;
    if (l == r)
        return;
    if (x <= mid)
        modify(Tree[thisrt].lson, l, mid, x, base);
    else
        modify(Tree[thisrt].rson, mid + 1, r, x, base);
}

ll query(ll rt, ll l, ll r, ll x, ll sum)
{
    if (l == r)
        return sum + x * l;
    ll mid = (l + r) >> 1;
    if (Tree[Tree[rt].lson].num >= x)
        return query(Tree[rt].lson, l, mid, x, sum);
    else
        return query(Tree[rt].rson, mid + 1, r, x - Tree[Tree[rt].lson].num, sum + Tree[Tree[rt].lson].sum);
}