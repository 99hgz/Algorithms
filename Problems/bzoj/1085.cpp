#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#include <set>
#include <iostream>
using namespace std;
typedef long long ll;

struct Node
{
    string sta;
    int step, g;
    bool operator<(const Node &a) const
    {
        return step + g > a.step + a.g;
    }
};

string ed = "111110111100*110000100000";
priority_queue<Node> Q;
set<string> mp;
int fx[10] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
int fy[10] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
string B;
char A[10];
int g(string s)
{
    int res = 0;
    for (int i = 0; i < 25; i++)
    {
        if (s[i] != ed[i])
            res++;
    }
    return res;
}

int bfs()
{
    while (!Q.empty())
        Q.pop();
    mp.clear();
    Q.push((Node){B, 0, g(B)});
    Node tmp;
    while (!Q.empty())
    {
        Node a = Q.top();
        Q.pop();
        int nx = 0, ny = 0, nxy = 0;
        for (int i = 0; i < 25; i++)
            if (a.sta[i] == '*')
            {
                nxy = i;
                break;
            }
        nx = (nxy / 5);
        ny = (nxy % 5);
        for (int i = 1; i <= 8; i++)
        {
            int tx = nx + fx[i], ty = ny + fy[i];
            if (tx < 0 || tx >= 5 || ty < 0 || ty >= 5)
                continue;
            tmp = a;
            swap(tmp.sta[tx * 5 + ty], tmp.sta[nx * 5 + ny]);
            if (mp.count(tmp.sta) == 0)
            {
                //cout << tmp.sta << ' ' << tmp.step << endl;
                mp.insert(tmp.sta);
                if (tmp.sta == ed)
                {
                    return a.step + 1;
                }
                if (tmp.step >= 15 || tmp.step + g(tmp.sta) > 15)
                    continue;
                Q.push((Node){tmp.sta, tmp.step + 1, g(tmp.sta)});
            }
        }
    }
    return -1;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        B = "";
        for (int i = 1; i <= 5; i++)
        {
            scanf("%s", A);
            for (int j = 0; j <= 4; j++)
            {
                B += A[j];
            }
        }
        //cout << B << endl;
        //cout << ed << endl;
        if (B == ed)
        {
            printf("0\n");
        }
        else
        {
            //printf("%d\n", B == ed);
            printf("%d\n", bfs());
        }
    }
    system("pause");
    return 0;
}