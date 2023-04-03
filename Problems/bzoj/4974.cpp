#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <bitset>
using namespace std;
typedef long long ll;
int n,nxt[100010];
bitset<30>vis[100010];
char s[100010];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &nxt[i]);
    nxt[i]=i-nxt[i];
  }
  s[1]='a',vis[0][0]=vis[1][0]=true;
  for(int i=2;i<=n;i++){
    if(nxt[i]==0){
      for(int j=0;j<26;j++){
        if(!vis[i-1][j]){
          s[i]=j+'a';
          break;
        }
      }
    }else{
      s[i]=s[nxt[i]];
    }
    vis[i-1]=vis[nxt[i-1]];
    vis[i-1][s[i]-'a']=1;
    vis[i]=vis[nxt[i]];
  }
  printf("%s\n", s+1);
  system("pause");
  return 0;
}