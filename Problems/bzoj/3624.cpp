#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int n, m, k, u, v, c, blocks, addedges;

int father[20010];
struct Node
{
    int u, v, c;
};
vector<Node> edges;
vector<Node> chosenedges;

void init()
{
    memset(father, -1, sizeof father);
}

void addedge(int u, int v, int c)
{
    edges.push_back((Node){u, v, c});
}

int get_father(int x)
{
    return father[x] == -1 ? x : father[x] = get_father(father[x]);
}

bool Union(int u, int v)
{
    int fa = get_father(u);
    int fb = get_father(v);
    if (fa == fb)
        return false;
    father[fa] = fb;
    return true;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &c);
        addedge(u, v, c);
    }
    init();
    blocks = n;
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i].c == 1)
        {
            if (Union(edges[i].u, edges[i].v))
            {
                blocks--;
            }
        }
    }
    if (blocks > k + 1)
    {
        printf("no solution\n");
        system("pause");
        return 0;
    }
    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i].c == 0)
        {
            if (Union(edges[i].u, edges[i].v))
            {
                chosenedges.push_back(edges[i]);
                blocks--;
            }
        }
    }
    if (blocks > 1)
    {
        printf("no solution\n");
        system("pause");
        return 0;
    }
    init();
    blocks = n;
    for (int i = 0; i < chosenedges.size(); i++)
    {
        if (Union(chosenedges[i].u, chosenedges[i].v))
        {
            blocks--;
        }
    }
    addedges = chosenedges.size();
    for (int i = 0; i < edges.size(); i++)
    {
        if (addedges == k)
            break;
        if (edges[i].c == 0)
        {
            if (Union(edges[i].u, edges[i].v))
            {
                chosenedges.push_back(edges[i]);
                blocks--;
                addedges++;
            }
        }
    }
    if (addedges < k)
    {
        printf("no solution\n");
        system("pause");
        return 0;
    }
    for (int i = 0; i < edges.size(); i++)
    {
        if (blocks == 1)
            break;
        if (edges[i].c == 1)
        {
            if (Union(edges[i].u, edges[i].v))
            {
                chosenedges.push_back(edges[i]);
                blocks--;
            }
        }
    }
    if (blocks == 1)
    {
        for (int i = 0; i < chosenedges.size(); i++)
        {
            printf("%d %d %d\n", chosenedges[i].u, chosenedges[i].v, chosenedges[i].c);
        }
    }
    else
    {
        printf("no solution\n");
        system("pause");
        return 0;
    }
    system("pause");
    return 0;
}