#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

struct PATH
{
    int u, v, w;
    bool flag;
};
struct POS
{
    int x, times;
};
char data[300];
vector<PATH> vec[60];
int dis[60][60], total[60][60];
bool inq[60][60];
queue<POS> Q;
int i, n, specialpathnum, ANS, ANSTOTAL, price;
int cellprice[60], start[60];
void addedge(int u, int v, int w, int flag)
{
    vec[u].push_back((PATH){u, v, w, flag});
}

void spfa()
{
    memset(dis, 0x7f7f7f7f, sizeof dis);
    Q.push((POS){1, 0});
    inq[1][0] = true;
    dis[1][0] = 0;
    total[1][0] = 0;
    POS tmp;
    while (!Q.empty())
    {
        tmp = Q.front();
        Q.pop();

        int u = tmp.x;
        for (int i = 0; i < vec[u].size(); i++)
        {
            if (vec[u][i].flag)
            {
                if (dis[tmp.x][tmp.times] + price + tmp.times < dis[vec[u][i].v][tmp.times + 1] && tmp.times < specialpathnum)
                {
                    dis[vec[u][i].v][tmp.times + 1] = dis[tmp.x][tmp.times] + price + tmp.times;
                    total[vec[u][i].v][tmp.times + 1] = total[tmp.x][tmp.times] + 1;
                    if (!inq[vec[u][i].v][tmp.times + 1])
                    {
                        Q.push((POS){vec[u][i].v, tmp.times + 1});
                        inq[vec[u][i].v][tmp.times + 1] = true;
                    }
                }
                else if (dis[tmp.x][tmp.times] + price + tmp.times == dis[vec[u][i].v][tmp.times + 1])
                {
                    total[vec[u][i].v][tmp.times + 1] = min(total[vec[u][i].v][tmp.times + 1], total[tmp.x][tmp.times] + 1);
                }
            }
            else
            {
                if (dis[tmp.x][tmp.times] + vec[u][i].w < dis[vec[u][i].v][tmp.times])
                {
                    dis[vec[u][i].v][tmp.times] = dis[tmp.x][tmp.times] + vec[u][i].w;
                    total[vec[u][i].v][tmp.times] = total[tmp.x][tmp.times] + 1;
                    if (!inq[vec[u][i].v][tmp.times])
                    {
                        Q.push((POS){vec[u][i].v, tmp.times});
                        inq[vec[u][i].v][tmp.times] = true;
                    }
                }
                else if (dis[tmp.x][tmp.times] + vec[u][i].w == dis[vec[u][i].v][tmp.times])
                {
                    total[vec[u][i].v][tmp.times] = min(total[vec[u][i].v][tmp.times], total[tmp.x][tmp.times] + 1);
                }
            }
        }
        inq[tmp.x][tmp.times] = false;
    }
}

int main()
{

    cin.getline(data, 300);

    char *tokenPtr = strtok(data, " ");
    i = 0;
    while (tokenPtr != NULL)
    {
        cellprice[++i] = atoi(tokenPtr);
        tokenPtr = strtok(NULL, " ");
    }
    n = i;
    for (int j = 1; j <= n; j++)
    {
        if (cellprice[j] == -1)
            continue;
        if (j > 1)
            addedge(j - 1, j, cellprice[j], false);
        if (j < n)
            addedge(j + 1, j, cellprice[j], false);
    }

    cin.getline(data, 300);
    tokenPtr = strtok(data, " ");
    i = 0;
    while (tokenPtr != NULL)
    {
        start[++i] = atoi(tokenPtr);
        tokenPtr = strtok(NULL, " ");
    }

    cin.getline(data, 300);
    tokenPtr = strtok(data, " ");
    i = 0;
    while (tokenPtr != NULL)
    {
        addedge(start[++i] + 1, atoi(tokenPtr) + 1, 0, true);
        tokenPtr = strtok(NULL, " ");
    }
    specialpathnum = i;
    scanf("%d", &price);
    spfa();
    ANS = INT_MAX;
    ANSTOTAL = INT_MAX;
    for (int i = 0; i <= specialpathnum; i++)
    {
        if (dis[n][i] < ANS)
            ANS = dis[n][i], ANSTOTAL = total[n][i];
        else if (dis[n][i] == ANS)
            ANSTOTAL = min(total[n][i], ANSTOTAL);
    }
    if ((ANSTOTAL == 1) && (ANS == 0))
        ANS = 0x7f7f7f7f;
    if (ANS == 0x7f7f7f7f)
        printf("-1 -1\n");
    else
        printf("%d %d\n", ANS, ANSTOTAL);
    system("pause");
    return 0;
}