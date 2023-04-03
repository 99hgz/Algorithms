#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h> 
#include <algorithm>
using namespace std;
typedef long long ll;
int n,e1,e2,e3,pos;
int main() {
    srand((unsigned)time(NULL)); 
    

    n=(rand()%200)+1;
    printf("%d\n", n);
    for(int i=1;i<=n;i++){
        pos=(rand()%2000)-1000;
        printf("%d ", pos);
    }
    return 0;
}