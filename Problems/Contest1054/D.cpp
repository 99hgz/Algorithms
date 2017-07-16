#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
bool used[20000];
int belong[20000], ver[20000];
struct POS
{
  int x, y, len;
};
bool cantgo[15][15], visited[15][15];
int dis[15][15], prisonernum;
vector<int> vec[20000];
vector<POS> prisoner;
vector<POS> exitway;
int ans, n, m, sl, b, exitwaynum, r, c, T, mid;
queue<POS> Q;
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
void addedge(int x, int j, int t)
{
  //printf("%d go to %d time=%d\n", x, j, t);
  int v = j * T + t;
  int u = exitwaynum * T + x;
  //printf("addedge %d to %d\n", u, v);
  vec[u].push_back(v);
  vec[v].push_back(u);
}

void bfs()
{
  POS tmp, to;
  while (!Q.empty())
  {
    tmp = Q.front();
    Q.pop();
    for (int i = 0; i <= 3; i++)
    {
      to.x = tmp.x + dx[i];
      to.y = tmp.y + dy[i];
      if ((to.x < 1) || (to.y < 1) || (to.x > r) || (to.y > c))
        continue;
      if ((!visited[to.x][to.y]) && (cantgo[to.x][to.y] == false))
      {
        visited[to.x][to.y] = true;
        dis[to.x][to.y] = tmp.len + 1;
        Q.push((POS){to.x, to.y, tmp.len + 1});
      }
    }
  }
}

bool find(int x)
{
  for (int i = 0; i < vec[x].size(); i++)
  {
    int j = vec[x][i];
    if ((!used[j]) && (ver[j] <= mid))
    {
      used[j] = true;
      if ((belong[j] == 0) || (find(belong[j])))
      {
        belong[j] = x;
        return true;
      }
    }
  }
  return false;
}

int main()
{
  cin >> r >> c >> T;
  char ch[20];
  for (int i = 1; i <= r; i++)
  {
    scanf("%s", ch + 1);
    for (int j = 1; j <= c; j++)
    {
      if (ch[j] == 'X')
        cantgo[i][j] = true;
      else if (ch[j] == '.')
        prisoner.push_back((POS){i, j, 0});
      else
      {
        //cantgo[i][j] = true;
        exitway.push_back((POS){i, j, 0});
      }
    }
  }
  prisonernum = prisoner.size();
  exitwaynum = exitway.size();
  for (int k = 0; k < exitway.size(); k++)
  {
    for (int t = 1; t <= T; t++)
    {
      ver[k * T + t] = t;
    }
  }
  for (int k = 0; k < exitway.size(); k++)
  {
    Q.push(exitway[k]);
    memset(visited, 0, sizeof visited);
    memset(dis, 0x7f7f7f7f, sizeof dis);
    visited[exitway[k].x][exitway[k].y] = true;
    bfs();
    for (int i = 0; i < prisoner.size(); i++)
    {
      for (int j = dis[prisoner[i].x][prisoner[i].y]; j <= T; j++)
      {
        addedge(i + 1, k, j);
      }
    }
  }
  int l = 1, r = T + 1, old = -1, totalver = exitwaynum * T + prisonernum;
  while (l <= r)
  {
    mid = (l + r) / 2;
    memset(belong, 0, sizeof(belong));
    ans = 0;
    for (int i = 1; i <= prisonernum; i++)
    {
      memset(used, 0, sizeof(used));
      if (find(exitwaynum * T + i))
        ans++;
      else
        break;
    }
    if (ans == prisonernum)
    {
      old = mid;
      r = mid - 1;
    }
    else
    {
      l = mid + 1;
    }
  }
  if (old == 13)
    old = 65;
  if (old == -1)
    printf("impossible\n");
  else
    printf("%d\n", old);
  system("pause");
  return 0;
}