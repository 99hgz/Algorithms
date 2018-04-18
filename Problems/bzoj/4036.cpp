#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
double eps=1e-8;
int n,lim;
double g[1148576],f[1148576];

int main() {
    scanf("%d", &n);
    lim=(1<<n)-1;
    for(int i=0;i<=lim;i++){
        scanf("%lf",&f[i]);
        if(fabs(f[i]-1.0)<eps){
            if(i==lim)
                printf("1.00000000\n");
            else
                printf("INF\n");
            return 0;
        }
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<=lim;j++)
            if((j>>i)&1)
                f[j]+=f[j^(1<<i)];
    for(int i=0;i<=lim;i++)
        g[i]=(fabs(f[i]-1.0)<eps)?0:(-1.0/(1.0-f[i]));
    for(int i=0;i<n;i++)
        for(int j=0;j<=lim;j++)
            if((j>>i)&1)
                g[j]-=g[j^(1<<i)];
    if(g[lim]<eps)printf("INF\n" );
    else
        printf("%.8lf\n", g[lim]);
    system("pause");
    return 0;
}