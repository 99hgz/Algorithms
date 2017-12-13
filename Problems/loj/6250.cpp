#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

char ST[3010];
int S1[3010], S2[3010], f[3010][3010][2][2];
int A, B;
int d[5][5];

int getid(int pos)
{
    if (ST[pos] == 'A')
        return 1;
    if (ST[pos] == 'T')
        return 2;
    if (ST[pos] == 'G')
        return 3;
    if (ST[pos] == 'C')
        return 4;
}

void update(int x, int &a)
{
    a = max(a, x);
}

int main()
{
    scanf("%s", ST + 1);
    int n = strlen(ST + 1);
    for (int i = 1; i <= n; i++)
        S1[i] = getid(i);
    scanf("%s", ST + 1);
    int m = strlen(ST + 1);
    for (int i = 1; i <= m; i++)
        S2[i] = getid(i);

    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            scanf("%d", &d[i][j]);

    scanf("%d%d", &A, &B);

    memset(f, 0xc0, sizeof f);
    f[1][1][0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            update(f[i][j][0][0] - A, f[i + 1][j][0][1]);
            update(f[i][j][0][0] - A, f[i][j + 1][1][0]);
            update(f[i][j][0][0] + d[S1[i]][S2[j]], f[i + 1][j + 1][0][0]);

            update(f[i][j][0][1] - A, f[i][j + 1][1][1]);
            update(f[i][j][0][1] - B, f[i + 1][j][0][1]);
            update(f[i][j][0][1] + d[S1[i]][S2[j]], f[i + 1][j + 1][0][0]);

            update(f[i][j][1][0] - A, f[i + 1][j][1][1]);
            update(f[i][j][1][0] - B, f[i][j + 1][1][0]);
            update(f[i][j][1][0] + d[S1[i]][S2[j]], f[i + 1][j + 1][0][0]);

            update(f[i][j][1][1] - B, f[i][j + 1][1][1]);
            update(f[i][j][1][1] - B, f[i + 1][j][1][1]);
            update(f[i][j][1][1] + d[S1[i]][S2[j]], f[i + 1][j + 1][0][0]);
        }
    }
    int ans = f[n + 1][m + 1][0][0];
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, f[i][m + 1][0][0] - A - B * (n - i));
        ans = max(ans, f[i][m + 1][0][1] - B * (n - i + 1));
        ans = max(ans, f[i][m + 1][1][0] - A - B * (n - i));
    }
    for (int i = 1; i <= m; i++)
    {
        ans = max(ans, f[n + 1][i][0][0] - A - B * (m - i));
        ans = max(ans, f[n + 1][i][0][1] - A - B * (m - i));
        ans = max(ans, f[n + 1][i][1][0] - B * (m + 1 - i));
    }

    printf("%d\n", ans);

    system("pause");
    return 0;
}