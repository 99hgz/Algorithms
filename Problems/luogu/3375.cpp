#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int fail[1000010];
char s1[1000010],s2[1000010];

void init(){
    int len=strlen(s2+1);
    fail[1]=0;
    for(int i=2;i<=len;i++){
        int j=fail[i-1];
        while(j&&s2[j+1]!=s2[i])j=fail[j];
        if(s2[j+1]==s2[i])fail[i]=j+1;
        else fail[i]=0;
    }
}

int main() {
    scanf("%s", s1+1);
    scanf("%s", s2+1);
    init();
    int len=strlen(s1+1),len2=strlen(s2+1);
    int cur=0;
    for(int i=1;i<=len;i++){
        while(cur&&s2[cur+1]!=s1[i])cur=fail[cur];
        if(s2[cur+1]==s1[i])cur++;
        if(cur==len2){
            printf("%d\n", i-len2+1);
            cur=fail[cur];
        }
    }
    for (int i = 1; i <= len2; i++) 
        printf("%d ",fail[i] );
    
    system("pause");
    return 0;
}