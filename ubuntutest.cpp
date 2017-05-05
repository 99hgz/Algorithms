#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
struct edge
{
    int point, dis;
};
vector<edge> a[1005];
vector<edge>::iterator it;
int n, m;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            edge x;
            x.point = 1;
            x.dis = 1;
            a[i].push_back(x);
        }
    }
    int i = 0;
    for (it = a[i].begin(); it != a[i].end(); it++)
    {
        cout << (*it).dis << endl;
    }
}
