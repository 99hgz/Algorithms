#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;
typedef pair<int,int> pr;
typedef bitset<101> bt;
typedef vector<int> RES;
#define fi first
#define se second

int q[110],n,m,x[110],y[110],d;
bt to[110];

int getfirst1(bt &a){
    for(int i=1;i<=n;i++)
        if(a[i])
            return i;
}

RES calc(bt a){
    //return (a.count()==1)?1:(a.count()/2);
    //if(a.count()<=2) return (a.count()+1)/2;
    int tot=0;
    q[++tot]=getfirst1(a);
    int all=a.count();
    for(int i=1;i<=all-1;i++){
        bt o=to[q[i]]&a;
        int t1=getfirst1(o);
        if(t1!=q[i-1])
            q[++tot]=t1;
        else{
            o[t1]=0;
            int t2=getfirst1(o);
            q[++tot]=t2;
        }
    }
    RES res;
    for(int i=1;i<=tot/2;i++)
        res.push_back(q[i*2-1]);
    return res;
    /*q[tot+1]=q[1];
    q[tot+2]=q[2];
    q[tot+3]=q[3];
    for(int i=1;i<=3;i++){
        pr ans=make_pair(0,1);
        for(int j=i+tot-3;j>=i;j--)
            ans=make_pair(max(ans.fi,ans.se),ans.fi+1);
        res=max(res,ans.se);
    }
    return res;*/
}

RES none;
RES dfs(bt a){
    if(a.count()==0) return none;
    int id=0,mx=0;
    for(int i=1;i<=n;i++)
        if(a[i]==1){
            bt o=to[i]&a;
            int tmp=o.count();
            if(tmp<=1){
                a[i]=0;
                if(tmp==1)
                    a[getfirst1(o)]=0;
                RES r=dfs(a);
                r.push_back(i);
                return r;
            }
            if(tmp>mx)
                mx=tmp,id=i;
        }
    if(mx==2)
        return calc(a);
    bt a2=a;
    bt o=to[id]&a;
    for(int i=1;i<=n;i++)
        if(o.test(i))
            a2[i]=0;
    a[id]=a2[id]=0;
    RES f1=dfs(a2);
    f1.push_back(id);
    RES f2=dfs(a);
    return (f1.size()>f2.size())?f1:f2;
}

int main() {
    scanf("%d%d", &n,&d);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &x[i],&y[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j)
                to[i][j]=((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])>d*d);
    bt init;
    for(int i=1;i<=n;i++)
        init[i]=1;
    RES ans=dfs(init);
    printf("%d\n",(int)ans.size());
    for(int i=0;i<ans.size();i++)
        printf("%d ",ans[i]);
    return 0;
}