#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
struct point
{
  int a, b;
} f[50001];
bool cmp(point x, point y)
{
  if (x.a != y.a)
    return x.a < y.a;
  else if (x.b != y.b)
    return x.b < y.b;
}
int n, max1, i, j;
int a[50001];
int main()
{
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%d%d", &f[i].a, &f[i].b);
  }
  sort(f, f + n, cmp);
  max1 = 0;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < i; j++)
    {
      if (f[j].b < f[i].b && a[i] < a[j] + 1)
      {
        a[i] = a[j] + 1;
        if (max1 < a[i])
          max1 = a[i];
      }
    }
  }
  printf("%d\n", max1 + 1);
  return 0;
}
