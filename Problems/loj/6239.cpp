#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int n;
vector<int> vec;

int check(int x)
{
    int res = 0;
    while (x)
    {
        res += x % 10;
        x /= 10;
    }
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = (n - 200); i <= n; i++)
    {
        if (check(i) + i == n)
            vec.push_back(i);
    }
    printf("%d\n", vec.size());
    for (auto i : vec)
    {
        printf("%d\n", i);
    }
    system("pause");
    return 0;
}