#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define min(x,y) ((x<y)?(x):(y))
using namespace std;
const int MAX=0x5fffffff;//
int tab[250][250];//邻接矩阵 
int dis[250];//距源点距离,分层图 
int q[2000],h,r;//BFS队列 ,首,尾 
int N,M,ANS;//N:点数;M,边数 
int BFS()
{
     int i,j;
     memset(dis,0xff,sizeof(dis));//以-1填充 
     dis[1]=0;
     h=0;r=1;
     q[1]=1;
     while (h<r)
     {
           j=q[++h];
           for (i=1;i<=N;i++)
               if (dis[i]<0 && tab[j][i]>0)
               {
                  dis[i]=dis[j]+1; 
                  q[++r]=i;
               }
     }
     if (dis[N]>0)
        return 1;
     else
        return 0;//汇点的DIS小于零,表明BFS不到汇点 
}
//Find代表一次增广,函数返回本次增广的流量,返回0表示无法增广 
int find(int x,int low)//Low是源点到现在最窄的(剩余流量最小)的边的剩余流量
{
    int i,a=0;
    if (x==N)return low;//是汇点 
    for (i=1;i<=N;i++)
    if (tab[x][i] >0 //联通 
     && dis[i]==dis[x]+1 //是分层图的下一层 
     &&(a=find(i,min(low,tab[x][i]))))//能到汇点(a <> 0) 
    {
       tab[x][i]-=a;
       tab[i][x]+=a;
       return a;
    }
    return 0;
    
}
int main()
{
    //freopen("ditch.in" ,"r",stdin );
    //freopen("ditch.out","w",stdout);
    int i,j,f,t,flow,tans;
    while (scanf("%d%d",&M,&N)!=EOF){
    memset(tab,0,sizeof(tab));
    for (i=1;i<=M;i++)
    {
        scanf("%d%d%d",&f,&t,&flow);
        tab[f][t]+=flow;
    }
    //
    ANS=0;
    while (BFS())//要不停地建立分层图,如果BFS不到汇点才结束 
    {
          while(tans=find(1,0x7fffffff))ANS+=tans;//一次BFS要不停地找增广路,直到找不到为止 
    }
    printf("%d\n",ANS);
    }
    system("pause");
}
/**************************************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
int N, NP, NC, M;
struct Edge
{
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
} es[150 * 150];
int R, S, T;
vector<int> tab[109]; // 边集
int dis[109];
int current[109];
void addedge(int u, int v, int cap)
{
    tab[u].push_back(R);
    es[R++] = Edge(u, v, cap); // 正向边
    tab[v].push_back(R);
    es[R++] = Edge(v, u, 0); // 反向边容量为0
    // 正向边下标通过异或就得到反向边下标, 2 ^ 1 == 3 ; 3 ^ 1 == 2
}
int BFS()
{
    queue<int> q;
    q.push(S);
    memset(dis, 0x3f, sizeof(dis));
    dis[S] = 0;
    while (!q.empty())
    {
        int h = q.front();
        q.pop();
        for (int i = 0; i < tab[h].size(); i++)
        {
            Edge &e = es[tab[h][i]];
            if (e.cap > 0 && dis[e.v] == 0x3f3f3f3f)
            {
                dis[e.v] = dis[h] + 1;
                q.push(e.v);
            }
        }
    }
    return dis[T] < 0x3f3f3f3f; // 返回是否能够到达汇点
}
int dinic(int x, int maxflow)
{
    if (x == T)
        return maxflow;
    // i = current[x] 当前弧优化
    for (int i = current[x]; i < tab[x].size(); i++)
    {
        current[x] = i;
        Edge &e = es[tab[x][i]];
        if (dis[e.v] == dis[x] + 1 && e.cap > 0)
        {
            int flow = dinic(e.v, min(maxflow, e.cap));
            if (flow)
            {
                e.cap -= flow; // 正向边流量降低
                es[tab[x][i] ^ 1].cap += flow; // 反向边流量增加
                return flow;
            }
        }
    }
    return 0; // 找不到增广路 退出
}
int DINIC()
{
    int ans = 0;

    while (BFS()) // 建立分层图
    {
        int flow;
        memset(current, 0, sizeof(current)); // BFS后应当清空当前弧数组
        while (flow = dinic(S, 0x3f3f3f3f)) // 一次BFS可以进行多次增广
            ans += flow;
    }
    return ans;
}
int main()
{
    while (scanf("%d%d%d%d", &N, &NP, &NC, &M) != EOF)
    {
        R = 0;
        S = N;
        T = N + 1;
        for (int i = 0; i <= T; i++)
            tab[i].clear();
        for (int i = 0; i < M; i++)
        {
            int u, v, cap;
            scanf(" (%d,%d)%d", &u, &v, &cap);
            addedge(u, v, cap);
        }
        for (int i = 0; i < NP; i++)
        {
            int u, p;
            scanf(" (%d)%d", &u, &p);
            addedge(S, u, p);
        }
        for (int i = 0; i < NC; i++)
        {
            int u, c;
            scanf(" (%d)%d", &u, &c);
            addedge(u, T, c);
        }

        printf("%d\n", DINIC());
    }
    return 0;
}