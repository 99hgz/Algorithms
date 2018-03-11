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
        //补为2pi
        if (angle<0) angle+=2.0*pi;
        //printf("eid=%d angle=%.8lf\n",cnt,angle );
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
        //printf("regionid=%d\n",region_tot );
        double area=0;
        while(!vis[eid]){
            //printf("%d (%d,%d)->(%d,%d)\n", eid,p[line[eid].u].x,p[line[eid].u].y,p[line[eid].v].x,p[line[eid].v].y);
            int v=line[eid].v;
            area+=cross(p[u],p[v]);
            vis[eid]=true;
            u=v;
            belong[eid]=region_tot;
            if (!Rank[eid^1]) eid=OutDegree[v].back();
            else eid=OutDegree[v][Rank[eid^1]-1];
        }
       // printf("%.8lf\n", area);
        if (area<0) {//printf("ERR!\n" );
         inf_area=region_tot;}
        S[region_tot]=area/2;
    }

    void work(){
        for (int i = 1; i <= n; i++){
            sort(OutDegree[i].begin(),OutDegree[i].end(),SortWithPolarAngle);
            int rk=0;
            //printf("point %d\n",i );
            for(int j=0;j<OutDegree[i].size();j++){
                int e=OutDegree[i][j];
                Rank[e]=rk++;
                //printf("%d\n", e);
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
                    //printf("erase:%d %d(%d,%d) %d(%d,%d)\n",cur.id,line[cur.id].u,p[line[cur.id].u].x,p[line[cur.id].u].y,line[cur.id].v,p[line[cur.id].v].x,p[line[cur.id].v].y);
                    s.erase(kptit[cur.id]);
                }
                else{
                    //printf("insert:%d\n",cur.id );
                    kptit[cur.id]=s.insert(Info(cur.id,p[line[cur.id].u],p[line[cur.id].v])).first;
                    //printf("test it%d\n",(*kptit[cur.id]).id );
                }
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

namespace MST{
    struct GraphNode{
        int v, w;
    };
    vector<GraphNode> vec2[400010];
    
    int deep[400010], father[400010][20], fa[400010];
    int st[400010][20];
    int cnt;
    struct EDGE{
        int u, v, w;
    } edge[400010];
    bool cmp(EDGE a, EDGE b){return a.w < b.w;}
    
    void addedge(int u,int v,int w){
        //printf("addedge:%d %d %d\n", u,v,w);
        edge[++cnt]=(EDGE){u,v,w};
    }

    void addedgeTree(int u, int v, int w)
    {
        vec2[u].push_back((GraphNode){v, w});
        swap(u, v);
        vec2[u].push_back((GraphNode){v, w});
    }
    
    int gf(int x)
    {
        return fa[x] == 0 ? x : fa[x] = gf(fa[x]);
    }
    
    void build()
    {
        sort(edge + 1, edge + 1 + cnt, cmp);
        for (int i = 1; i <= cnt; i++)
        {
            int fx = gf(edge[i].u), fy = gf(edge[i].v);
            if (fx != fy)
            {
                fa[fx] = fy;
                addedgeTree(edge[i].u, edge[i].v, edge[i].w);
            }
        }
    }
    
    void dfs(int x, int fa, int w, int dep)
    {
        deep[x] = dep;
        father[x][0] = fa;
        st[x][0] = w;
        for (int i = 0; i < vec2[x].size(); i++)
        {
            int v = vec2[x][i].v;
            if (fa != v)
                dfs(v, x, vec2[x][i].w, dep + 1);
        }
    }
    
    void init()
    {
        for (int i = 1; i <= 18; i++)
            for (int j = 1; j <= G::region_tot; j++){
                    father[j][i] = father[father[j][i - 1]][i - 1];
                    st[j][i] = max(st[j][i - 1] , st[father[j][i - 1]][i - 1]);
                }
    }
    
    int lca(int a, int b)
    {
        int res = 0;
        if (deep[a] < deep[b])
            swap(a, b);
        int st2 = floor(log(deep[a] - 1) / log(2));
        for (int i = st2; i >= 0; i--)
            if (deep[a] - (1 << i) >= deep[b])
            {
                res = max(res , st[a][i]);
                a = father[a][i];
            }
        if (a == b)
            return res;
        for (int i = st2; i >= 0; i--)
            if ((father[a][i] != -1) && (father[a][i] != father[b][i]))
            {
                res = max(res ,max(st[a][i] , st[b][i]));
                a = father[a][i];b = father[b][i];
            }
        return max(st[b][0] , max(res , st[a][0]));
    }
}

int main() {
    //freopen("z:/data6.in", "r", stdin);
    //freopen("z:/data9.out", "w", stdout);
    
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d",&p[i].x,&p[i].y);
    cnt=1;
    for (int i = 1; i <= m; i++){
        scanf("%d%d%d", &u,&v,&h);
        //if (h==484296208) printf("eid=%d\n",i );
        line[++cnt]=LINE(u,v,h);
        OutDegree[u].push_back(cnt);
        line[++cnt]=LINE(v,u,h);
        OutDegree[v].push_back(cnt);
    }
    G::work();
    /*
    for (int i = 1; i <= G::region_tot; i++)
        printf("%.8lf\n", G::S[i]);*/

    scanf("%d", &q);
    q<<=1;
    for (int i = 1; i <= q; i++){
        que[i].id=i;
        scanf("%lf%lf", &que[i].x,&que[i].y);
    }
    scanning_line::work();
    //printf("%d\n", G::inf_area);
    for (int i = 1; i <= q; i++){
        if (quepos[i]==G::inf_area) quepos[i]=-1;
        //printf("%d %d\n",i, quepos[i]);
    }

    for (int i = 2; i <= cnt; i+=2){
        //printf("%d\n%d\n", G::belong[i],G::belong[i^1]);
        if (G::belong[i]==G::inf_area||G::belong[i^1]==G::inf_area) {
            //printf("N\n");
            continue;
        }
        //printf("Y\n");

        MST::addedge(G::belong[i],G::belong[i^1],line[i].len);
    }
    MST::build();
    MST::dfs(G::inf_area==1?2:1,0,0,1);
    MST::init();
    for (int i = 1; i <= q; i+=2){
        if (quepos[i]==-1||quepos[i+1]==-1) {printf("-1\n");continue;}
        int fa=MST::gf(quepos[i]),fb=MST::gf(quepos[i+1]);
        //printf("%d %d\n", fa,fb);
        if (fa==fb) printf("%d\n",MST::lca(quepos[i],quepos[i+1])); else printf("-1\n");
    }
    //system("pause");
    return 0;
}