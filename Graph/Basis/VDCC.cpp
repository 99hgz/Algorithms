#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
#define LL long long
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while (ch<'0' || ch>'9') {if (ch=='-') f=-1; ch=getchar();}
    while (ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
#define MAXN 100010
#define MAXM 500010
struct EdgeNode{int next,to;}edge[MAXM<<1];
int head[MAXN],cnt=1;
inline void AddEdge(int u,int v) {cnt++; edge[cnt].next=head[u]; head[u]=cnt; edge[cnt].to=v;}
inline void InsertEdge(int u,int v) {AddEdge(u,v); AddEdge(v,u);}
int N,M;
vector<int>BCC[MAXN];
#define Pa pair<int,int>
Pa st[MAXM]; int top;
int dfn[MAXN],low[MAXN],dfsn,son[MAXN],size[MAXN],cut[MAXN],bcc,belong[MAXN];
LL sum[MAXN];
inline void Tarjan(int now,int last)
{
    dfn[now]=low[now]=++dfsn;  LL su=0; size[now]=1;
    for (int i=head[now]; i; i=edge[i].next)
        if (!dfn[edge[i].to])
            {
                st[++top]=make_pair(now,edge[i].to); son[now]++;
                Tarjan(edge[i].to,now); low[now]=min(low[now],low[edge[i].to]);
                size[now]+=size[edge[i].to];
                if (dfn[now]<=low[edge[i].to])
                    {
                        sum[now]+=su*size[edge[i].to]; su+=(LL)size[edge[i].to];
                        cut[now]=1; bcc++; BCC[bcc].clear(); int tnow=-1,tto=-1;
                        while (tnow!=now && tto!=edge[i].to)
                            {
                                tnow=st[top].first,tto=st[top].second; top--;
                                if (belong[tnow]!=bcc) BCC[bcc].push_back(tnow),belong[tnow]=bcc;
                                if (belong[tto]!=bcc) BCC[bcc].push_back(tto),belong[tto]=bcc;
                            }
                    }
            }
        else if (dfn[edge[i].to]<dfn[now] && edge[i].to!=last)
            st[++top]=make_pair(now,edge[i].to),low[now]=min(low[now],dfn[edge[i].to]);
    if (last<0 && son[now]==1) cut[now]=0;
    sum[now]+=su*(N-su-1);
}
int main()
{
    N=read(),M=read();
    for (int x,y,i=1; i<=M; i++) x=read(),y=read(),InsertEdge(x,y);
    for (int i=1; i<=N; i++) if (!dfn[i]) Tarjan(i,-1);
    for (int i=1; i<=N; i++) printf("%lld\n",(LL)(sum[i]+N-1)*2);
    return 0;
}