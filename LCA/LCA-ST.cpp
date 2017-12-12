void lca_dfs(int x, int fa, int depth)
{
    st[x][0] = fa;
    deep[x] = depth;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i];
        if (P != fa)
            lca_dfs(P, x, depth + 1);
    }
}

void init_st()
{
    int deep = floor(log(n) / log(2));
    for (int j = 1; j <= deep; j++)
        for (int i = 1; i <= n; i++)
            if (st[i][j - 1] != -1)
                st[i][j] = st[st[i][j - 1]][j - 1];
}

int lca(int a, int b)
{
    int ua = a, ub = b;
    if (deep[a] < deep[b])
        swap(a, b);
    int depth = floor(log(deep[a] - 1) / log(2));
    for (int i = depth; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
            a = st[a][i];
    if (a == b)
        return deep[ua] + deep[ub] - 2 * deep[a];
    for (int i = depth; i >= 0; i--)
        if ((st[a][i] != -1) && (st[a][i] != st[b][i]))
        {
            a = st[a][i];
            b = st[b][i];
        }
    return deep[ua] + deep[ub] - 2 * deep[st[b][0]];
}