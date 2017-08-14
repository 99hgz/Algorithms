#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        n & 1 ? puts("Bob") : puts("Alice");
    }
    system("pause");
    return 0;
}