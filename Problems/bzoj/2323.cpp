#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct MT{
    int n,m;
    ll mt[3][3];
    void print(){
        printf("print:%d*%d\n",n,m );
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++)
                printf("%lld ",mt[i][j] );
            printf("\n" );
        }
    }
}f[1010],S,o,base[1010];

int n;
char st[1010];
int num[1010];
ll p=1000000007;

MT operator *(MT a,MT b){
    MT c;
    c.n=c.m=2;
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= 2; j++){
            ll res=0;
            for (int k = 1; k <= 2; k++)
                res=(res+a.mt[i][k]*b.mt[k][j])%p;
            c.mt[i][j]=res;
        }
    return c;
}

MT operator + (MT a,MT b){
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= 2; j++)
            a.mt[i][j]=(a.mt[i][j]+b.mt[i][j])%p;
    return a;
}

MT power(MT a,int b){
    MT tmp;
    tmp.n=tmp.m=2;
    tmp.mt[1][1]=tmp.mt[2][2]=1;
    tmp.mt[1][2]=tmp.mt[2][1]=0;
    while(b){
        if (b&1) tmp=tmp*a;
        a=a*a;
        b>>=1;
    }
    return tmp;
}   

void init(){
    S.n=S.m=2;
    S.mt[1][2]=S.mt[2][1]=S.mt[2][2]=1;

    f[0].n=f[0].m=2;
    f[0].mt[1][1]=2;
    f[0].mt[1][2]=f[0].mt[2][1]=-1;
    f[0].mt[2][2]=1;

    o.n=o.m=2;
    memset(o.mt,0,sizeof o.mt);

    base[0]=S;
    for (int i = 1; i <= 1000; i++)
        base[i]=power(base[i-1],10);
}

void solve(){
    for (int i = 1; i <= n; i++){
        MT tmp;
        tmp.n=tmp.m=2;
        tmp.mt[1][1]=tmp.mt[2][2]=1;
        tmp.mt[1][2]=tmp.mt[2][1]=0;
        f[i]=o;
        for (int j = i-1; j>=0; j--) {
            tmp=tmp*power(base[i-j-1],num[j+1]);
            f[i]=f[i]+f[j]*tmp;
        }
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s", st+1);
    for (int i = 1; i <= n; i++)
        num[i]=st[i]-'0';
    init();
    solve();
    //f[n].print();
    printf("%lld\n", (f[n].mt[2][2]+p)%p);
    system("pause");
    return 0;
}