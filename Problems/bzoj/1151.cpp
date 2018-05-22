#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int fail[1000010];
ll ans;
char s1[1000010],s2[1000010];

void init(){
    int len=strlen(s1+1);
    fail[1]=0;
    for(int i=2;i<=len;i++){
        int j=fail[i-1];
        while(j&&s1[j+1]!=s1[i])j=fail[j];
        if(s1[j+1]==s1[i])fail[i]=j+1;
        else fail[i]=0;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", s1+1);
    init();
    int len=strlen(s1+1);
    int cur=0;
    for(int i=1;i<=len;i++){
        int tmp=0;
        int p=fail[i];
        while(fail[p]) p=fail[p];
        fail[i]=p;
        if(p)
            tmp=i/(i-p)*(i-p);
        ans+=(p==0)?0:((tmp==i)?(tmp-(i-p)):tmp);
        //printf("%d %d\n",i, (tmp==i)?(tmp-(i-p)):tmp);
    }
    
    printf("%lld\n", ans);
    
    system("pause");
    return 0;
}