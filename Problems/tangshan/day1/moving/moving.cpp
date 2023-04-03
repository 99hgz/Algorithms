#include<iostream>
#include<cstdio>
#include<cstring>

#define N 100007
#define ll long long

using namespace std;
ll n,m,ans,cnt;
struct tree
{
    ll l,r,mx,sum;
}tr[N<<2];

inline ll read()
{
    ll x=0,f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}

void pushup(ll k)
{
    tr[k].sum=tr[k<<1].sum+tr[k<<1|1].sum;
    tr[k].mx=max(tr[k<<1].mx,tr[k<<1|1].mx);
}

void build(ll k,ll l,ll r)
{
    tr[k].l=l;tr[k].r=r;tr[k].sum=tr[k].mx=0;
    if(l==r)
    {
        tr[k].sum=read();
        tr[k].mx=tr[k].sum;
        return;
    }
    ll mid=l+r>>1;
    build(k<<1,l,mid);build(k<<1|1,mid+1,r);
    pushup(k);
}

void changemod(ll k,ll l,ll r,ll mod)
{
    if(l>r) return;
    if(tr[k].mx<mod) return;
    if(tr[k].l==tr[k].r)
    {
        tr[k].mx%=mod;
        tr[k].sum=tr[k].mx;
        return;
    }
    ll mid=tr[k].l+tr[k].r>>1;
    if(r<=mid) changemod(k<<1,l,r,mod);
    else if(l>mid) changemod(k<<1|1,l,r,mod);
    else changemod(k<<1,l,mid,mod),changemod(k<<1|1,mid+1,r,mod);
    pushup(k);
}

void change(ll k,ll pos,ll x)
{
    if(tr[k].l==tr[k].r && tr[k].l==pos)
    {
        tr[k].sum=tr[k].mx=x;
        return;
    }
    ll mid=tr[k].l+tr[k].r>>1;
    if(pos<=mid) change(k<<1,pos,x);
    if(pos>mid)  change(k<<1|1,pos,x);
    pushup(k);
}

ll query(ll k,ll l,ll r)
{
    if(l>r) return 0;
    if(tr[k].l==l && tr[k].r==r)
    return tr[k].sum;
    ll mid=tr[k].l+tr[k].r>>1;
    if(r<=mid) return query(k<<1,l,r);
    else if(l>mid) return query(k<<1|1,l,r);
    else return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
}

int main()
{
    n=read();m=read();
    build(1,1,n);ll opt,x,y,z;
    for(ll i=1;i<=m;i++)
    {
        opt=read();
        if(opt==2)
        {
            x=read();y=read();
            printf("%lld\n",query(1,x,y));
        }
        if(opt==1)
        {
            x=read();y=read();z=read();
            changemod(1,x,y,z);
        }
        
    }
    //system("pause");
    return 0;
}