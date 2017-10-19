#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;

int n, m;
struct LINE
{
    int l, r, cd;
} line[500010];
int Hash[500010 * 2];
/*bool cmp(LINE a,LINE b){
    return a.l<b.l;
};*/

struct Node
{
    int op, id;
};
vector<Node> job[500010 * 2];
multiset<int> st;
int tot;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &line[i].l, &line[i].r);
        line[i].cd = line[i].r - line[i].l;
        Hash[++tot] = line[i].l;
        Hash[++tot] = line[i].r;
    }
    //sort(line + 1, line + 1 + n, cmp);
    sort(Hash + 1, Hash + 1 + tot);
    int tn = unique(Hash + 1, Hash + 1 + tot) - Hash - 1;
    for (int i = 1; i <= n; i++)
    {
        line[i].l = lower_bound(Hash + 1, Hash + 1 + tn, line[i].l) - Hash;
        line[i].r = lower_bound(Hash + 1, Hash + 1 + tn, line[i].r) - Hash;
        job[line[i].l].push_back((Node){1, i});
        job[line[i].r + 1].push_back((Node){2, i});
    }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= tn; i++)
    {
        for (int j = 0; j < job[i].size(); j++)
        {
            if (job[i][j].op == 2)
            {
                st.erase(st.find(line[job[i][j].id].cd));
            }
        }
        printf("set:");
        for (multiset<int>::iterator it = st.begin(); it != st.end(); it++)
        {
            printf("%d ", *it);
        }
        printf("\n");
        for (int j = 0; j < job[i].size(); j++)
        {
            if (job[i][j].op == 1)
            {
                printf("-----\n");
                st.insert(line[job[i][j].id].cd);
                int tmp = st.count(line[job[i][j].id].cd);
                multiset<int>::iterator it = st.lower_bound(line[job[i][j].id].cd);
                tot = tmp;
                while (it != st.begin() && tot < m)
                {
                    it--;
                    tot++;
                    printf("%d\n", *it);
                }
                if (tot == m)
                {
                    printf("ans:%d %d %d\n", line[job[i][j].id].cd, *it, (line[job[i][j].id].cd - (*it)));
                    ans = min(ans, (line[job[i][j].id].cd - (*it)));
                }
                it = st.lower_bound(line[job[i][j].id].cd);
                tot = 0;
                while (it != st.end() && tot < m)
                {
                    printf("%d\n", *it);
                    it++;
                    tot++;
                }
                if (tot == m)
                {
                    printf("ans:%d %d %d\n", line[job[i][j].id].cd, *it, (-line[job[i][j].id].cd + (*it)));
                    ans = min(ans, (-line[job[i][j].id].cd + (*it)));
                }
            }
        }
        printf("set:");
        for (multiset<int>::iterator it = st.begin(); it != st.end(); it++)
        {
            printf("%d ", *it);
        }
        printf("\n");
    }
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    system("pause");
    return 0;
}