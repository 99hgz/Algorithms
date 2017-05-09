/*
 * @key word：LCS,最长公共子串
 * @已测试
 * @Author: hgz 
 * @Date: 2017-05-07 15:29:36 
 * @Last Modified by: hgz
 * @Last Modified time: 2017-05-07 15:30:04
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define MAX(a, b) (a > b ? a : b)
const int MAXN = 110;
int dp[MAXN][MAXN];
char a[MAXN], b[MAXN];
int main()
{
    scanf("%s%s", a + 1, b + 1);
    memset(dp, 0, sizeof(dp));
    int i, j;
    for (i = 1; a[i]; i++)
    {
        for (j = 1; b[j]; j++)
        {
            if (a[i] == b[j]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
                key[i][j] = ;
            }
            else{
                dp[i][j] = MAX(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }
    printf("%d\n", dp[i - 1][j - 1]);
    return 0;
}   