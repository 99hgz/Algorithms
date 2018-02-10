#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;

int n, total;

struct NODE
{
    NODE()
    {
        post = 0;
        vis = 0;
        for (int i = 0; i < 4; i++)
        {
            son[i] = 0;
        }
        last = false;
    }
    bool last;
    int son[5];
    int post, vis;
} Node[10000010];
inline int getasd(char g)
{
    if (g == 'S')
        return 0;
    if (g == 'N')
        return 1;
    if (g == 'W')
        return 2;
    if (g == 'E')
        return 3;
}
void add(string st)
{
    int cur = 0, len = st.length();
    for (int i = 0; i < len; i++)
    {
        if (Node[cur].son[getasd(st[i])] == 0)
            Node[cur].son[getasd(st[i])] = ++total;
        cur = Node[cur].son[getasd(st[i])];
    }
    Node[cur].last = true;
}

void addedge()
{
    queue<int> Q;
    Q.push(0);
    while (!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++)
        {

            if (Node[cur].son[i] != 0)
            {
                Q.push(Node[cur].son[i]);
                if (cur != 0)
                    Node[Node[cur].son[i]].post = Node[Node[cur].post].son[i];
            }
            else
            {
                Node[cur].son[i] = Node[Node[cur].post].son[i];
            }
        }
    }
}

string str[100010];
int m;
int getans(string p)
{
    int cur = 0, l = 0, res = 0, len = p.length();
    for (int i = 0; i < len; i++)
    {
        cur = Node[cur].son[getasd(p[i])];
        l++;
        if (Node[cur].vis)
            res = l;
    }
    return res;
}

int main()
{
    string p;
    cin >> n >> m;
    cin >> p;
    for (int i = 1; i <= m; i++)
    {
        cin >> str[i];
        add(str[i]);
    }
    addedge();

    int cur = 0, len = p.length();
    for (int i = 0; i < len; i++)
    {
        cur = Node[cur].son[getasd(p[i])];
        for (int j = cur; j; j = Node[j].post)
            if (Node[j].vis)
                break;
            else
                Node[j].vis = true;
    }

    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", getans(str[i]));
    }
    // system("pause");
    return 0;
}