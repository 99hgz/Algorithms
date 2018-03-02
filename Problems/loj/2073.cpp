#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

ll pre[2][100010],suc[2][100010],base[100010];
ll p=100000009;
int n,len[2][100010],len2[2][100010],res;
char st[2][100010];

void preHash(int id){
    for (int i = 1; i <= n; i++)
        pre[id][i]=(pre[id][i-1]*31+st[id][i]-'A'+1)%p;
    for (int i = n; i >= 1; i--) 
        suc[id][i]=(suc[id][i+1]*31+st[id][i]-'A'+1)%p;
}

ll GetHash(int id,int op,int l,int r){
    if (op==0)
        return (((pre[id][r]-pre[id][l-1]*base[r-l+1])%p)+p)%p;
    else
        return (((suc[id][l]-suc[id][r+1]*base[r-l+1])%p)+p)%p;
}

bool check(int id1,int l1,int r1,int id2,int l2,int r2){
    ll a=GetHash(id1,0,l1,r1);
    ll b=GetHash(id2,1,l2,r2);
    //printf("check:%d %d %d %d %d %d=%lld %lld\n",id1,l1,r1,id2,l2,r2, a,b);
    return a==b;
}

int main() {
    scanf("%d", &n);
    scanf("%s", st[0]+1);
    scanf("%s", st[1]+1);
    base[0]=1;
    for (int i = 1; i <= n; i++)
        base[i]=base[i-1]*31%p;
    preHash(0),preHash(1);
    for (int j = 0; j <= 1; j++){
        //printf("--------------------\n" );
        for (int i = 1; i <= n; i++){
            int l=1,r=min(i,n-i+1),ans=1;
            while(l<=r){
                int mid=(l+r)>>1;
                if (check(j,i-mid+1,i,j,i,mid+i-1))
                    ans=mid,l=mid+1;
                else 
                    r=mid-1;
            }
            len[j][i]=ans;
            res=max(res,ans*2-1);
            //printf("%d\n", ans);
        }
        //printf("------\n");
        for (int i = 1; i < n; i++){
            int l=0,r=min(i,n-i),ans=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if (check(j,i-mid+1,i,j,i+1,mid+i))
                    ans=mid,l=mid+1;
                else 
                    r=mid-1;
            }
            len2[j][i]=ans;
            res=max(res,ans*2);
            //printf("%d\n", ans);
        }
    }

    for (int i = 1; i <= n; i++){
        int L=i-len[1][i]+1,R=i+len[1][i]-1;
        int l=0,r=min(L,n-R),ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if (check(0,L-mid+1,L,1,R+1,R+mid))
                ans=mid,l=mid+1;
            else 
                r=mid-1;
        }
        res=max(res,ans*2+len[1][i]*2-1);
    }
    for (int i = 1; i < n; i++){
        if (len2[1][i]==0) continue;
        int L=i-len2[1][i]+1,R=i+len2[1][i];
        int l=0,r=min(L,n-R),ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if (check(0,L-mid+1,L,1,R+1,R+mid))
                ans=mid,l=mid+1;
            else 
                r=mid-1;
        }
        res=max(res,ans*2+len2[1][i]*2);
    }
    
    for (int i = 1; i <= n; i++){
        int L=i-len[0][i]+1,R=i+len[0][i]-1;
        int l=0,r=min(L-1,n-R+1),ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if (check(0,L-mid,L-1,1,R,R+mid-1))
                ans=mid,l=mid+1;
            else 
                r=mid-1;
        }
        res=max(res,ans*2+len[0][i]*2-1);
    }

    for (int i = 1; i < n; i++){
        if (len2[0][i]==0) continue;
        int L=i-len2[0][i]+1,R=i+len2[0][i];
        int l=0,r=min(L-1,n-R+1),ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if (check(0,L-mid,L-1,1,R,R+mid-1))
                ans=mid,l=mid+1;
            else 
                r=mid-1;
        }
        res=max(res,ans*2+len2[0][i]*2);
    }
    printf("%d\n", res);
    system("pause");
    return 0;
}