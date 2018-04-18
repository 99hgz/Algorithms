#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;

double eps=1e-6;
struct Point{
    double x,y,r;
    Point ():x(0),y(0),r(0){};
    Point (double x,double y):x(x),y(y){};
    Point point(double a)  {
        return Point(x + cos(a) * r, y + sin(a) * r);  
    }
    bool operator == (const Point &t)const
    {
        return fabs(x-t.x)<eps && fabs(y-t.y)<eps;
    }
}p[10];
int n,e,v,xj,fa[10];
Point operator - (Point a,Point b){
    return Point(a.x-b.x,a.y-b.y);
}

int gf(int x){
    return fa[x]==0?x:fa[x]=gf(fa[x]);
}

void merge(int a,int b){
    int fx=gf(a),fy=gf(b);
    if(fx!=fy)
        fa[fx]=fy;
}

int dcmp(double x)  
{  
    if(fabs(x) < eps) return 0;  
    else  
        return x < 0 ? -1 : 1;  
}  

double angle(Point v)  
{  
    return atan2(v.y,v.x);  
}  
double sqr(double x){return x*x;}
vector<Point> operator &(Point C1,Point C2){
    if(C2.x<C1.x) swap(C1,C2);
    double d = sqrt(sqr(C1.x-C2.x) + sqr(C1.y-C2.y));  
    if(dcmp(C1.r + C2.r - d) < 0) return vector<Point>();
    if(dcmp(fabs(C1.r - C2.r) - d) > 0) return vector<Point>(); 
    double a = angle(C2 - C1); 
    double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
    Point p1 = C1.point(a-da),p2 = C1.point(a+da);  
    return vector<Point>{p1,p2};
}  

bool cmp(Point a,Point b){
    if(fabs(a.x-b.x)<eps)return a.y<b.y;
    return a.x<b.x;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].r);
    if(n==1)
        printf("%d\n", 2);
    else{
        vector<Point>all;
        for(int i=1;i<=n;i++){
            vector<Point>pat;
            for(int j=1;j<=n;j++){
                if(i==j)continue;
                vector<Point>tmp=p[i]&p[j];
                if(tmp.size()>0)
                    merge(i,j);
                for(auto v:tmp)
                    pat.push_back(v),all.push_back(v);
                //printf("%d %d %d\n", i,j,tmp.size());
            }
            sort(pat.begin(),pat.end(),cmp);

            vector<Point>::iterator it;
            it = unique(pat.begin(),pat.end());  
            pat.resize(distance(pat.begin(),it)); 
            e+=pat.size();
            //printf("%d\n", e);
        }
        sort(all.begin(),all.end(),cmp);
        
        vector<Point>::iterator it;
        it = unique(all.begin(), all.end());  
        all.resize(distance(all.begin(),it)); 
        //for(auto k:all)
        //    printf("%.4lf %.4lf\n",k.x,k.y); 
        v=all.size();
        for(int i=1;i<=n;i++)
            xj+=(gf(i)==i);
        //printf("%d %d %d\n", e,v,xj);
        printf("%d\n",e-v+xj+1);
    }

    //system("pause");
    return 0;
}