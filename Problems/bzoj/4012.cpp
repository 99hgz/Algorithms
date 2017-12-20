#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pr;
int n, k, u, v, w, tn, Hash[150010];
ll A, L, R, ans;
struct Node
{
    int v, w;
};
vector<Node> vec[150010];
int size[150010], f[150010], root, father[150010], deep[150010];
bool vis[150010];

int st[150010][20];
ll dis[150010][20];
struct Node2
{
    int pos, num;
    ll val;
};

bool cmp(const Node2 &a, const Node2 &b)
{
    return a.pos < b.pos;
}

vector<Node2> Troot[150010][2];
int tot, Root, val[150010], cases;
void addedge(int u, int v, int w)
{
    vec[u].push_back((Node){v, w});
}

void getroot(int treesize, int x, int fa)
{
    size[x] = 1, f[x] = 0;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i].v;
        if ((P != fa) && (!vis[P]))
        {
            getroot(treesize, P, x);
            size[x] += size[P];
            f[x] = max(f[x], size[P]);
        }
    }
    f[x] = max(f[x], treesize - size[x]);
    if (f[x] < f[root])
        root = x;
}

int getsize(int x, int fa)
{
    int res = 1;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i].v;
        if ((P != fa) && (!vis[P]))
            res += getsize(P, x);
    }
    return res;
}

void solve(int x, int fa)
{
    father[x] = fa;
    vis[x] = true;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i].v;
        if (!vis[P])
        {
            root = 0;
            getroot(getsize(P, x), P, 0);
            solve(root, x);
        }
    }
}

//*********************LCA

void lca_dfs(int x, int fa, int depth)
{
    st[x][0] = fa;
    deep[x] = depth;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i].v;
        if (P != fa)
        {
            lca_dfs(P, x, depth + 1);
            dis[P][0] = vec[x][i].w;
        }
    }
}

void init_st()
{
    int deep = floor(log(n) / log(2));
    for (int j = 1; j <= deep; j++)
        for (int i = 1; i <= n; i++)
            if (st[i][j - 1] != -1)
            {
                st[i][j] = st[st[i][j - 1]][j - 1];
                dis[i][j] = dis[st[i][j - 1]][j - 1] + dis[i][j - 1];
            }
}

ll _lca(int a, int b)
{
    int ua = a, ub = b;
    ll res = 0;
    if (deep[a] < deep[b])
        swap(a, b);
    int depth = floor(log(deep[a] - 1) / log(2));
    for (int i = depth; i >= 0; i--)
        if (deep[a] - (1 << i) >= deep[b])
        {
            res += dis[a][i];
            a = st[a][i];
        }
    if (a == b)
        return res;
    for (int i = depth; i >= 0; i--)
        if ((st[a][i] != -1) && (st[a][i] != st[b][i]))
        {
            res += dis[a][i] + dis[b][i];
            a = st[a][i];
            b = st[b][i];
        }
    return res + dis[a][0] + dis[b][0];
}

ll lca(int a, int b)
{
    ll tmp = _lca(a, b);
    //printf("lca %d %d=%lld\n", a, b, tmp);
    return tmp;
}

void Tmodify(int x, int id, int pos, ll val)
{
    if (Troot[x][id].size() == 0)
    {
        Troot[x][id].push_back((Node2){pos, 1, val});
        return;
    }
    if ((*(Troot[x][id].end() - 1)).pos == pos)
        ((*(Troot[x][id].end() - 1)).val) += val,
            ((*(Troot[x][id].end() - 1)).num)++;
    else
        Troot[x][id].push_back((Node2){pos, ((*(Troot[x][id].end() - 1)).num) + 1, val + ((*(Troot[x][id].end() - 1)).val)});
    /*printf("----------\n");
    for (auto it : Troot[x][id])
        printf("%d %d %lld\n", it.pos, it.num, it.val);
    printf("----------\n");*/
}

pr Tquery(int x, int id, int L, int R)
{
    vector<Node2>::iterator Lit = lower_bound(Troot[x][id].begin(), Troot[x][id].end(), (Node2){L, 0}, cmp);
    vector<Node2>::iterator Rit = lower_bound(Troot[x][id].begin(), Troot[x][id].end(), (Node2){R, 0}, cmp);
    if (Lit == Troot[x][id].end())
        return make_pair(0, 0);
    if ((*Troot[x][id].begin()).pos > R)
        return make_pair(0, 0);
    if ((Rit == Troot[x][id].end()) || (((*Rit).pos) > R))
        Rit--;
    /*printf("Tquery %d %d %d %d ----------\n", x, id, L, R);
    for (auto it : Troot[x][id])
        printf("%d %d %lld\n", it.pos, it.num, it.val);*/

    ll LL = (Lit == (Troot[x][id].begin())) ? 0 : ((*(Lit - 1)).val);
    ll Lnum = (Lit == (Troot[x][id].begin())) ? 0 : ((*(Lit - 1)).num);
    //printf("return %lld %lld----------\n", ((*Rit).val) - LL, (ll)((*Rit).num) - Lnum);
    return make_pair(((*Rit).val) - LL, (ll)((*Rit).num) - Lnum);
}

void modify(int source, int x, int val)
{
    Tmodify(x, 0, val, lca(source, x));
    if (father[x])
        Tmodify(x, 1, val, lca(source, father[x]));
    if (x != Root)
        modify(source, father[x], val);
}

void getans(int source, int x, int L, int R)
{
    //printf("getans:source=%d x=%d L=%d R=%d\n", source, x, L, R);
    int tmp = lca(x, source);
    pr res = Tquery(x, 0, L, R);
    ans += res.first + res.second * tmp;
    if (father[x])
    {
        res = Tquery(x, 1, L, R);
        ans -= res.first + res.second * lca(source, father[x]);
    }
    if (x != Root)
        getans(source, father[x], L, R);
}

vector<int> order[150010];

int main()
{
    int m;
    scanf("%d%d%lld", &n, &m, &A);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &val[i]);
        Hash[i] = val[i];
    }

    sort(Hash + 1, Hash + 1 + n);
    tn = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
    for (int i = 1; i <= n; i++)
    {
        val[i] = lower_bound(Hash + 1, Hash + 1 + tn, val[i]) - Hash;
        order[val[i]].push_back(i);
        //printf("trueval=%d\n", val[i]);
    }

    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    lca_dfs(1, 0, 1);
    init_st();

    root = 0;
    f[0] = 0x3f3f3f3f;
    getroot(n, 1, 0);
    Root = root;
    solve(root, 0);

    for (int i = 1; i <= tn; i++)
        for (int j = 0; j < order[i].size(); j++)
            modify(order[i][j], order[i][j], i);

    ll lastans = 0;
    for (int i = 1; i <= m; i++)
    {
        int u;
        ll a, b;
        scanf("%d%lld%lld", &u, &a, &b);
        L = min((a + lastans) % A, (b + lastans) % A),
        R = max((a + lastans) % A, (b + lastans) % A);
        ans = 0;
        if (L > Hash[tn])
        {
            printf("0\n");
            lastans = 0;
            continue;
        }
        L = lower_bound(Hash + 1, Hash + 1 + tn, L) - Hash;
        int it = lower_bound(Hash + 1, Hash + 1 + tn, R) - Hash;
        if (Hash[it] == R)
            R = it;
        else
            R = it - 1;
        getans(u, u, L, R);
        lastans = ans;
        printf("%lld\n", ans);
    }
    system("pause");
}
