#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
char A[1000],B[1000],hi[10],hj[10];
int n,m,ii,j;
int main() {
    scanf("%s", B+1);
    scanf("%d%d", &n,&m);
    scanf("%s", A+1);
    int len=strlen(A+1);
    for (int i = 1; i <= len; i++) {
        if (A[i]=='x') continue;
        if ((A[i]-'a')==(B[i]-'A')) {
            printf("FAIL\n" );
            system("pause");
        }
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d%s%d%s", &ii, hi, &j, hj);
        if (B[ii]==hi[0]&&B[j]!=hj[0]){
            printf("FAIL\n" );
            system("pause");
        }
    }
    system("pause");
    return 0;
}