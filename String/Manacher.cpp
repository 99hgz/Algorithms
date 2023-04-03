#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

char S[500010],a[500010];
int n,f[500010],maxR,p,l[500010],ans;

int main() {
    scanf("%s",S);
    a[0]='@';
    for(int i=0;S[i];i++)
        a[++n]='#',a[++n]=S[i];
    a[++n]='#';
    a[n+1]='*';
    for(int i=1;i<=n;i++){
        f[i]=(i<maxR)?min(f[2*p-i],maxR-i+1):1;
        while(i-f[i]>0&&i+f[i]<=n&&a[i-f[i]]==a[i+f[i]])f[i]++;
        if(i+f[i]-1>maxR) maxR=i+f[i]-1,p=i;
    }
   // system("pause");
    return 0;
}