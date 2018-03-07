#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
const int N=300010;
const int M=1200010;
#define pi acos(-1)

struct complex{
    double x, y;
    complex(double a=0, double b=0):x(a), y(b){}
};
complex operator +(complex a, complex b) {return complex(a.x+b.x, a.y+b.y);}
complex operator -(complex a, complex b) {return complex(a.x-b.x, a.y-b.y);}
complex operator *(complex a, complex b) {return complex(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);}
typedef complex E;

int r[M],n1;
vector<int>ansv;
E A[M],B[M],ans[M],C[M],D[M];
char st2[M],st1[M];
int n,l;
void fft(E *u,int v){
    for (int i = 0; i < n; i++) 
        if (r[i]>i)
            swap(u[r[i]],u[i]);
    for(int i=1;i<n;i<<=1){
        E wn(cos(pi/i),v*sin(pi/i));
        for(int j=0;j<n;j+=(i<<1)){
            E w(1,0);
            for(int k=0;k<i;k++,w=w*wn){
                E x=u[j+k],y=w*u[i+j+k];
                u[j+k]=x+y;
                u[i+j+k]=x-y;
            }
        }
    }
    if (v==-1)
        for (int i = 0; i < n; i++) 
            u[i]=u[i]*(1.0/(double)n);
}

int main() {
    
    scanf("%d%d", &n,&n1);
    scanf("%s", st1);
    scanf("%s", st2);
    if(n<n1) swap(n,n1),swap(st1,st2);


    for (int i = 0; i < n; i++) 
        A[i]=(st1[i]=='*'?0:st1[i]-'a'+1);
    for (int i = 0; i < n1; i++) 
        B[n1-i-1]=(st2[i]=='*'?0:st2[i]-'a'+1);
    int n3=n;

    int m=2*n;
    for(n=1;n<=m;n<<=1)
        l++;
    
    for (int i = 0; i < n; i++)
        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));

    for (int i = 0; i < n; i++) {
        C[i]=A[i]*A[i]*A[i];
        D[i]=B[i];
    }
    fft(C,1),fft(D,1);
    for (int i = 0; i < n; i++) 
        ans[i]=ans[i]+C[i]*D[i];

    for (int i = 0; i < n; i++) {
        C[i]=2*A[i]*A[i];
        D[i]=B[i]*B[i];
    }
    fft(C,1),fft(D,1);
    for (int i = 0; i < n; i++) 
        ans[i]=ans[i]-C[i]*D[i];

    for (int i = 0; i < n; i++) {
        C[i]=A[i];
        D[i]=B[i]*B[i]*B[i];
    }
    fft(C,1),fft(D,1);
    for (int i = 0; i < n; i++) 
        ans[i]=ans[i]+C[i]*D[i];
    fft(ans,-1);
    

    
    for (int i = n1-1; i <= n3-1; i++) {
        //printf("%.4lf\n", ans[i].x);
        if (fabs(ans[i].x)<0.5)
            ansv.push_back(i-n1+1);
    }
    
    printf("%d\n", ansv.size());
    for (int i = 0; i<ansv.size(); i++)
        printf("%d ", ansv[i]+1);
    system("pause");
    return 0;
}