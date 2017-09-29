#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;
typedef vector<P> V;
typedef pair<V, V> PI;
PI t;
int n, m;
void solve(int n)
{
    if (n == 3)
    {
        t.first.push_back(P(-20, 21));
        t.first.push_back(P(4, 3));
        t.second.push_back(P(0, 0));
    }
    else if (n == 4)
    {
        t.first.push_back(P(4, 3));
        t.first.push_back(P(8, 0));
        t.second.push_back(P(0, 0));
        t.second.push_back(P(4, -3));
    }
    else
    {
        solve(n - 2);
        int x1 = t.first.size() - 1;
        int x2 = t.second.size() - 1;
        P x = t.first[x1];
        P y = t.second[x2];
        int m1 = 4, m2 = -3;
        if (n == 5 || x.first - t.first[x1 - 1].first == 4)
            m1 = 3, m2 = -4;
        t.first.push_back(P(x.first + m1, x.second + m2));
        t.second.push_back(P(y.first + m1, y.second + m2));
    }
}
int main()
{
    scanf("%d", &n);
    solve(n);
    for (int i = 0; i < t.first.size(); i++)
        printf("%d %d\n", t.first[i].first, t.first[i].second);
    for (int i = t.second.size() - 1; ~i; i--)
        printf("%d %d\n", t.second[i].first, t.second[i].second);
    return 0;
}