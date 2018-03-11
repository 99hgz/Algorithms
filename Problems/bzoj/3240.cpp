#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll mod=1000000007,phi;
ll a,b,c,d,n,m;
char _n[1000010],_m[1000010];
struct MATRIX
{
    int n, m;
    ll mt[2][2];
} A,B,E;
MATRIX operator*(MATRIX a, MATRIX b)
{
    MATRIX c;
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < b.m; j++)
        {
            c.mt[i][j] = 0;
            for (int k = 0; k < a.m; k++)
            {
                c.mt[i][j] += a.mt[i][k] * b.mt[k][j];
                c.mt[i][j] %= mod;
            }
        }
    c.n = a.n;
    c.m = b.m;
    return c;
}

MATRIX power(MATRIX a, ll b)
{
    //printf("%lld\n", b);
    MATRIX ans = E;
    while (b > 0)
    {
        if (b & 1)
            ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}

int main() {
    //printf("start\n" );
    freopen("Z:/a.txt", "r", stdin);
    //freopen("F:\Downloads\testdata (4).in.out", "w", stdout);
    
    scanf("%s", _n);
    //printf("start\n" );
    //printf("%s\n", _n);
    scanf("%s", _m);
    scanf("%lld%lld%lld%lld",&a,&b,&c,&d );
    if (a==1&&c==1) phi=1000000007; else phi=1000000006;
    int len=strlen(_n);
    for (int i = 0; i < len; i++) 
        n=(n*10+_n[i]-'0')%phi;
    len=strlen(_m);
    for (int i = 0; i < len; i++) 
        m=(m*10+_m[i]-'0')%phi;
    n=(n-1+phi)%phi;
    m=(m-1+phi)%phi;
    E.n=E.m=2;
    E.mt[0][0]=E.mt[1][1]=1;
    A.n=A.m=2;
    A.mt[0][0]=a,A.mt[1][0]=b,A.mt[1][1]=1;
    A=power(A,m);
    B.n=B.m=2;
    B.mt[0][0]=c,B.mt[1][0]=d,B.mt[1][1]=1;
    B=A*B;
    B=power(B,n);
    B=B*A;
    printf("%lld\n", (B.mt[0][0]+B.mt[1][0])%mod);
    system("pause");
    return 0;
}