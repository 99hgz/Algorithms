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
        for (int i = 0; i < 26; i++)
        {
            son[i] = 0;
        }
        last = false;
    }
    bool last;
    int son[26];
    int post;
} Node[1000000];

void add(string st)
{
    int cur = 0;
    for (int i = 0; i < st.length(); i++)
    {
        if (Node[cur].son[st[i] - 'a'] == 0)
            Node[cur].son[st[i] - 'a'] = ++total;
        cur = Node[cur].son[st[i] - 'a'];
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
        for (int i = 0; i < 26; i++)
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

bool search(string st)
{
    int cur = 0;
    for (int i = 0; i < st.length(); i++)
    {
        cur = Node[cur].son[st[i] - 'a'];
        if (Node[cur].last)
            return true;
    }
    return false;
}

int main()
{
    string str;

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> str;
        add(str);
    }
    addedge();
    cin >> str;
    cout << (search(str) ? "YES" : "NO") << endl;
    system("pause");
    return 0;
}