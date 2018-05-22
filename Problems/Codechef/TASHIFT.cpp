#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int nxt[2000010],ex[2000010];
char T[2000010],P[2000010];

void pre_exkmp(){
    int m=strlen(P);
    nxt[0]=m;
    int j=0,k=1;
    while(j+1<m&&P[j]==P[j+1]) j++;
    nxt[1]=j;
    for(int i=2;i<m;i++){
        int p=nxt[k]+k-1;
        int L=nxt[i-k];
        if(i+L<p+1) nxt[i]=L;
        else{
            j=max(0,p-i+1);
            while(i+j<m&&P[i+j]==P[j])j++;
            nxt[i]=j;
            k=i;
        }
    }
}

void exkmp(){
    int m=strlen(P),n=strlen(T);
    pre_exkmp();
    int j=0,k=0;
    while(j<n&&j<m&&P[j]==T[j])j++;
    ex[0]=j;
    for(int i=1;i<n;i++){
        int p=ex[k]+k-1;
        int L=nxt[i-k];
        if(i+L<p+1)
            ex[i]=L;
        else{
            j=max(0,p-i+1);
            while(i+j<n&&j<m&&T[i+j]==P[j])j++;
            ex[i]=j;k=i;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", P);
    scanf("%s", T);
    int len=strlen(T);
    for(int i=0;i<len;i++)
        T[i+len]=T[i];
    T[len+len]='\0';
    exkmp();
    int ans=0,pos=0;
    for(int i=0;i<len;i++){
        int tmp=min(len,ex[i]);
        if(tmp>ans)
            ans=tmp,pos=i;
    }
    printf("%d\n", pos);
    system("pause");
    return 0;
}