#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;
typedef long long ll;

int n, total;

struct NODE
{
    int last;
    int son[26];
    int originson[26];
    int post;
} Node[100010];
char st[100010];
int pos;
int stringnode[10010];
vector<int> failtree[100010];
int timestamp;
int BIT[200010], in[100010], out[100010];
struct QRY
{
    int s1, ans;
};
vector<QRY> qry[100010];

//int qryhead[]

struct QRYINDEX
{
    int bh, index;
} qryindex[100100];
/*void add(int id,int pos)
{
    int cur = 0;
    for (int i = 0; i < pos; i++)
    {
    	//printf("%c",st[i]);
        if (Node[cur].son[st[i] - 'a'] == 0)
            Node[cur].son[st[i] - 'a'] = ++total;
        cur = Node[cur].son[st[i] - 'a'];
    }
    printf("add:%d\n",pos);
    Node[cur].last = id;
    stringnode[id]=cur;
}*/

void addedgeTOfailtree(int u, int v)
{
    //printf("add fail tree:%d %d\n", u, v);
    failtree[v].push_back(u);
}

void addedge()
{
    queue<int> Q;
    Q.push(0);
    while (!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        for (int i = 0; i < 26; i++)
        {
            if (Node[cur].son[i] != 0)
            {
                Q.push(Node[cur].son[i]);
                if (cur != 0)
                {
                    addedgeTOfailtree(Node[cur].son[i], Node[Node[cur].post].son[i]);
                    Node[Node[cur].son[i]].post = Node[Node[cur].post].son[i];
                }
                else
                {
                    addedgeTOfailtree(Node[cur].son[i], cur);
                }
            }
            else
            {
                Node[cur].son[i] = Node[Node[cur].post].son[i];
            }
        }
    }
}

int BITadd(int x, int val)
{
    for (; x <= timestamp; x += x & -x)
        BIT[x] += val;
}

int BITsum(int x)
{
    int res = 0;
    for (; x; x -= x & -x)
        res += BIT[x];
    return res;
}

void triedfs(int x, int dep)
{
    //printf("dfs:%d %d\n", x, in[x]);
    BITadd(in[x], 1);
    if (qry[x].size())
    {
        for (int i = 0; i < qry[x].size(); i++)
        {
            //printf("%d has a query with %d in=%d out=%d\n", x, qry[x][i].s1, in[qry[x][i].s1], out[qry[x][i].s1]);
            qry[x][i].ans =
                BITsum(out[qry[x][i].s1]) -
                BITsum(in[qry[x][i].s1] - 1);
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (Node[x].originson[i])
            triedfs(Node[x].originson[i], dep + 1);
    }
    BITadd(in[x], -1);
}

void failtreedfs(int x)
{
    in[x] = ++timestamp;
    //printf("failtreedfs:%d\n", x);

    for (int i = 0; i < failtree[x].size(); i++)
    {
        int v = failtree[x][i];
        failtreedfs(v);
    }
    //printf("failtreedfs:%d\n", x);
    out[x] = ++timestamp;
}
stack<int> S;
int main()
{
    int stid = 0;
    string str;
    cin >> str;
    int len = str.length();
    pos = 0;
    S.push(0);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == 'B')
        {
            S.pop();
        }
        else if (str[i] == 'P')
        {
            Node[S.top()].last = ++stid;
            stringnode[stid] = S.top();
            //printf("point=%d\n", S.top());
        }
        else
        {
            if (Node[S.top()].son[str[i] - 'a'] == 0)
                Node[S.top()].son[str[i] - 'a'] = ++total;
            if (Node[S.top()].originson[str[i] - 'a'] == 0)
                Node[S.top()].originson[str[i] - 'a'] = total;
            S.push(Node[S.top()].son[str[i] - 'a']);
        }
    }
    addedge();
    failtreedfs(0);
    int q, x, y;
    scanf("%d", &q);
    //printf("%d",q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d", &x, &y);
        qry[stringnode[y]].push_back((QRY){stringnode[x], 0});
        qryindex[i] = (QRYINDEX){stringnode[y], qry[stringnode[y]].size() - 1};
    }
    triedfs(0, 1);
    for (int i = 1; i <= q; i++)
        printf("%d\n", qry[qryindex[i].bh][qryindex[i].index].ans);
    //system("pause");
    return 0;
}