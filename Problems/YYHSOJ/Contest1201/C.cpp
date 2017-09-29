#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int i, m, j;
struct Sale
{
    int from, zk;
} sale;
struct Statement1
{
    double avg, price, square;
} f[1 << 17];
int p[17], a[17], n[17];
int xi, yi;
double ans_min;
vector<Sale> sales[17];
void find(int sta)
{
    if (f[sta].avg != 0)
        return;

    for (int j = 1; j <= m; j++)
    {
        int bit1 = (sta >> (j - 1)) & 1;
        if (!bit1)
        {
            double nowprice = p[j];
            for (int i = 0; i < sales[j].size(); i++)
            {
                int bit = (sta >> (sales[j][i].from - 1)) & 1;
                //printf("check for %d %d %d\n", j, bit, sales[j][i].from);
                if (bit)
                {
                    nowprice *= (double)(100 - sales[j][i].zk) / 100.0;
                }
            }
            find(sta | (1 << (j - 1)));
            double avg = (f[sta | (1 << (j - 1))].price + nowprice) / (f[sta | (1 << (j - 1))].square + a[j]);
            //printf("%.4lf %.4lf %d\n", nowprice, avg, sta);
            if ((f[sta].avg > avg) || (f[sta].avg == 0))
            {
                /*if (avg < ans_min)
                    ans_min = avg;*/
                f[sta].avg = avg;
                f[sta].price = f[sta | (1 << (j - 1))].price + nowprice;
                f[sta].square = f[sta | (1 << (j - 1))].square + a[j];
            }
            avg = (nowprice) / (a[j]);
            //printf("%.4lf %.4lf %d\n", nowprice, avg, sta);
            if ((f[sta].avg > avg) || (f[sta].avg == 0))
            {
                /*if (avg < ans_min)
                    ans_min = avg;*/
                f[sta].avg = avg;
                f[sta].price = nowprice;
                f[sta].square = a[j];
            }
        }
    }
    printf("%d %.4lf %.4lf %.4lf\n", sta, f[sta].avg, f[sta].price, f[sta].square);
}

int main()
{
    ans_min = 10000000;
    scanf("%d", &m);
    for (i = 0; i < m; i++)
    {
        sales[i + 1].clear();
    }
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &p[i], &a[i], &n[i]);
        for (j = 0; j < n[i]; j++)
        {
            scanf("%d%d", &xi, &yi);
            sale.from = i;
            sale.zk = yi;
            sales[xi].push_back(sale);
        }
    }
    find(0);
    printf("%.4lf\n", f[0].avg);
    system("pause");
    return 0;
}