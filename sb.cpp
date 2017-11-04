void change(int v, int val)
{
  if (lazy1[v] == -1 && lazy2[v] == -1)
    lazy2[v] = val;
  if (lazy1[v] != -1)
    lazy1[v] = min(lazy1[v], val);
  if (lazy2[v] != -1)
    lazy2[v] = min(lazy2[v], val);
  tree[v] = min(tree[v], val);
}
void pushdown(int v)
{
  if (lazy1[v] != -1)
  {
    lazy1[v << 1] = lazy1[v << 1 | 1] = lazy1[v];
    lazy2[v << 1] = lazy2[v << 1 | 1] = -1;
    tree[v << 1] = tree[v << 1 | 1] = lazy1[v];
    lazy1[v] = -1;
  }
  if (lazy2[v] != -1)
  {
    change(v << 1, lazy2[v]);
    change(v << 1 | 1, lazy2[v]);
    lazy2[v] = -1;
  }
}
