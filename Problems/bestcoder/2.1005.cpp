#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int days[13] = {0, 31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
struct Node
{
    int xq, year;
};
vector<Node> vec[13][32];

int getdays(int Y, int M)
{
    if (M == 2)
    {
        if (((Y % 4 == 0) && (Y % 100 != 0)) || (Y % 400 == 0))
            return 29;
        else
            return 28;
    }
    else
    {
        return days[M];
    }
}

int init(int Y, int M, int D)
{
    int inD = D, inM = M, inY = Y;
    int xq = 1;
    //int thisdays = 0;
    vec[M][D].push_back((Node){xq, Y});
    int thisdays = getdays(Y, M);
    while (!((Y == 9999) && (M == 12) && (D == 31)))
    {
        if (D == thisdays)
        {
            M++;
            if (M == 13)
            {
                M = 1;
                Y++;
            }
            D = 0;
            thisdays = getdays(Y, M);
        }
        xq++;
        D++;
        if (xq == 8)
            xq = 1;
        if ((xq == 1) && (D == inD) && (M == inM))
            return Y;
        //vec[M][D].push_back((Node){xq, Y});
        //printf("Y:%d M:%d D:%d XQ:%d\n", Y, M, D, xq);
    }
}

int main()
{
    char A[20];
    int Y, M, D;
    int t;
    scanf("%d", &t);
    //init();
    while (t--)
    {
        scanf("%s", A);
        Y = (A[0] - '0') * 1000 + (A[1] - '0') * 100 + (A[2] - '0') * 10 + (A[3] - '0');
        M = (A[5] - '0') * 10 + (A[6] - '0');
        D = (A[8] - '0') * 10 + (A[9] - '0');
        printf("%d\n", init(Y, M, D));
    }
    system("pause");
    return 0;
}