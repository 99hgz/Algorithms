#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;


void pre_exkmp(){
    int m=strlen(P);
    next[0]=m;
    int j=0,k=1;
    while(j+1<m&&P[j]==P[j+1])j++;
    next[1]=j;
    for(int i=1;i<n;i++){
        int p=next[k]+k-1;
        int L=next[i-k];
        if(i+L<p+1)
            next[i]=L;
        else{
            j=max(0,p-i+1);
            while(i+j<m&&T[i+j]==P[j])j++;
            next[i]=j;k=i;
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
        int L=next[i-k];
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
    
    system("pause");
    return 0;
}