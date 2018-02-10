#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef int ll;

struct queNode
{
  int n;
  ll d;
} quenode;
struct vecNode
{
  int v;
  ll w;
} vecnode;
struct cmp
{
  bool operator()(queNode a, queNode b) { return a.d > b.d; }
};

int n, m, s, e, a, b, c;
bool visited[1001000];
ll d[1001000];
vector<vecNode> vec[1001000];

priority_queue<queNode, vector<queNode>, cmp> q;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void addedge(int u, int v, ll w)
{
  vecnode.v = v;
  vecnode.w = w;
  vec[u].push_back(vecnode);
}

int dijkstra(int s)
{
  for (int i = 1; i <= n; i++)
  {
    d[i] = 0x7fffffff;
    visited[i] = false;
  }
  quenode.d = 0;
  quenode.n = s;
  d[s] = 0;
  q.push(quenode);
  queNode tmp;
  while (!q.empty())
  {
    tmp = q.top();
    q.pop();
    if (visited[tmp.n])
      continue;
    visited[tmp.n] = true;
    for (int i = 0; i < vec[tmp.n].size(); i++)
    {
      int u = tmp.n, v = vec[tmp.n][i].v;
      if ((!visited[v]) && (d[v] > d[u] + vec[u][i].w))
      {
        d[v] = d[u] + vec[u][i].w;
        quenode.d = d[v];
        quenode.n = v;
        q.push(quenode);
      }
    }
  }
}
int T,rxa,rxc,rya,ryc,rp,x,y,z;
int main()
{
  n=read();m=read();
    T=read();rxa=read();rxc=read();rya=read();ryc=read();rp=read();
    int a,b;
    for(int i=1;i<=T;i++)
    {
        x=((ll)x*rxa+rxc)%rp;
        y=((ll)y*rya+ryc)%rp;
        a=min(x%n+1,y%n+1);
        b=max(y%n+1,y%n+1);
        addedge(a,b,100000000-100*a);
    }
    for(int i=1;i<=m-T;i++)
    {
        x=read(),y=read(),z=read();
        addedge(x,y,z);
    }
  dijkstra(1);
  printf("%d\n", d[n]);
  system("pause");
  return 0;
}