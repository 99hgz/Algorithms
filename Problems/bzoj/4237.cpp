#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

struct P{
    int x,y;
}a[200010],s1[200010],s2[200010];
int n;
ll ans;
bool cmp(P a,P b){
    return a.y<b.y;
}

bool cmp2(P a,P b){
    return a.x<b.x;
}

void solve(int l,int r){
    if (r==l) return;
    int mid=(l+r)>>1;
    solve(l,mid);
    solve(mid+1,r);
    sort(a+l,a+1+mid,cmp2);
    sort(a+mid+1,a+r+1,cmp2);
    int top1=0,top2=0;
    int last=l;
    for (int i = mid+1; i <= r; i++){
        while(top2&&s2[top2].y>a[i].y)
            top2--;
        s2[++top2]=a[i];

        for (int i = last; i <= mid; i++){
            if (s2[top2].x<a[i].x)break;
            while(top1&&s1[top1].y<a[i].y)
                top1--;
            s1[++top1]=a[i];
            last++;
        }

        int L=lower_bound(s1+1,s1+1+top1,(P){s2[top2-1].x,0},cmp2)-s1;
        int R=lower_bound(s1+1,s1+1+top1,(P){s2[top2].x,0},cmp2)-s1-1;
        //printf("%d %d\n", L,R);
        ans+=(ll)R-L+1;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d%d", &a[i].x,&a[i].y);
        //a[i].x++,a[i].y++;
    }
    sort(a+1,a+1+n,cmp);
    solve(1,n);
    printf("%lld\n", ans);
    system("pause");
    return 0;
}