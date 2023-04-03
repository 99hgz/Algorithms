#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

char st[100010];
ll y[100010];
ll n;
ll MOD=1e9+7;
ll mt(ll a){
    return ((a%MOD)+MOD)%MOD;
}

ll pow(ll a,ll b){
    ll res=1;
    while(b){
        if (b&1) res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

struct Polynomial{
    ll a[210];
    Polynomial(ll x=0){
        memset(a,0,sizeof a);
        a[0]=x;
    }
    ll& operator[](ll x){
        return a[x];
    }
    Polynomial& operator *(ll x){
        for(ll i=0;i<=n*2;i++)
            a[i]=a[i]*x%MOD;
        return *this;
    }
    Polynomial& operator +(Polynomial b){
        for(ll i=0;i<=n*2;i++)
            a[i]=(a[i]+b[i])%MOD;
        return *this;
    }

}C_Poly;

Polynomial t(Polynomial a,ll b){
    for(ll i=n*2;i>=1;i--)
        a[i]=(a[i-1]+a[i]*b)%MOD;
    a[0]=a[0]*b%MOD;
    return a;
}

Polynomial operator *(Polynomial a,Polynomial b){
    Polynomial res;
    for(ll i=0;i<=n;i++)
        for(ll j=0;j<=n;j++)
            res.a[i+j]=(res[i+j]+a[i]*b[j])%MOD;
    return res;
}

Polynomial operator %(Polynomial a,Polynomial b){
    for(ll i=n;i>=0;i--){
        ll tmp=mt(-a[i+n]*pow(b[n],MOD-2));
        for(ll j=0;j<=n;j++)
            a[i+j]=mt(a[i+j]+tmp*b[j]);
    }
    return a;
}


struct MATRIX
{
    ll n, m;
    ll arr[110][110];
    void print(){
        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=n;j++)
                printf("%lld ",arr[i][j]);
            printf("\n");
        }
    }
}a,ans,b;

MATRIX operator*(MATRIX a, MATRIX b)
{
    MATRIX c;
    for (ll i = 1; i <= a.n; i++)
        for (ll j = 1; j <= b.m; j++)
        {
            c.arr[i][j] = 0;
            for (ll k = 1; k <= a.m; k++)
            {
                c.arr[i][j] += a.arr[i][k] * b.arr[k][j];
                c.arr[i][j] %= MOD;
            }
        }
    c.n = a.n;
    c.m = b.m;
    return c;
}

MATRIX operator+(MATRIX a,MATRIX b){
    for(ll i=1;i<=a.n;i++)
        for(ll j=1;j<=a.m;j++)
            a.arr[i][j]=(a.arr[i][j]+b.arr[i][j])%MOD;
    return a;
}

MATRIX operator*(MATRIX a,ll b){
    for(ll i=1;i<=a.n;i++)
        for(ll j=1;j<=a.m;j++)
            a.arr[i][j]=(a.arr[i][j]*b)%MOD;
    return a;
}

ll det(MATRIX a){
    ll d=1;
    //a.print();
    for(ll i=1;i<=n;i++){
        ll cur=i;
        for(ll j=i;j<=n;j++)
            if(a.arr[j][i]){
                cur=j;
                break;
            }
        if (i!=cur){
            d=mt(-d);
            for(ll j=1;j<=n;j++)
                swap(a.arr[i][j],a.arr[cur][j]);
        }
        d=mt(d*a.arr[i][i]);
        ll tmp=pow(a.arr[i][i],MOD-2);
        for(ll j=1;j<=n;j++)
            a.arr[i][j]=a.arr[i][j]*tmp%MOD;
        for(ll j=1;j<=n;j++)
            if(j!=i){
                ll tmp=a.arr[j][i];
                for(ll k=1;k<=n;k++)
                    a.arr[j][k]=mt(a.arr[j][k]-tmp*a.arr[i][k]);
            }
        //a.print();
    }
   
    return d;
}

int main() {
    scanf("%s", st+1);
    ll len=strlen(st+1);
    scanf("%lld", &n);
    //ll k;
    //scanf("%lld", &k);
    a.n=a.m=b.n=b.m=n;
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=n;j++)
            scanf("%lld",&a.arr[i][j]);
    memcpy(b.arr,a.arr,sizeof a.arr);
    for(ll i=0;i<=n;i++){
        if(i)
            for(ll j=1;j<=n;j++)
                a.arr[j][j]--;
        y[i]=det(a);
        //printf("%lld =%lld\n", i,y[i]);
    }
    for(ll i=0;i<=n;i++){
        Polynomial tmp(1);
        for(ll j=0;j<=n;j++)
            if(j!=i){
                tmp=t(tmp,mt(-j));
                tmp=tmp*pow(mt(i-j),MOD-2);
            }
        C_Poly=C_Poly+tmp*y[i];
    }

    Polynomial xs(1),x(0);
    x[1]=1;
    for(ll i=len;i>=1;i--){
        if(st[i]=='1')
            xs=xs*x%C_Poly;
        x=x*x%C_Poly;
    }
    /*while(k){
        if (k&1)
            xs=xs*x%C_Poly;
        x=x*x%C_Poly;
        k>>=1;
    }*/
    /*for(ll i=0;i<=n;i++)
    printf("xs[%lld]=%lld\n",i,C_Poly[i] );*/
    
    MATRIX c;
    memset(c.arr,0,sizeof c.arr);
    c.n=c.m=n;
    for(ll i=1;i<=n;i++)
        c.arr[i][i]=1;
    ans.n=ans.m=n;
    for(ll i=0;i<=n;i++){
        ans=ans+c*xs[i];
        c=c*b;
    }
    ans.print();
    system("pause");
    return 0;
}