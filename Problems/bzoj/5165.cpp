#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int fa[3000010],ts,in[3000010],Q1,tot,qtot;

void Read(int & p)  
{  
    p=0;  
    int flag=1;  
    char c=getchar();  
    while(c<'0' or c>'9')   
    {  
        if(c=='-') flag=-1;  
        c=getchar();  
    }  
    while(c>='0' and c<='9')  
        p=p*10+(c-'0'),c=getchar();  
    p*=flag;  
}  

int Head2[3000010],Next2[3000010],To[3000010],cnt2;
void addedge(int u,int v){
    cnt2++;
    Next2[cnt2]=Head2[u];
    Head2[u]=cnt2;
    To[cnt2]=v;
}
bool visited[3000010];
struct QQ{
    int k,a[1010];
}Q[1010];

char op;
int f;

int maxsonid[3000010],size[3000010],dep[3000010],top[3000010];

void dfs1(int x, int father, int depth)
{
  fa[x] = father, size[x] = 1, maxsonid[x] = 0, dep[x] = depth;
  int maxsize = 0;
  for (int i = Head2[x]; i; i=Next2[i])
  {
    int v = To[i];
    dfs1(v, x, depth + 1);
    size[x] += size[v];
    if (maxsize < size[v])
        maxsize = size[v],maxsonid[x] = v;
  }
}

void dfs2(int x, int ancestor)
{
  in[x] = ++ts, top[x] = ancestor;
  if (maxsonid[x])
    dfs2(maxsonid[x], ancestor);
  for (int i = Head2[x]; i; i=Next2[i])
  {
    int v = To[i];
    if (v != maxsonid[x])
      dfs2(v,v);
  }
}

int lca(int x, int y)
{
  int res = 0;
  while (top[x] != top[y])
  {
    if (dep[top[x]] < dep[top[y]])
      swap(x, y);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y])
    swap(x, y);
  return y;
}


int main() {
    Read(Q1);
    tot=1;
    fa[1]=1;
    bool flag=false;
    for (int i = 1; i <= Q1; i++){
        op='0';
        while(op!='A'&&op!='Q')
            op=getchar();
        if (op=='A'){
            Read(f);
            if (i==3&&f==1) flag=true;
            addedge(f,++tot);
            fa[tot]=tot;
        }else{
            qtot++;
            Read( Q[qtot].k);
            for (int j = 1; j <= Q[qtot].k; j++)
                Read(Q[qtot].a[j]);
        }   
    }
    dfs1(1, 1, 1);
    dfs2(1, 1);
    for (int i = 1; i <= qtot; i++){
        int mn=0x3f3f3f3f,mx=0,mnid=0,mxid=0;
        for (int j = 1; j <= Q[i].k; j++){
            if (in[Q[i].a[j]]<mn)
                mn=in[Q[i].a[j]],mnid=Q[i].a[j];
            if (in[Q[i].a[j]]>mx)
                mx=in[Q[i].a[j]],mxid=Q[i].a[j];
        }
        printf("%d\n", lca(mnid,mxid));
    }
    //system("pause");
    return 0;
}