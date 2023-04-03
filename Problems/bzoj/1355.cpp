#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,fail[1000010];
char s[1000100];

int main() {
    scanf("%d", &n);
    scanf("%s", s+1);
    
    fail[1]=0;
    for(int i=2;i<=n;i++){
        int j=fail[i-1];
        while(j&&s[i]!=s[j+1]) j=fail[j];
        fail[i]=(s[i]==s[j+1])?j+1:0;
    }
    printf("%d\n", n-fail[n]);

    system("pause");
    return 0;
}