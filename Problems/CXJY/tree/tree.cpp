#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;
int qnum;
int Q[1000010];
//vector<int> vec[1000010];
int Next[1000010], head[1000010], tree[1000010], tot1;
int size[1000010], a[1000010], b[1000010], n, rt, freenum, valtoid[1000010], uniid[1000010], tot[1000010];
bool used[1000010];

void add(int x, int y)
{
    tot1++;
    Next[tot1] = head[x];
    head[x] = tot1;
    tree[tot1] = y;
}

void get_size(int x)
{
    //printf("%d\n", x);
    for (int i = head[x]; i; i = Next[i])
    //for (int i = 0; i < vec[x].size(); i++)
    {
        get_size(tree[i]);
        if (b[tree[i]] == 0)
            size[x] += size[tree[i]] + 1, tot[x]++, uniid[x] = tree[i];
    }
}

bool qd(int x)
{
    if (tot[x] > 1)
        return false;
    else
        return true;
}

int uni(int x)
{
    return uniid[x];
}

void dfs(int x)
{
    b[x] = Q[qnum];
    used[b[x]] = true;
    qnum--;
    if (qd(x) && (freenum + qnum == size[x]) && (qnum > 0))
    {
        int tmp = uni(x);
        size[x] -= size[tmp] + 1;
        dfs(uni(x));
        size[x] += size[tmp] + 1;
    }
}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i], &b[i]);
        used[b[i]] = true;

        if (a[i] == i)
            rt = i;
        else
            add(a[i], i);
        //vec[a[i]].push_back(i);
        valtoid[b[i]] = i;
    }
    get_size(rt);
    qnum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            Q[++qnum] = i;
            //Q.push(i);
        }
        else
        {
            if (size[valtoid[i]] == 0)
                continue;
            int tmp = qnum;
            if (qd(valtoid[i]) && (freenum + tmp == size[valtoid[i]]) && (tmp > 0))
            {
                dfs(uni(valtoid[i]));
            }
            freenum = (freenum + tmp - size[valtoid[i]]);
            qnum = 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", b[i]);
    }
    //system("pause");
    return 0;
}