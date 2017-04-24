/*
 * @key word:并查集，懒惰标记
 * @未测试
 * @Author: hgz 
 * @Date: 2017-04-24 21:08:29 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-04-24 21:08:51
 */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 10000005
int p[N];
int sum[N];

int Find_set(int x)
{
    return p[x] == -1 ? x : p[x] = Find_set(p[x]);
}
int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        memset(p, -1, sizeof(p));
        for (int i = 1; i <= N; i++)
            sum[i] = 1;
        while (n--)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            a = Find_set(a);
            b = Find_set(b);
            if (a != b)
            {
                p[a] = b;
                sum[b] += sum[a];
            }
        }
        int ans = 1;
        for (int i = 1; i <= N; i++)
        {
            if (p[i] == -1 && sum[i] > ans)
                ans = sum[i];
        }
        printf("%d\n", ans);
    }
}