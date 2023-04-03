#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <iostream>
#include<string>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;
typedef bitset<1010> ll;
vector<ll> vec[1010 * 4];
int ID, m, n, u, v;
struct NODE
{
    int last;
    ll bit;
} Node[510];
struct LB
{
    ll f[1010];
    void insert(ll val)
    {
        for (int i = 1000; i >= 0; i--)
            if (val.test(i))
                if (f[i].none())
                {
                    f[i] = val;
                    break;
                }
                else
                    val ^= (f[i]);
    }
    void max()
    {
        ll res = 0;
        for (int i = 1000; i >= 0; i--)
            if (!res.test(i))res = (res ^ f[i]);
        bool flag=false;
        for(int i=1000;i>=0;i--)
            if (res.test(i)||flag){
                flag=true;
                printf("%d",res.test(i));
            }
        if (!flag) printf("0");
        printf("\n");
    }
} t;
void insert(int rt, int l, int r, int L, int R, ll val)
{
    if (L <= l && r <= R)
    {
        vec[rt].push_back(val);
        return;
    }
    if (l > R || r < L)
        return;
    int mid = (l + r) >> 1;
    insert(rt * 2, l, mid, L, R, val);
    insert(rt * 2 + 1, mid + 1, r, L, R, val);
}

void dfs(int rt, int l, int r, LB k)
{
    for (int i = 0; i < vec[rt].size(); i++)
        k.insert(vec[rt][i]);
    if (l == r)
    {
        k.max();
        return;
    }
    int mid = (l + r) >> 1;
    dfs(rt * 2, l, mid, k);
    dfs(rt * 2 + 1, mid + 1, r, k);
}

int main()
{
    scanf("%d", &ID);
    scanf("%d%d", &n, &m);
    string st;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        cin>>st;
        if (u==v) continue;
        if (Node[u].last != 0)
            insert(1, 1, m, Node[u].last, i - 1, Node[u].bit);
        if (Node[v].last != 0)
            insert(1, 1, m, Node[v].last, i - 1, Node[v].bit);
        Node[u].last = i;
        Node[v].last = i;
        ll tmp(st);
        //cout<<"read:"<<tmp.to_ullong()<<endl;

        Node[u].bit ^= tmp; 
        Node[v].bit ^= tmp;
    }
    for (int i = 1; i <= n; i++)
        if (Node[i].last != 0)
            insert(1, 1, m, Node[i].last, m, Node[i].bit);
        
    dfs(1, 1, m, t);
    system("pause");
}