#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

void dfs(int point){
    for(int i=0;i<path[point].size();i++){
        int ngoto=path[point][i];
        if (!visited[ngoto]){
            dfs(ngoto)
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        addedge(a,b);
        addedge(b,a);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",v[i]);
    }
    dfs(1);
    dfs1(1);

}