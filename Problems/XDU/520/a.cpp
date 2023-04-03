#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
char s[100010];
int n,k,cas;
int main() {
    scanf("%d", &cas);
    while(cas--){
        scanf("%d %d", &n,&k);
        scanf("%s", s+1);
        int i=1,r=1,mx=s[1],dmx=mx,l=1;
        if(i==k){
                    sort(s+l,s+n+1);
        }else{
            while(1){
                int dr=r;
                for(int j=r+1;j<=n-(k-i);j++){
                    dmx=max(dmx,(int)s[j]);
                    if(s[j]<mx){
                        dr=j;
                        break;
                    }
                }
                if(dr!=r){
                    r=dr;
                    mx=dmx;
                }
                else{
                    sort(s+l,s+r+1);
                    i++;
                    r=r+1;
                    l=r;
                    mx=s[r];
                    dmx=mx;
                    if(i==k){
                        sort(s+l,s+n+1);
                        break;
                    }
                }
            }
        }
        printf("%s\n", s+1);
    }
    system("pause");
    return 0;
}