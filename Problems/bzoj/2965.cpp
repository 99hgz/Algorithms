#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
typedef long long ll;

#define pi acos(-1)

int n,m,cnt,u,v,h;

//点
struct POINT{
    int x,y;
    POINT(int x=0,int y=0):x(x),y(y){}
}p[400010];

POINT operator - (POINT a,POINT b){
    return (POINT){a.x-b.x,a.y-b.y};
}

//有向线段
struct LINE{
    int u,v,len;
    double angle;
    LINE(int u = 0, int v = 0, int len = 0) : u(u), v(v), len(len){
        POINT tmp=p[v]-p[u];
        angle=atan2(tmp.y,tmp.x);
        if (angle<0) angle+=2.0*pi;
    }
}line[400010];

vector<int>OutDegree[400010];

bool SortWithPolarAngle(int a,int b){
    return line[a].angle<line[b].angle;
}

const double eps=1.0e-8;
bool dcmp(double a,double b){
    return fabs(a-b)<eps;
}

double cross(POINT a,POINT b){
    return (double)a.x*b.y-(double)a.y*b.x;
}

namespace G{
    bool vis[400010];
    int region_tot;
    double S[400010];
    int belong[400010],Rank[400010],inf_area;

    void find_region(int u,int eid){
        if (vis[eid])return;
        region_tot++;
        double area=0;
        while(!vis[eid]){
            int v=line[eid].v;
            area+=cross(p[u],p[v]);
            vis[eid]=true;
            u=v;
            belong[eid]=region_tot;
            if (!Rank[eid^1]) eid=OutDegree[v].back();
            else eid=OutDegree[v][Rank[eid^1]-1];
        }
        if (area<0) 
            inf_area=region_tot;
        S[region_tot]=area/2;
    }

    void work(){
        for (int i = 1; i <= n; i++){
            sort(OutDegree[i].begin(),OutDegree[i].end(),SortWithPolarAngle);
            int rk=0;
            for(int j=0;j<OutDegree[i].size();j++){
                int e=OutDegree[i][j];
                Rank[e]=rk++;
            }
        }

        for (int i = 1; i <= n; i++){
            for(int j=0;j<OutDegree[i].size();j++)
                find_region(i,OutDegree[i][j]);
        }
    }
}

struct QUERY{
    int id;
    double x,y;
    QUERY(POINT a):id(0),x(a.x),y(a.y){}
    QUERY():id(0),x(0),y(0){}
}que[400010];
bool que_cmpwithx(QUERY a,QUERY b){
    return a.x<b.x;
}

struct Key_Point{
    int id,x,y;
}kpt[400010];

int quepos[400010];

double nowx;

struct Info{
    int id;
    double x,y,k;
    Info(int id,QUERY a,QUERY b):id(id),x(a.x),y(a.y){
        k=(b.y-a.y)/(b.x-a.x);
    }
};
bool operator <(Info a,Info b){
    double y1=a.y+a.k*(nowx-a.x);
    double y2=b.y+b.k*(nowx-b.x);
    if (!dcmp(y1,y2)) return y1<y2;
    return a.k<b.k;
}

set<Info>s;
set<Info>::iterator kptit[400010];
int q;

namespace scanning_line{

    bool kpt_cmpwithx(Key_Point a,Key_Point b){
        if (dcmp(a.x,b.x))
            return a.id<b.id;
        return a.x<b.x;
    }

    int ktot;

    void work(){
        ktot=1;
        for (int i = 2; i <= cnt; i++){
            if (p[line[i].v].x<p[line[i].u].x)continue;
            if (dcmp(p[line[i].v].x,p[line[i].u].x))continue;
            kpt[++ktot]=(Key_Point){i,p[line[i].u].x,p[line[i].u].y};
            kpt[++ktot]=(Key_Point){-i,p[line[i].v].x,p[line[i].v].y};
        }

        sort(que+1,que+1+q,que_cmpwithx);
        sort(kpt+2,kpt+1+ktot,kpt_cmpwithx);
        int kptpos=2;
        for (int i = 1; i <= q; i++){
            while(kptpos<=ktot&&kpt[kptpos].x<=que[i].x){
                Key_Point cur=kpt[kptpos];
                nowx=cur.x;
                if (cur.id<0){
                    cur.id=-cur.id;
                    s.erase(kptit[cur.id]);
                }
                else
                    kptit[cur.id]=s.insert(Info(cur.id,p[line[cur.id].u],p[line[cur.id].v])).first;
                
                kptpos++;
            }
            nowx=que[i].x;
            QUERY a=que[i],b=a;
            b.x+=1;
            set<Info>::iterator it=s.lower_bound(Info(0,a,b));
            if (it==s.end())
                quepos[que[i].id]=-1;
            else
                quepos[que[i].id]=G::belong[(*it).id^1];
        }
    }
}

namespace dinic{
    int S,T,Q[100010],dep[100010];
    int tot,Head[100010],Next[100010],Val[100010],cur[100010]


    bool bfs()
    {
        memset(dep, -1, sizeof dep);
        int t = 0, w = 1;
        Q[w] = S;
        dep[S] = 0;
        while (t != w)
        {
            t++;
            int u = Q[t];
            for (int it = Head[u]; it; it = Next[it])
            {
                int v = To[it];
                if (Val[it] > 0 && dep[v] == -1)
                {
                    dep[v] = dep[u] + 1;
                    w++;
                    Q[w] = v;
                }
            }
        }
        return dep[T] != -1;
    }

    int dfs(int x, int flow)
    {
        if (x == T)
            return flow;
        int used = 0;
        for (int it = cur[x]; it; it = Next[it])
        {
            int v = To[it];
            if (dep[v] == dep[x] + 1)
            {
                int tmp = dfs(v, min(Val[it], flow - used));
                used += tmp;
                Val[it] -= tmp;
                Val[it ^ 1] += tmp;
                cur[x] = it;
                if (used == flow)
                    return flow;
            }
        }
        if (used == 0)
            dep[x] = -1;
        return used;
    }

    int dinic()
    {
        int ans = 0;
        while (bfs())
        {
            for (int i = 1; i <= T; i++)
                cur[i] = Head[i];
            ans += dfs(S, 0x3f3f3f3f);
        }
        return ans;
    }

    void addedge(int u, int v, int flow)
    {
        tot++;
        Next[tot] = Head[u];
        Head[u] = tot;
        Val[tot] = flow;
        To[tot] = v;
        tot++;
        Next[tot] = Head[v];
        Head[v] = tot;
        Val[tot] = 0;
        To[tot] = u;
    }
}

int main() {
    //freopen("z:/data6.in", "r", stdin);
    //freopen("z:/data9.out", "w", stdout);
    
    scanf("%d%d%d", &q, &n,&m);

    for (int i = 1; i <= q; i++){
        que[i].id=i;
        scanf("%lf%lf", &que[i].x,&que[i].y);
    }

    for (int i = 1; i <= n; i++)
        scanf("%d%d",&p[i].x,&p[i].y);
    cnt=1;
    for (int i = 1; i <= m; i++){
        scanf("%d%d%d", &u,&v,&h);
        line[++cnt]=LINE(u,v,h);
        OutDegree[u].push_back(cnt);
        line[++cnt]=LINE(v,u,h);
        OutDegree[v].push_back(cnt);
    }
    G::work();

    scanning_line::work();
    for (int i = 1; i <= q; i++)
        if (quepos[i]==G::inf_area) quepos[i]=-1;

    dinic::S=G::region_tot+2;
    dinic::tot=1;
    for (int i = 2; i <= cnt; i+=2){
        if (G::belong[i]==G::inf_area){
            dinic::addedge(S,G::belong[i],line[i].len);
            continue;
        }
        if(G::belong[i^1]==G::inf_area){
            dinic::addedge(S,G::belong[i^1],line[i].len);
            continue;
        }
        dinic::addedge(G::belong[i],G::belong[i^1],line[i].len);
        dinic::addedge(G::belong[i^1],G::belong[i],line[i].len);
    }

    dinic::T=G::region_tot+1;
    for (int i = 1; i <= g::region_tot; i++)
        dinic::addedge(i,T,0x3f3f3f3f);
    

    //system("pause");
    return 0;
}