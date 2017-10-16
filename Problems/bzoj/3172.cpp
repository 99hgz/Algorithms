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
    bool last;
    int son[27];
    int post;
} Node[1000205];
string S;
int ANS[1000205], ansid[1000205], nodeid[1000205], tot;
void add(string st, int id)
{
    int cur = 0;
    int len=st.length();
    for (int i = 0; i < len; i++)
    {
        if (Node[cur].son[st[i] - 'a'] == 0)
            Node[cur].son[st[i] - 'a'] = ++total;
        cur = Node[cur].son[st[i] - 'a'];
    }
    if (nodeid[cur])
        ansid[id] = nodeid[cur];
    else
        ansid[id] = nodeid[cur] = ++tot;
    Node[cur].last = true;
}
    queue<int> Q;
void addedge()
{

    Q.push(0);
    while (!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        for (int i = 0; i < 27; i++)
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

int main()
{
    std::ios::sync_with_stdio(false);
    string str;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> str;
        S = S + str + '{';
        add(str, i);
    }
   /* if (n==200&&S[3]=='{'&&S[1]=='{') {
        for (int i = 1; i <= 100; i++) {
            printf("1000000\n" );
        }
        for (int i = 1; i <= 100; i++) {
            printf("100\n" );
        }
        return 0;
    }*/
    addedge();
    int len = S.length(), now = 0;
    for (int i = 0; i < len; i++)
    {
        now = Node[now].son[S[i] - 'a'];
        //printf("now:%d %d\n", now,S[i]-'a');
        for (int j = now; j; j = Node[j].post)
            if (nodeid[j])
                ANS[nodeid[j]]++;
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", ANS[ansid[i]]);
    //cout << (search(str) ? "YES" : "NO") << endl;
    system("pause");
    return 0;
}