
void modify(int &rt, int l, int r, int x, int base)
{
    int thisrt = ++tot;
    Tree[thisrt] = Tree[rt];
    rt = thisrt;
    int mid = (l + r) >> 1;
    Tree[thisrt].num += base;
    if (l == r)
        return;
    if (x <= mid)
        modify(Tree[thisrt].lson, l, mid, x, base);
    else
        modify(Tree[thisrt].rson, mid + 1, r, x, base);
}

int query(int rt, int l, int r, int x)
{
    if (l == r)
        return Tree[rt].num;
    int mid = (l + r) >> 1;
    if (x <= mid)
        return query(Tree[rt].lson, l, mid, x);
    else
        return query(Tree[rt].rson, mid + 1, r, x);
}

int query(int rt, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
        return Tree[rt].num;
    if (r < L || l > R)
        return 0;
    int mid = (l + r) >> 1;
    return query(Tree[rt].lson, l, mid, L, R) + query(Tree[rt].rson, mid + 1, r, L, R);
}

int query(int rt1, int rt2, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
        return Tree[rt2].num - Tree[rt1].num;
    if (r < L || l > R)
        return 0;
    int mid = (l + r) >> 1;
    return query(Tree[rt1].lson, Tree[rt2].lson, l, mid, L, R) + query(Tree[rt1].rson, Tree[rt2].rson, mid + 1, r, L, R);
}