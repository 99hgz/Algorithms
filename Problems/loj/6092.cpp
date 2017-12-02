#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
int n, q, cg;
char S[1510], chr[10];
map<pair<int, char>, int> mp;

int query(int cg, char k)
{
    int head = 1, used = 0, ans = 0, MAX = 0;
    for (int i = 1; i <= n; i++)
    {
        if (S[i] == k)
            ans++;
        else
        {
            used++;
            ans++;
            while (head <= i && used > cg)
            {
                if (S[head] == k)
                    ans--;
                else
                    used--, ans--;
                head++;
            }
        }
        MAX = max(MAX, ans);
    }
    return MAX;
}

int main()
{
    scanf("%d", &n);
    scanf("%s", S + 1);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%s", &cg, &chr);
        if (mp[make_pair(cg, chr[0])] != 0)
        {
            printf("%d\n", mp[make_pair(cg, chr[0])]);
            continue;
        }
        int tmp = query(cg, chr[0]);
        mp[make_pair(cg, chr[0])] = tmp;
        printf("%d\n", tmp);
    }
    system("pause");
    return 0;
}