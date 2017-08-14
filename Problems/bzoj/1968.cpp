#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += n / i;
    cout << ans;
    return 0;
}