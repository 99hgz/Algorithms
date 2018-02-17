#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
double x[10],y[10],r[10];
int n,ans;
int app[100];
bool isin(double px,double py,int id){
    double dis=(px-x[id])*(px-x[id])+(py-y[id])*(py-y[id]);
    if (abs(dis-r[id]*r[id])<=1e-6) return true;
    if (dis<r[id]*r[id]) return true;else return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%lf%lf%lf", &x[i],&y[i],&r[i]);
    for(int tx=-1001;tx<=1001;tx++)
        for (int ty = -1001; ty <= 1001; ty++) {
            if ((tx%100)==0||(ty%100)==0)continue;
            double nx=(double)tx/(double)100;
            double ny=(double)ty/(double)100;
            int sta=(isin(nx,ny,1))*4+(isin(nx,ny,2))*2+(isin(nx,ny,3));
            if (!app[sta])app[sta]=1,ans++;
        }
    printf("%d\n", ans);
    system("pause");
    return 0;
}