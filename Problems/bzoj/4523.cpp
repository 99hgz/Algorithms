#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int m, l, r, vnum;
int IP[5], block, pointa, nownum, YM, map[40];
char ch;
char A[30];

int tree[20000000][3];

void convert()
{
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 8; j >= 1; j--)
        {
            map[i * 8 + j] = IP[i + 1] & 1;
            IP[i + 1] >>= 1;
        }
    }
}

void insert(int cd, int times)
{
    //printf("%d\n", times);
    int pos = 1;
    for (int i = 1; i <= cd; i++)
    {
        if (tree[pos][map[i]] == 0)
        {
            tree[pos][map[i]] = ++vnum;
        }
        pos = tree[pos][map[i]];
    }
    //printf("%d\n", vnum);
    tree[pos][2] = times;
}

int search()
{
    int pos = 1;
    int stacknum = 0;
    int stack[40];
    for (int i = 1; i <= 34; i++)
    {

        if ((tree[pos][2] != 0) && (tree[pos][2] <= r))
        {
            while ((stacknum > 0) && (tree[pos][2] <= stack[stacknum]))
            {
                stacknum--;
            }
            stacknum++;
            stack[stacknum] = tree[pos][2];
        }
        if (tree[pos][map[i]] == 0)
            break;
        pos = tree[pos][map[i]];
    }

    int ans = 0;
    for (int i = stacknum; i >= 1; i--)
    {
        if (stack[i] >= l)
            ans++;
        else
            break;
    }
    return ans;
}

int main()
{
    vnum = 1;
    scanf("%d\n", &m);
    int addnum = 0;
    for (int i = 1; i <= m; i++)
    {
        ch = getchar();
        while (ch != 'A' && ch != 'Q')
            ch = getchar();
        if (ch == 'A')
        {
            addnum++;
            scanf("%s", A);
            int len = strlen(A);
            pointa = 0;
            nownum = 0;
            block = 1;
            while (A[pointa] != '/')
            {
                if (A[pointa] == '.')
                {
                    IP[block] = nownum;
                    nownum = 0;
                    block++;
                    pointa++;
                }
                else
                {
                    nownum = nownum * 10 + (A[pointa] - '0');
                    pointa++;
                }
            }
            IP[block] = nownum;
            nownum = 0;
            block++;
            pointa++;
            while (pointa < len)
            {
                nownum = nownum * 10 + (A[pointa] - '0');
                pointa++;
            }
            YM = nownum;
            //printf("%d\n", YM);
            convert();
            /*for (int j = 1; j <= 32; j++)
            {
                printf("%d", map[j]);
            }
            printf("\n");*/
            insert(YM, addnum);
        }
        else
        {
            scanf("%s %d %d", A, &l, &r);
            //printf("%d %d\n", l, r);
            int len = strlen(A);
            pointa = 0;
            nownum = 0;
            block = 1;
            while (pointa < len)
            {
                if (A[pointa] == '.')
                {
                    IP[block] = nownum;
                    nownum = 0;
                    block++;
                    pointa++;
                }
                else
                {
                    nownum = nownum * 10 + (A[pointa] - '0');
                    pointa++;
                }
            }
            IP[block] = nownum;
            convert();
            /*for (int i = 1; i <= 32; i++)
            {
                printf("%d", map[i]);
            }
            printf("\n");*/
            printf("%d\n", search());
        }
    }
    system("pause");
    return 0;
}