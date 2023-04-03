#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxl = 1000000 + 5;
const int T = 1000000 + 5;
int q;
ll xx;
int m,len;

char s[T];

int cf[1000010];
ll presum[1000010];
void addseg(int l,int r){
    //printf("addseg:%d %d\n",l,r);
    cf[l]++,cf[r+1]--;
}

void pre(){
    for(int i=1;i<=len;i++){
        cf[i]+=cf[i-1];
        //printf("len[%d]=%d\n",i,cf[i]);
    }
    for(int i=1;i<=len;i++)
        presum[i]=presum[i-1]+cf[i];
}

int Tree[2000010*4];

void modify(int rt,int l,int r,int pos,int val){
    Tree[rt]+=val;
    if(l==r)
        return;
    int mid=(l+r)>>1;
    if(pos<=mid)
        modify(rt<<1,l,mid,pos,val);
    else
        modify(rt<<1|1,mid+1,r,pos,val);
}
void _modify(int rt,int l,int r,int pos,int val){
    //printf("modify %d %d\n",pos,val);
    modify(rt,l,r,pos,val);
}
int query(int rt,int l,int r,int x){
    if(l==r)
        return l;
    int mid=(l+r)>>1;
    if(Tree[rt<<1]>=x)
        return query(rt<<1,l,mid,x);
    else
        return query(rt<<1|1,mid+1,r,x-Tree[rt<<1]);
}

int last,root,cnt;
int len1[2000010],spmn[2000010],a[2000010][26],fa[2000010];
void init()
{
    last = root = ++cnt;
}

void extend(int ch,int startpos)
{
    int p = last, np = last = ++cnt;
    len1[np] = len1[p] + 1;
    spmn[np] = startpos;
    while (p && !a[p][ch])
        a[p][ch] = np, p = fa[p];
    if (!p)
        fa[np] = root;
    else
    {
        int q = a[p][ch];
        if (len1[q] == len1[p] + 1)
            fa[np] = q;
        else
        {
            int nq = ++cnt;
            len1[nq] = len1[p] + 1;
            memcpy(a[nq], a[q], sizeof a[q]);
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while (p && a[p][ch] == q)
                a[p][ch] = nq, p = fa[p];
        }
    }
}
int dfn[2000010],ts,redfn[2000010];
#include<vector>
vector<pair<int,int> >ord[2000010],op[2000010];
vector<int>vec[2000010];
pair<int,int>ANS[1000010];
pair<long long,int> Q[1000010];

void dfs2(int x){
    for(auto v:vec[x]){
        dfs2(v);
        spmn[x]=min(spmn[x],spmn[v]);
    }
}

void dfs(int x){
    dfn[x]=++ts;
    redfn[ts]=x;
    for(int v:vec[x]){
        ord[x].push_back(make_pair(s[spmn[v]+len1[x]],v));
        //printf("dfs:%d %c %d %d %d\n",x,s[spmn[v]+len1[x]],v,spmn[v],len1[x]+1);
    }
    sort(ord[x].begin(),ord[x].end());
    for(auto tmp:ord[x]){
        int v=tmp.second;
        dfs(v);
        spmn[x]=min(spmn[x],spmn[v]);
    }
    if(len1[x]){
        addseg(len1[fa[x]]+1,len1[x]);
        op[len1[fa[x]]+1].push_back(make_pair(1,x));
        //printf("op:%d %d\n",len1[fa[x]]+1,x);
        op[len1[x]+1].push_back(make_pair(-1,x));
    }
}

int main(){
    int curit=0;
    scanf("%s", s);
    printf("%d\n", sizeof a);
    memset(spmn,0x3f3f3f3f,sizeof spmn);
    len = strlen(s);
    init();
    for(int i=len-1;i>=0;i--)
        extend(s[i]-'a',i);
    for(int i=1;i<=cnt;i++)
        vec[fa[i]].push_back(i);
    /*for(int i=1;i<=cnt;i++)
        for(int j=0;j<26;j++)
            if(a[i][j])
                printf("%d %c->%d\n",i,j+'a',a[i][j]);*/
    dfs2(root);
    dfs(root);
    pre();
    scanf("%d",&q);

    for(int i=1;i<=q;i++){
        scanf("%lld",&xx);
        Q[i]=make_pair(xx,i);
    }
    sort(Q+1,Q+1+q);

    for(int i=1;i<=q;i++){
        xx=Q[i].first;

        int l=1,r=len,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(presum[mid]>=xx)
                r=mid-1,ans=mid;
            else
                l=mid+1;
        }
        xx=xx-presum[ans-1];
        //printf("id=%d len=%d rest=%d\n",Q[i].second,ans,xx);
        while(ans>curit){
            curit++;
            for(auto tmp:op[curit]){
                if(tmp.first==1)
                    _modify(1,1,ts,dfn[tmp.second],1);
                else
                    _modify(1,1,ts,dfn[tmp.second],-1);
            }
        }
        int calc_len=ans;
        if(calc_len==0){
            ANS[Q[i].second]=make_pair(1,-1);
            continue;
        }
        int tmp=query(1,1,ts,xx);
        //printf("query:%d,%d\n",tmp,redfn[tmp]);
        ANS[Q[i].second]=make_pair(ans,spmn[redfn[tmp]]+1);
    }
    for(int i=1;i<=q;i++)
        printf("%d %d\n",ANS[i].second,ANS[i].second+ANS[i].first-1);
}