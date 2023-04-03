#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int L,T,init[60],skt[10],ans[51],nans[51],mid;

bool dfs(int pos,int pre){
    if(pre>mid||nans[0]>ans[0])
        return 0;
    if((pos+T-1)>L){
        for(int i=pos;i<=L;i++)
            pre+=init[i];
        if(pre>mid)
            return 0;
        if(nans[0]==ans[0]){
            bool flag=true;
            for(int i=1;i<=nans[0];i++)
                if(nans[i]<ans[i]){
                    flag=false;
                    break;
                }
            if(flag)
                memcpy(ans,nans,sizeof ans);
        }else
            memcpy(ans,nans,sizeof ans);
        return 1;
    }
    bool res=dfs(pos+1,pre+init[pos]);
    for(int i=1;i<=T;i++)
        init[pos+i-1]^=skt[i];
    nans[0]++;
    nans[nans[0]]=pos;
    res|=dfs(pos+1,pre+init[pos]);
    for(int i=1;i<=T;i++)
        init[pos+i-1]^=skt[i];
    nans[0]--;
    return res;
}

int main() {
    scanf("%d%d",&L,&T);
    for(int i=1;i<=L;i++)
        scanf("%1d",&init[i]);
    for(int i=1;i<=T;i++)
        scanf("%1d",&skt[i]);
    ans[0]=0x3f3f3f3f;
    for(mid=0;mid<=L;mid++)
        if(dfs(1,0))
            break;
    printf("%d\n",ans[0]);
    for(int i=1;i<=ans[0];i++)
        printf("%d\n", ans[i]);
    system("pause");
    return 0;
}