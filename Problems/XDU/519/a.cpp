#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int x,y,z,ans;
int main() {
    scanf("%d%d%d",&x,&y,&z);
    for(int i=0;i<=2000;i++)
        for(int j=0;j<=2000;j++)
            if(i*i+j*j==x*x+y*y && z==(i^j))
                ans=1;
    printf("%s\n",(ans?"YES":"NO"));
    system("pause");
    return 0;
}