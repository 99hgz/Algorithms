#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>
using namespace std;
typedef long long ll;
ll u[2000000],cnt;
ll len[1000100],ANS,base[20];
bool vis[100010];
int q[1000100];

struct Node{
    ll val;
    int id;
}s[1000010];
int T,pre[1000010];

bool cmp(Node a,Node b){
    return a.val<b.val;
}

int count(ll x){
    int res=0;
    while(x){
        res++;
        x/=10;
    }
    return res;
}

int main() {
    base[0]=1;
    for(ll i=1;i<=9;i++)len[i]=1;
    for(ll i=10;i<=999999;i++)len[i]=len[i/10]+1;
    for(int i=1;i<=15;i++)
        base[i]=base[i-1]*10;
    //freopen("Z:/data.in", "r", stdin);
    //freopen("Z:/data.out", "w", stdout);

    /*double dur;
    clock_t start,end;
    start = clock();*/

    scanf("%d", &T);
    for (int i = 1; i <= T; i++){
        scanf("%lld%lld", &s[i].val,&s[i+T].val);
        s[i].id=-i,s[i+T].id=i;
        s[i].val--;
    }
    sort(s+1,s+1+T*2,cmp);

    for (ll i = 1; i <= 317; i++){
        for(ll j=1;j<=100000/(i*i);j++){
            ll num=i*i*j;
            if(num>=100000) break;
            //if(vis[num]) continue;
            //vis[num]=true;
            //ANS++;
            //printf("%lld\n", num);
            for(ll k=i+1;k<=100000;k++){
                ll nnum=num,nlen=len[num];
                ll ans=num;
                /*check*/
                ll _=num/i/i*k*k;
                int __=len[num]+count(num/i*k)+count(_);
                if(__>15)break;
                //if(_>=100000) break;
                for(ll c=2;c<=15;c++){
                    if(nnum%i!=0) break;
                    nnum=nnum/i*k;
                    //if(nnum>=100000)break;
                    nlen+=count(nnum);
                    if(nlen>15) break;
                    ans=ans*base[count(nnum)]+nnum;
                    if(c>=3){
                        ANS++;
                        u[++cnt]=ans;
                        //cout<<ans<<endl;
                        //int p=lower_bound(s+1,s+1+T*2,(Node){ans,0},cmp)-s;
                        //pre[p]++;
                    }
                }
            }
        }
    }
    sort(u+1,u+1+cnt);
    int num1=unique(u+1,u+1+cnt)-u-1;
    int head=1;
    for(int i=1;i<=cnt;i++){
        while(head<=2*T&&u[i]>s[head].val) head++;
        pre[head]++;
    }


    //printf("%d\n", ANS);
    int pp=0;
    for(int i=1;i<=2*T;i++){
        pp+=pre[i];
        q[abs(s[i].id)]+=((s[i].id<0)?-1:1)*pp;
    }
    for(int i=1;i<=T;i++)
        printf("Case #%d: %d\n", i,q[i]);
    /*end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));*/

    //system("pause");
    return 0;
}