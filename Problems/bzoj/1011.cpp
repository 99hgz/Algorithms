#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int n;
double A,m[100010],ans[100010],sum[100010];
int main() {
    scanf("%d%lf", &n,&A);
    for (int i = 1; i <= n; i++){ 
        scanf("%lf", &m[i]);
        sum[i]=sum[i-1]+m[i];
    }
    for (int i = 1; i <= n; i++) {
        double dis=A*i,mid;
        int lim=floor(dis);
        if (lim<=100){
            for (int j = 1; j <= lim; j++) {
                ans[i]+=m[i]*m[j]/(double)(i-j);
            }
        }else{
            int len=lim/100;
            for (int j = len; j <= len*100; j+=len) {
                mid=(2*i-2*j+len-1)*0.5;
                ans[i]+=(sum[j]-sum[j-len])*m[i]/mid;
            }
            for (int j = len*100+1; j <= lim; j++) {
                ans[i]+=m[i]*m[j]/(double)(i-j);
                
            }
        }
        printf("%.6lf\n", ans[i]);
    }
    system("pause");
    return 0;
}