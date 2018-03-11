void init()
{
    last = root = ++cnt;
}

void extend(int ch)
{
    int p = last, np = last = ++cnt;
    len[np] = len[p] + 1;
    while (p && !a[p][ch])
        a[p][ch] = np, p = fa[p];
    if (!p)
        fa[np] = root;
    else
    {
        int q = a[p][ch];
        if (len[q] == len[p] + 1)
            fa[np] = q;
        else
        {
            int nq = ++cnt;
            len[nq] = len[p] + 1;
            memcpy(a[nq], a[q], sizeof a[q]);
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while (p && a[p][ch] == q)
                a[p][ch] = nq, p = fa[p];
        }
    }
}