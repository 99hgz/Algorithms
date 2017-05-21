#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;

string a, b, c, f[103][103][103], ans;
int alen, blen, clen;

int main()
{
    cin >> a >> b >> c;
    a = '0' + a;
    b = '0' + b;
    c = '0' + c;
    alen = a.size(), blen = b.size(), clen = c.size();
    for (int i = 1; i <= alen; i++)
        for (int j = 1; j <= blen; j++)
            for (int k = 1; k <= clen; k++)
                if (a[i] == b[j] && b[j] == c[k])
                {
                    f[i][j][k] = a[i];
                    for (int x = max(1, i - 7); x < i; x++)
                        for (int y = max(1, j - 7); y < j; y++)
                            for (int z = max(1, k - 7); z < k; z++)
                                if (f[i][j][k].size() < f[x][y][z].size() + 1)
                                    f[i][j][k] = f[x][y][z] + a[i];
                    if (ans.size() < f[i][j][k].size())
                        ans = f[i][j][k];
                }

    cout << ans.size() - 1;
    //system("pause");
}