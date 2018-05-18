#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

struct P{
    long double x,y;
}point[100010];
int n;
long double S;

long double calc(P a,P b){
    return a.x*b.y-a.y*b.x;
}

P operator -(P a,P b){
    return (P){a.x-b.x,a.y-b.y};
} 

int gcd(int x,int y){
    return y==0?x:gcd(y,x%y);
}

long double base[100010],N,ss[100010];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%Lf%Lf",&point[i].x,&point[i].y);
    point[n]=point[0];
    for(int i=1;i<n-1;i++)
        S+=calc(point[i]-point[0],point[i+1]-point[0]);
    printf("%.8lf\n", (double)S);
    base[0]=1;
    for(int i=1;i<=n;i++)
        base[i]=base[i-1]*0.5;

    int lim=min(100,n);
    long double cn2=(long double)n*(n-1)/2;
    long double fm=(1.0-1.0*(cn2+n+1)*base[n]);
    for(int i=3;i<=lim;i++){
        long double g=(base[i]-base[n])/fm;
        for(int st=0;st<n;st++){
            ss[st]+=calc(point[(st+i-2)%n]-point[st],point[(st+i-1)%n]-point[st]);
            S-=g*ss[st];
        }
    }
    S/=2.0;

    for(int i=2;i<=lim;i++){
        long double g=(base[i]-base[n])/fm;
        for(int st=0;st<n;st++){
            int tmp=gcd((int)fabs(point[st].x-point[(st+i-1)%n].x),(int)fabs(point[st].y-point[(st+i-1)%n].y));
            N+=g*(long double)tmp;
        }
        printf("%d %.8lf\n", i,N);
    }

    printf("%Lf\n", S-N/2.0+1.0);
    //system("pause");
    return 0;
}