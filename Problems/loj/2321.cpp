#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int S,T,n,m,a[2010][2010],color,tot1;
int fl[2010];
struct Node{
    int x,y,fx;
}st[10000];
int calc(int x,int y,int fx){
    fx=(fx-1)%4;
    fx++;
    int res=((x*(m+2)+y)*4+fx-1)+3;
    st[res]=(Node){x,y,fx};
    return res;
}
int lowbit(int x){
    return x&(-x);
}
namespace flow{
    int tot=1, Head[100010], Next[100010], From[100010], To[100010], Cost[100010], Val[100010];
    int FLOW, Q[50100], pre[100010], dis[100010];
    bool inq[100010];

    void _addedge(int u, int v, int w, int c)
    {
        tot++;
        Next[tot] = Head[u];
        Head[u] = tot;
        From[tot] = u;
        To[tot] = v;
        Cost[tot] = c;
        Val[tot] = w;
    }

    void addedge(int u, int v, int w, int c)
    {
        if (color) swap(u,v);
        //printf("%d->%d (%d,%d,%d)->(%d,%d,%d)  w=%d  c=%d\n",u,v,st[u].x,st[u].y,st[u].fx,
        //st[v].x,st[v].y,st[v].fx,w,c );
        //printf("%d -> %d [ label = \" W(%d,%d) \" ];\n",u,v,w,c );
        _addedge(u, v, w, c);
        _addedge(v, u, 0, -c);
    }

    int calc()
    {
        int res = 0, flow = 0x3f3f3f3f;
        for (int it = T; pre[it]; it = From[pre[it]])
            flow = min(flow, Val[pre[it]]);

        FLOW += flow;
        //printf("nowflow=%d\n",FLOW );
        for (int it = T; pre[it]; it = From[pre[it]])
        {
            Val[pre[it]] -= flow;
            Val[pre[it] ^ 1] += flow;
            res += flow * Cost[pre[it]];
        }
        return res;
    }

    bool spfa()
    {
        int h = 0, t = 1;
        Q[1] = S;
        memset(pre, 0, sizeof pre);
        memset(inq, 0, sizeof inq);
        memset(dis, 0x3f3f3f3f, sizeof dis);
        inq[S] = true;
        dis[S] = 0;
        while (t != h)
        {
            h++;
            if (h == 20000)
                h = 1;
            int u = Q[h];
            //printf("spfa:%d %d\n",u,dis[u] );
            inq[u] = false;
            for (int it = Head[u]; it; it = Next[it])
            {
                int v = To[it];
                if (Val[it] > 0 && dis[v] > dis[u] + Cost[it])
                {
                    dis[v] = Cost[it] + dis[u];
                    pre[v] = it;
                    if (!inq[v])
                    {
                        inq[v] = true;
                        t++;
                        if (t == 20000)
                            t = 1;
                        Q[t] = v;
                    }
                }
            }
        }
        return pre[T] != 0;
    }

    int mcf()
    {
        int res = 0;
        while (spfa())
            res += calc();
        return res;
    }
}
using namespace flow;
int main() {
    fl[1]=1;
    fl[2]=2;
    fl[4]=3;
    fl[8]=4;
    st[2]=(Node){-1,-1,-1};
    S=1,T=2;
    scanf("%d%d", &n,&m);
    for (int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++){
            color=(i+j)&1;
            int allf=0;
            if (color==0){
                addedge(calc(i,j,1),calc(i-1,j,3),1,0),
                addedge(calc(i,j,2),calc(i,j+1,4),1,0),
                addedge(calc(i,j,3),calc(i+1,j,1),1,0),
                addedge(calc(i,j,4),calc(i,j-1,2),1,0);
            }
            if (a[i][j]&1)
                allf++,addedge(color?T:S,calc(i,j,1),1,0);
            if (a[i][j]&2)
                allf++,addedge(color?T:S,calc(i,j,2),1,0);
            if (a[i][j]&4)
                allf++,addedge(color?T:S,calc(i,j,3),1,0);
            if (a[i][j]&8)
                allf++,addedge(color?T:S,calc(i,j,4),1,0);
            tot1+=allf;
            if (allf==1){
                int fx=fl[a[i][j]];
                addedge(calc(i,j,fx),calc(i,j,fx+1),1,1);
                addedge(calc(i,j,fx),calc(i,j,fx+2),1,2);
                addedge(calc(i,j,fx),calc(i,j,fx+3),1,1);
            }else if (allf==2){
                int tmp=lowbit(a[i][j]);
                a[i][j]-=tmp;
                int fx1=fl[tmp],fx2=fl[a[i][j]];
                if (fx2-fx1==2) continue;
                addedge(calc(i,j,fx1),calc(i,j,fx1+2),1,1);
                addedge(calc(i,j,fx2),calc(i,j,fx2+2),1,1);
            }else if (allf==3){
                int tmp=15-a[i][j];
                int fx=fl[lowbit(tmp)];
                addedge(calc(i,j,fx+1),calc(i,j,fx),1,1);
                addedge(calc(i,j,fx+3),calc(i,j,fx),1,1);
                addedge(calc(i,j,fx+2),calc(i,j,fx),1,2);
            }
        }
    int res=mcf();
    if (FLOW*2==tot1)
        printf("%d\n", res);
    else 
        printf("%d\n", -1);
    //printf("%d %d-%d\n", res,FLOW,tot1);
    system("pause");
    return 0;
}