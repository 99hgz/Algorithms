#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
char a[100010];
int f[100010],ans01,ans,ans1;
bool chk(int pos,int x){
    if(pos<=0)return 0;
    if(f[pos]==1)return 0;
    if(a[pos]==x+'0')return 1;
    return 0;
}
int main() {
    scanf("%s",a+1);
    int len=strlen(a+1);
    for(int i=1;i<=len;i++){
        if(a[i]=='0'){
            if(chk(i-1,1))
                f[i]=1,f[i-1]=1,ans01++;
        }else{
            if(chk(i-1,0))
                f[i]=1,f[i-1]=1,ans01++;
        }
    }
    for(int i=1;i<=len;i++)
        if(a[i]=='1' && f[i]==0)
            ans1++;
    
    ans=max(ans01,ans1);
    for(int i=1;i<=len;i++)
        if(a[i]=='0' && f[i]==0)
            ans=-1;
    
    printf("%d\n", ans);
    system("pause");
    return 0;
}