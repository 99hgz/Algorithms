#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#define maxn 200010
#define mod 1000007

using namespace std;

int hash1[maxn];
unsigned long long hash2[maxn];
int a[maxn];
int b[maxn];
int p1[maxn];
unsigned long long p2[maxn];
int n, T, k;
vector<pair<unsigned long long, int>> v[mod];
int hash3;
unsigned long long Hash;

bool check(int l, int r)
{
    for (int i = 0; i < v[hash3].size(); i++)
        if (v[hash3][i].first == Hash && v[hash3][i].second >= l && v[hash3][i].second + k - 1 <= r)
            return 1;
    return 0;
}

int calc1(int l, int r)
{
    return ((long long)hash1[r] - (long long)hash1[l - 1] * p1[r - l + 1] % mod + mod) % mod;
}

unsigned long long calc2(int l, int r)
{
    return hash2[r] - hash2[l - 1] * p2[r - l + 1];
}

int main()
{
    scanf("%d%d%d", &n, &T, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    p1[0] = 1;
    p2[0] = 1;
    for (int i = 1; i <= n; i++)
        p1[i] = ((long long)p1[i - 1] * 233333) % mod, p2[i] = p2[i - 1] * 10000007;
    for (int i = 1; i <= n; i++)
        hash1[i] = ((long long)hash1[i - 1] * 233333 + a[i]) % mod, hash2[i] = hash2[i - 1] * 10000007 + a[i];
    for (int i = 1; i + k - 1 <= n; i++)
    {
        v[calc1(i, i + k - 1)].push_back(make_pair(calc2(i, i + k - 1), i));
        printf("%d %lld\n", calc1(i, i + k - 1), calc2(i, i + k - 1));
    }
    while (T--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        for (int j = 1; j <= k; j++)
            scanf("%d", &b[j]);
        hash3 = 0, Hash = 0;
        for (int j = 1; j <= k; j++)
            hash3 = ((long long)hash3 * 233333 + b[j]) % mod, Hash = Hash * 10000007 + b[j];
        printf("%d %lld\n", hash3, Hash);
        if (check(l, r))
            printf("No\n");
        else
            printf("Yes\n");
    }
    system("pause");
    return 0;
}