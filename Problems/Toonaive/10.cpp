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
        post = son[0] = son[1] = 0;
        last = false;
    }
    bool last;
    int son[2];
    int post;
} Node[1000000];

int st[1000], st2[1000];
char rd[1000];
int f[1000][1000][65];
void add(int len, int id)
{
    int cur = 0;
    for (int i = 1; i <= len; i++)
    {
        printf("%d", st[i]);
        if (Node[cur].son[st[i]] == 0)
            Node[cur].son[st[i]] = ++total;
        cur = Node[cur].son[st[i]];
    }
    printf("\n");
    Node[cur].last |= 1 << (id - 1);
}

void addedge()
{
    queue<int> Q;
    Q.push(0);
    while (!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        for (int i = 0; i <= 1; i++)
        {
            if (Node[cur].son[i] != 0)
            {
                Q.push(Node[cur].son[i]);
                if (cur != 0)
                    Node[Node[cur].son[i]].post = Node[Node[cur].post].son[i];
            }
            else
                Node[cur].son[i] = Node[Node[cur].post].son[i];
        }
    }
}
int m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", rd);
        int len = strlen(rd);
        for (int j = 0; j < len; j++)
            st[j + 1] = (rd[j] - '0');
        add(len, i);

        for (int j = 1; j <= len; j++)
            st2[j] = st[j];
        for (int j = (len + 1) / 2; j <= len; j++)
        {
            for (int k = 1; k <= j; k++)
                st[k] = st2[j + k - 1];
            add(j, i);
        }

        for (int j = 1; j * 2 <= len; j++)
        {
            swap(st[j], st[len - j + 1]);
            st[j] = 1 - st[j];
            st[len - j + 1] = 1 - st[len - j + 1];
        }
        add(len, i);

        for (int j = (len + 1) / 2; j <= len; j++)
        {
            for (int k = 1; k <= j; k++)
                st[k] = st2[j + k - 1];
            add(j, i);
        }
    }
    addedge();
    f[0][0][0] = 1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j <= total; j++)
            for (int k = 0; k <= 1; k++)
                for (int l = 0; l < (1 << n); l++)
                {
                    f[i + 1][Node[j].son[k]][l | Node[Node[j].son[k]].last] += f[i][j][l];
                    //printf("%d\n",l|Node[Node[j].son[k]].last);
                }
    int ans = 0;
    for (int j = 0; j <= total; j++)
        ans += f[m][j][(1 << n) - 1];
    printf("%d", ans);
    return 0;
}