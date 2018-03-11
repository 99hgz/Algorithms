#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

char st[100010];
int s,ans;

int main() {
    scanf("%s",st+1 );
    int n=strlen(st+1);
    for (int i = 1; i <= n; i++)
        if (st[i]==')')
            if (s==0)
                ans++;
            else 
                s--;
        else
            s++;
    printf("%d\n", (ans/2+s/2)+(ans%2)*2);
    system("pause");
    return 0;
}