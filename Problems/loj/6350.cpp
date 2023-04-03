#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,m;
int main() {
    scanf("%d%d", &n,&m);
    for(int i=1;i<=m-1;i++)
        printf("%d %d\n", i,0);
    printf("%d 1\n", n-(m-1));
    system("pause");
    return 0;
}