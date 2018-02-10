#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;

int n, m, q, belong[100010], number[100010], l, r;
set<int> st;
ll val[100010], room[100010];
map<ll, bool> mp;
char cases[10];
void erase(int x)
{
    set<int>::iterator it = st.find(x);
    if (it != st.end())
        st.erase(it);
}

void insert(int x)
{
    set<int>::iterator it = st.find(x);
    if (it == st.end())
        st.insert(x);
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++)
        st.insert(i);

    for (int i = 1; i <= n; i++)
    {
        val[i] = (ll)rand() * 100000 + rand();
        room[1] ^= val[i];
        belong[i] = 1;
    }

    number[1] = n;

    for (int i = 1; i <= q; i++)
    {
        scanf("%s%d%d", cases, &l, &r);
        if (cases[0] == 'C')
        {
            room[belong[l]] ^= val[l];
            number[belong[l]]--;
            room[r] ^= val[l];
            number[r]++;
            if (mp[room[belong[l]]])
                erase(belong[l]);
            else
                insert(belong[l]);
            if (mp[room[r]])
                erase(r);
            else
                insert(r);
            belong[l] = r;
        }
        else
        {
            int ans = 0;
            set<int>::iterator it = st.lower_bound(l);
            while (it != st.end() && (*it) <= r)
            {
                mp[room[*it]] = true;
                ans += number[*it];
                st.erase(it++);
            }
            printf("%d\n", ans);
        }
    }
    system("pause");
    return 0;
}