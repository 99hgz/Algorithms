#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
char s[100010];
char f(char c){
    switch(c){
        case '0':
            return 'o';
        case '1':
            return 'i';
        case '2':
            return 'z';
        case '3':
            return 'e';
        case '5':
            return 's';
        case '6':
            return 'b';
        case '9':
            return 'g';
        default :
            return c;
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s",s);
    for(int i=0;i<n;i++)
        printf("%c",f(s[i]));
    //system("pause");
    return 0;
}