#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;

int total = 1;

struct NODE
{
    bool last;
    int son[10];
    int post;
} Node[25];
int n, m, P;
char A[110];
struct MATRIX
{
    int n, m;
    int arr[25][25];
} f, E;

MATRIX operator*(MATRIX a, MATRIX b)
{
    MATRIX c;
    for (int i = 1; i <= a.n; i++)
        for (int j = 1; j <= b.m; j++)
        {
            c.arr[i][j] = 0;
            for (int k = 1; k <= a.m; k++)
            {
                c.arr[i][j] += a.arr[i][k] * b.arr[k][j];
                c.arr[i][j] %= P;
            }
        }
    c.n = a.n;
    c.m = b.m;
    return c;
}

MATRIX power(MATRIX a, ll b)
{
    MATRIX ans = E;
    while (b > 0)
    {
        if (b & 1)
            ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}

void add()
{
    int cur = 1;
    int len = strlen(A);
    for (int i = 0; i < len; i++)
    {
        if (Node[cur].son[A[i] - '0'] == 0)
            Node[cur].son[A[i] - '0'] = ++total;
        cur = Node[cur].son[A[i] - '0'];
    }
    Node[cur].last = true;
}

void addedge()
{
    queue<int> Q;
    for (int i = 0; i <= 9; i++)
    {
        if (Node[1].son[i] == 0)
            Node[1].son[i] = 1;
        else
        {
            Node[Node[1].son[i]].post = 1;
            Q.push(Node[1].son[i]);
        }
    }
    while (!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        for (int i = 0; i < 10; i++)
        {

            if (Node[cur].son[i] != 0)
            {
                Q.push(Node[cur].son[i]);
                Node[Node[cur].son[i]].post = Node[Node[cur].post].son[i];
            }
            else
            {
                Node[cur].son[i] = Node[Node[cur].post].son[i];
            }
        }
        Node[cur].last |= Node[Node[cur].post].last;
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &P);
    scanf("%s", A);
    add();
    addedge();
    f.n = f.m = E.n = E.m = total;
    for (int i = 1; i <= total; i++)
    {
        E.arr[i][i] = 1;
    }
    for (int i = 1; i <= total; i++)
    {
        if (Node[i].last)
            continue;
        for (int j = 0; j <= 9; j++)
        {
            if (Node[Node[i].son[j]].last)
                continue;
            f.arr[i][Node[i].son[j]]++;
        }
    }
    f = power(f, n);
    int ANS = 0;
    for (int i = 1; i <= total; i++)
    {
        ANS = (ANS + f.arr[1][i]) % P;
    }
    printf("%d\n", ANS);
    system("pause");
    return 0;
}