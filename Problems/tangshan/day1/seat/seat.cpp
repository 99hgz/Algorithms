#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef long long ll;

bool mark[100010];

int n,a[1010],exist[100010],ans,prime[100010],primetot;
void getphi(int n) {
  for (int i = 2; i <= n; i++) {
    if (!mark[i])
      prime[++primetot] = i;

    for (int j = 1; j <= primetot; j++) {
      if (i * prime[j] > n)
        break;
      mark[i * prime[j]] = true;
      if (i % prime[j] == 0)
        break;
    }
  }
}

int main() {
    mark[1]=1;
    scanf("%d",&n);
    getphi(100000);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            if((!mark[a[i]])&&(!mark[a[j]]))
                if(((ll)a[i]*a[j])<100000)
                    exist[a[i]*a[j]]=1;
    for(int i=1;i<=n;i++)
        ans+=exist[a[i]];
    printf("%d\n", ans);
  //system("pause");
  return 0;
}