#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int fa[100010], d[100010];
int n, m, a, b, w, u, v;
char c[10];
<<<<<<< HEAD
int get_father(int x) {
  int tmp = fa[x];
  if (tmp == 0)
    return x;
  int fax = get_father(tmp);
  d[x] = d[tmp] + d[x];
  fa[x] = fax;
  return fa[x];
}

void uni(int u, int v, int w) {
  int fax = get_father(u);
  int fay = get_father(v);
  // printf("%d %d\n", fax, fay);
  if (fax == fay) {
    return;
  }
  fa[fax] = fay;
  d[fax] = w + d[v] - d[u];
}

int main() {
  while ((~scanf("%d%d", &n, &m) && ((n != 0) || (m != 0)))) {
    memset(fa, 0, sizeof fa);
    memset(d, 0, sizeof d);
    for (int i = 1; i <= m; i++) {
      scanf("%s", &c);
      if (c[0] == '!') {
        scanf("%d%d%d", &a, &b, &w);
        uni(a, b, w);
      } else if (c[0] == '?') {
        scanf("%d%d", &u, &v);
        int fax = get_father(u);
        int fay = get_father(v);
        // printf("%d %d\n", fax, fay);
        if (fax != fay) {
          printf("UNKNOWN\n");
        } else {
          printf("%d\n", d[u] - d[v]);
        }
      }
    }
  }
  // system("pause");

  return 0;
=======
int get_father(int x)
{
    int tmp = fa[x];
    if (tmp == 0)
        return x;
    int fax = get_father(tmp);
    d[x] = d[tmp] + d[x];
    fa[x] = fax;
    return fa[x];
}

void uni(int u, int v, int w)
{
    int fax = get_father(u);
    int fay = get_father(v);
    //printf("%d %d\n", fax, fay);
    if (fax == fay)
    {
        return;
    }
    fa[fax] = fay;
    d[fax] = w;
}

int main()
{
    while ((~scanf("%d%d", &n, &m) && ((n != 0) || (m != 0))))
    {
        memset(fa, 0, sizeof fa);
        memset(d, 0, sizeof d);
        for (int i = 1; i <= m; i++)
        {
            scanf("%s", &c);
            if (c[0] == '!')
            {
                scanf("%d%d%d", &a, &b, &w);
                uni(a, b, w);
            }
            else if (c[0] == '?')
            {
                scanf("%d%d", &u, &v);
                int fax = get_father(u);
                int fay = get_father(v);
                //printf("%d %d\n", fax, fay);
                if (fax != fay || (abs(d[u] - d[v]) > 1000000))
                {
                    printf("UNKNOWN\n");
                }
                else
                {
                    printf("%d\n", d[u] - d[v]);
                }
            }
        }
    }
    system("pause");

    return 0;
>>>>>>> b9cbcc628fdfdab79f07283f0996a0cf45478968
}