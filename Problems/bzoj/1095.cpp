#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
typedef long long ll;
#define G greater<int>
int n, k, u, v, w;
vector<int> vec[100010];
int size[100010], f[100010], root, ans, father[100010], deep[100010];
bool vis[100010];

struct DELETE_HEAP
{
    multiset<int, G> st;
    int id;
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
        printf("%d erase:%d\n", id, x);
        st.erase(st.find(x));
    }
    void insert(int x)
    {
        if (x == 0)
            return;
        printf("%d insert:%d\n", id, x);
        st.insert(x);
    }
} heap1[100010], heap2[100010], global_heap;

int st[100010][20], lighton[100010];

void addedge(int u, int v)
{
    vec[u].push_back(v);
}

void getroot(int treesize, int x, int fa)
{
    size[x] = 1, f[x] = 0;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i];
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
        int P = vec[x][i];
        if ((P != fa) && (!vis[P]))
            res += getsize(P, x);
    }
    return res;
}

void solve(int x, int fa)
{
    //printf("%d\n", x);
    father[x] = fa;
    vis[x] = true;
    for (int i = 0; i < vec[x].size(); i++)
    {
        int P = vec[x][i];
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

//*************************
int Root;
void turnon(int source, int x)
{
    if (x == Root)
        return;
    //printf("%d->%d\n", source, x);
    int tmp = heap1[x].top();
    heap1[x].insert(lca(source, father[x]));
    if (tmp != heap1[x].top())
    {
        int tmp2 = heap2[father[x]].top();
        int tmp3 = heap2[father[x]].ctop();
        heap2[father[x]].erase(tmp);
        heap2[father[x]].insert(heap1[x].top());
        if ((tmp2 != heap2[father[x]].top() || tmp3 != heap2[father[x]].ctop()))
        {
            if (tmp2 && tmp3)
                global_heap.erase(tmp2 + tmp3);
            if (heap2[father[x]].top() && heap2[father[x]].ctop())
                global_heap.insert(heap2[father[x]].top() + heap2[father[x]].ctop());
        }
    }
    turnon(source, father[x]);
}

void turnoff(int source, int x)
{
    if (x == Root)
        return;
    printf("turnoff%d->%d\n", source, x);
    int tmp = heap1[x].top();
    heap1[x].erase(lca(source, father[x]));
    if (tmp != heap1[x].top())
    {
        int tmp2 = heap2[father[x]].top();
        int tmp3 = heap2[father[x]].ctop();
        if (tmp)
        {
            heap2[father[x]].erase(tmp);
            //printf("erase:%d insert:%d %d %d %d\n", tmp, heap1[x].top(), tmp2, tmp3, heap2[father[x]].ctop());
        }

        heap2[father[x]].insert(heap1[x].top());
        if ((tmp2 != heap2[father[x]].top() || tmp3 != heap2[father[x]].ctop()))
        {
            if (tmp2 && tmp3)
                global_heap.erase(tmp2 + tmp3);
            if (heap2[father[x]].top() && heap2[father[x]].ctop())
                global_heap.insert(heap2[father[x]].top() + heap2[father[x]].ctop());
        }
    }
    turnoff(source, father[x]);
}

int main()
{
    scanf("%d", &n);
    int light = n;
    for (int i = 1; i <= n; i++)
    {
        heap1[i].id = i * 10 + 1;
        heap2[i].id = i * 10 + 2;
    }
    global_heap.id = 0;
    ans = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }

    lca_dfs(1, 0, 1);
    init_st();

    root = 0;
    f[0] = 0x3f3f3f3f;
    getroot(n, 1, 0);
    Root = root;
    solve(root, root);
    //建树

    for (int i = 1; i <= n; i++)
    {
        lighton[i] = true;
        turnon(i, i);
    }
    /*printf("%d\n", heap2[3].size());
    for (auto v : heap2[3].st)
    {
        printf("%d\n", v);
    }*/

    int Q;
    scanf("%d", &Q);
    char CASE[10];
    for (int i = 1; i <= Q; i++)
    {
        scanf("%s", CASE);
        if (CASE[0] == 'G')
        {
            if (light == 0)
                printf("-1\n");
            else if (light == 1)
                printf("0\n");
            else
                printf("%d\n", global_heap.top());
        }
        else
        {
            int num;
            scanf("%d", &num);
            if (lighton[num])
            {
                turnoff(num, num);
                light--;
            }
            else
            {
                turnon(num, num);
                light++;
            }
            lighton[num] ^= 1;
        }
    }

    /*scanf("%d", &q);
    printf("%d\n", ans);*/
    system("pause");
    return 0;
}