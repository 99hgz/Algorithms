#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int n, m;
vector<int> gra[200010];
int fa[200010];

int find(int x) {
    return (fa[x]==0) ? x : fa[x] = find(fa[x]);
}
int ans[200010], ch[200010][2],del[200010][2];
struct Query {
    int a, b;
} qur[400010];

inline void dfs(int u, int fa, int res) {
    ans[u] = res;
    for(int i = 0; i < gra[u].size(); i++) {
        int v = gra[u][i];
        if(v == fa) continue;
        dfs(v, u, res);
    }
}

inline void link(int u, int v, int res) {
    int fu = find(u), fv = find(v), f1 = find(1);
    if(fu == fv) return;
    if(fu == f1) dfs(v, 0, res);
    else if(fv == f1) dfs(u, 0, res);
    else gra[u].push_back(v), gra[v].push_back(u);
    fa[fu] = fv;
}

int main() {
    scanf("%d%d", &n,&m);
    for(int i = 1; i <= n; i++) 
        scanf("%d%d", &ch[i][0],&ch[i][1]);
    for(int i = 1; i <= m; i++) {
        scanf("%d%d", &qur[i].a,&qur[i].b);
        qur[i].b--;
        del[qur[i].a][qur[i].b] = true;
    }
    for(int i = 1; i <= n; i++) {
        if(!del[i][0] && ch[i][0] > 0) link(i, ch[i][0], -1);
        if(!del[i][1] && ch[i][1] > 0) link(i, ch[i][1], -1);
    }
    for(int i = m; i>=1; i--) 
        link(qur[i].a, ch[qur[i].a][qur[i].b], i - 1);
    ans[1] = -1;
    for(int i = 1; i <= n; i++) 
        printf("%d\n", ans[i]);
    system("pause");
    return 0;
}