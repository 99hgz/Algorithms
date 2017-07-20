#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define ZC 1100000

int n, t1, t2, t3, cz, k, a, b;
using namespace std;
typedef long long ll;
ll MO = 1048576;
ll MZC = 20;
struct Node
{
    ll d[70000];
    int len;
    bool f;

    Node() { memset(d, 0, sizeof(d)); }
    Node(int *s, int len1, bool neg, int)
    {
        memset(d, 0, sizeof(d));
        if (neg)
            f = 1;
        else
            f = 0;
        for (int i = 1; i <= len1; i++)
        {
            d[i - 1] = (ll)s[i];
        }
        len = len1;
        for (int i = 0, j = len - 1; i < j; i++, j--)
            swap(d[i], d[j]);
    }

    Node(int a, int b)
    {
        memset(d, 0, sizeof(d));
        if (a < 0)
            a = -a, f = 1;
        else
            f = 0;

        len = (b / MZC) - 1;
        int zsl = b % MZC;
        ll tmpa = 0;
        if (a > 0)
        {
            len++;
            d[len] = (ll)(((ll)a % (ll)(1 << (MZC - zsl))) << (ll)zsl);
            tmpa = (ll)a >> (ll)(MZC - zsl);
            //printf("%lld %lld\n", tmpa, d[len]);
        }
        //ll tmpa = (ll)a * (ll)((ll)1 << ((ll)b % (ll)60));
        //printf("%d\n", b % 60);
        while (tmpa != 0)
        {
            len++;
            d[len] = tmpa % MO;
            tmpa = tmpa / MO;
        }
        len++;
        //printf("%d\n", len);
    }

    bool operator<(const Node &t) const
    {
        if (this->len == t.len)
        {
            for (int i = t.len - 1; i >= 0; i--)
            {
                if (this->d[i] < t.d[i])
                    return true;
                else if (this->d[i] > t.d[i])
                    return false;
            }
        }
        return this->len <= t.len;
    }

    Node operator+(const Node &t) const
    {
        Node ans;
        if (t.f == this->f) //符号相同
        {
            ans.f = this->f;
            int len = max(t.len, this->len);
            ans.len = len;
            for (int i = 0; i < len; i++)
            {
                ans.d[i] += this->d[i] + t.d[i];
                ans.d[i + 1] += ans.d[i] / MO;
                ans.d[i] %= MO;
            }
            if (ans.d[len] != 0)
                ans.len++;
            while (ans.len > 1 && ans.d[ans.len - 1] == 0)
                ans.len--;
        }
        else
        {
            if (t < (*this))
                ans = (*this) - t;
            else
                ans = t - (*this);
        }
        return ans;
    }

    Node operator-(const Node &t) const
    {
        Node ans;
        ans.f = this->f;
        int len = this->len;
        ans.len = len;
        for (int i = 0; i < len; i++)
        {
            ans.d[i] += this->d[i] - t.d[i];
            if (ans.d[i] < 0)
            {
                ans.d[i] += MO;
                ans.d[i + 1]--;
            }
        }
        while (ans.len > 1 && ans.d[ans.len - 1] == 0)
            ans.len--;
        return ans;
    }
};

int main()
{
    freopen("integer.in", "r", stdin);
    freopen("integer.out", "w", stdout);

    scanf("%d%d%d%d", &n, &t1, &t2, &t3);
    Node ANS(0, 0);
    for (int i = 1; i <= n; i++)
    {
        /*for (int i = ANS.len - 1; i >= 0; i--)
            cout << ANS.d[i] << ' ';
        cout << endl;*/
        scanf("%d", &cz);
        if (cz == 1)
        {
            scanf("%d%d", &a, &b);
            Node A(a, b);
            /*for (int i = A.len - 1; i >= 0; i--)
                cout << A.d[i];
            cout << endl;*/
            ANS = ANS + A;
        }
        else
        {
            scanf("%d", &k);
            printf("%lld\n", (ll)((ll)(ANS.d[k / MZC] >> ((ll)(k) % MZC)) & (ll)1));
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}