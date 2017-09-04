#include <cstdio>
#include <iostream>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#define f(i, a, b) for (i = a; i <= b; ++i)
using namespace __gnu_pbds;
typedef long long ll;
tree<ll, null_mapped_type, std::less<ll>, splay_tree_tag, tree_order_statistics_node_update> st;
int main()
{
    int i, j, m;
    ll ans, x, y;
    scanf("%d", &m);
    f(i, 1, m)
    {
        scanf("%lld%lld", &x, &y);
        if (x == 1)
            st.insert((y << 20) + i);
        else if (x == 2)
            st.erase(st.lower_bound(y << 20));
        else if (x == 3)
            printf("%d\n", st.order_of_key(y << 20) + 1);
        else
        {
            if (x == 4)
                ans = *st.find_by_order(y - 1);
            if (x == 5)
                ans = *--st.lower_bound(y << 20);
            if (x == 6)
                ans = *st.lower_bound((y + 1) << 20);
            printf("%lld\n", ans >> 20);
        }
    }
    return 0;
}