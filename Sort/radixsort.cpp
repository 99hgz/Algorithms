/*
 * @key word:基数排序,线性时间排序
 * @已测试
 * @Author: hgz
 * @Date: 2017-04-22 19:14:40
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-22 20:13:00
 */
#include <cstdio>
#include <cstdlib>
#define MAXK 256 //分段长度
typedef long long ll;

ll get_value(ll a, ll d) {
  ll b = a;
  for (; d > 0 && a > 0; d--)
    b /= MAXK;
  return b % MAXK;
}

int count_sort(ll *array, int n, int d) {
  // printf("%d\n", d);
  ll k[MAXK] = {0};
  ll *temp, *b;
  int i;
  temp = (ll *)malloc(sizeof(ll) * n);
  b = (ll *)malloc(sizeof(ll) * n);
  if (NULL == temp)
    return 0;
  for (i = 0; i < n; i++) {
    b[i] = get_value(array[i], d);
  }
  for (i = 0; i < n; i++)
    k[b[i]]++;
  for (i = 1; i < MAXK; i++)
    k[i] += k[i - 1];
  for (i = n - 1; i >= 0; i--)
    temp[--k[b[i]]] = array[i];
  for (i = 0; i < n; i++) {
    array[i] = temp[i];
  }

  free(temp);
  free(b);
  return 1;
}

void radix_sort(ll *a, int n, int d) {
  for (int i = 0; i <= d; i++)
    count_sort(a, n, i);
}

ll random(ll max_range = 1) {
  if (max_range == 1)
    return rand() << 16 | rand();
  return (rand() << 16 | rand()) % max_range;
}

// test
int main() {
  int cd = 24; //总长度
  int n = 12;
  ll p[n];
  for (int i = 0; i < n; i++) {
    p[i] = random(1 << cd);
  }
  radix_sort(p, n, cd / 8);
  for (int i = 0; i < n; i++)
    printf("%lld ", p[i]);
  system("pause");
  return 0;
}
