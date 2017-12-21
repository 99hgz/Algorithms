#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define G greater<int>
int fa[200010], size[200010], timestamp, maxsonid[200010], dep[200010], in[200010], top[200010], init[200010], val[200010], out[200010];
vector<int> vec[200010];
int a, b;
struct DELETE_HEAP
{
    multiset<int, G> st;
    int top()
    {
        if (st.size() == 0)
            return 0;
        return *st.begin();
    }
    int ctop()
    {
        if (st.size() <= 1)
            return 0;
        set<int, G>::iterator it = st.begin();
        return *(++it);
    }
    int size()
    {
        return st.size();
    }
    void erase(int x)
    {
        if (st.size() == 0 || x == 0)
            return;
        st.erase(st.find(x));
    }
    void insert(int x)
    {
        if (x == 0)
            return;
        st.insert(x);
    }
};

struct LIST
{
    int a, b, v;
} list[200010];

DELETE_HEAP Tree[200010 * 4];
int n, m, u, v, cases, x, y;

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

void dfs1(int x, int father, int depth)
{
    fa[x] = father, size[x] = 1, maxsonid[x] = 0, dep[x] = depth;
    int maxsize = 0;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i];
        if (v != father)
        {
            dfs1(v, x, depth + 1);
            size[x] += size[v];
            if (maxsize <= size[v])
                maxsize = size[v],
                maxsonid[x] = v;
        }
    }
}

void dfs2(int x, int father, int ancestor)
{
    in[x] = ++timestamp, top[x] = ancestor, init[timestamp] = val[x];
    if (maxsonid[x])
        dfs2(maxsonid[x], x, ancestor);
    for (int i = 0; i < vec[x].size(); i++)
    {
        int v = vec[x][i];
        if (v != father && v != maxsonid[x])
            dfs2(v, x, v);
    }
    out[x] = timestamp;
}

void modify(int rt, int l, int r, int L, int R, int v, int op)
{
    if (L <= l && r <= R)
    {
        if (op)
            Tree[rt].insert(v);
        else
            Tree[rt].erase(v);
        return;
    }
    if (r < L || l > R)
        return;
    int mid = (l + r) >> 1;
    modify(rt * 2, l, mid, L, R, v, op), modify(rt * 2 + 1, mid + 1, r, L, R, v, op);
}

int query(int rt, int l, int r, int x)
{
    if (l == r)
        return Tree[rt].top();
    int mid = (l + r) >> 1;
    if (x <= mid)
        return max(Tree[rt].top(), query(rt * 2, l, mid, x));
    else
        return max(Tree[rt].top(), query(rt * 2 + 1, mid + 1, r, x));
}

//rangevector
struct Node
{
    int l, r;
};
vector<Node> rgvec, revec;
bool cmp(Node a, Node b)
{
    return a.l < b.l;
};
void reverse()
{
    rgvec.push_back((Node){0, 0});
    rgvec.push_back((Node){n + 1, n + 1});
    sort(rgvec.begin(), rgvec.end(), cmp);
    revec.clear();
    for (int i = 1; i < rgvec.size(); i++)
        if (rgvec[i - 1].r + 1 <= rgvec[i].l - 1)
            revec.push_back((Node){rgvec[i - 1].r + 1, rgvec[i].l - 1});
}
//end

void Modify(int x, int y, int v, int op)
{
    rgvec.clear();
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        rgvec.push_back((Node){in[top[x]], in[x]});
        x = fa[top[x]];
    }
    if (dep[x] < dep[y])
        swap(x, y);

    rgvec.push_back((Node){in[y], in[x]});
    /*printf("ranges:\n");
    for (auto i : rgvec)
        printf("%d %d\n", i.l, i.r);
    printf("end-->\n");*/
    reverse();

    /*printf("reranges:\n");
    for (auto i : revec)
        printf("%d %d\n", i.l, i.r);

    printf("end\n");*/
    for (int i = 0; i < revec.size(); i++)
        modify(1, 1, n, revec[i].l, revec[i].r, v, op);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs1(1, 1, 1);
    dfs2(1, 1, 1);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &cases);
        if (cases == 0)
        {
            scanf("%d%d%d", &a, &b, &v);
            Modify(a, b, v, 1);
            list[i] = (LIST){a, b, v};
        }
        else if (cases == 1)
        {
            scanf("%d", &y);
            Modify(list[y].a, list[y].b, list[y].v, 0);
        }
        else
        {
            scanf("%d", &y);
            int tmp = query(1, 1, n, in[y]);
            printf("%d\n", tmp == 0 ? -1 : tmp);
        }
    }
    //system("pause");
    return 0;
}