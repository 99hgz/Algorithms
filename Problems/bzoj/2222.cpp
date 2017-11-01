#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;

struct NODE
{
    int last;
    int son[26];
    int post;
} Node[1000000];
char A[1000010];
int total, n;
void add()
{
    int cur = 0;
    int len = strlen(A);
    for (int i = 0; i < len; i++)
    {
        if (Node[cur].son[A[i] - 'a'] == 0)
            Node[cur].son[A[i] - 'a'] = ++total;
        cur = Node[cur].son[A[i] - 'a'];
    }
    Node[cur].last++;
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
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(Node, 0, sizeof Node);
        total = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%s", A);
            add();
        }
        addedge();
        scanf("%s", A + 1);
        int len = strlen(A + 1);
        int cur = 0, ans = 0;
        for (int i = 1; i <= len; i++)
        {
            cur = Node[cur].son[A[i] - 'a'];
            ans += Node[cur].last;
            Node[cur].last = 0;
            int tmp = cur;
            while (tmp)
            {
                tmp = Node[tmp].post;
                if (tmp == 0 || Node[tmp].last == 0)
                    break;
                ans += Node[tmp].last;
                Node[tmp].last = 0;
            }
        }
        printf("%d\n", ans);
    }

    system("pause");
    return 0;
}