#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;
typedef long long ll;

class Random
{
  public:
    static void InitSeed() { srand(time(0)); } // set random seed

    static float Value() { return (float)rand() / RAND_MAX; } // get a random value between [0.0, 1.0]

    static int Range(int min, int max) // return a int random value between [min, max)
    {
        return min + (max - min) * Value();
    }

    static float Range(float min, float max) // return a float random value between [min, max]
    {
        return min + (max - min) * Value();
    }
};
int a[100010];
int main()
{
    freopen("lln.in", "w", stdout);
    Random r;
    r.InitSeed();
    int sl = 100000;
    printf("%d\n", sl);
    for (int i = 1; i <= sl; i++)
    {
        a[i] = r.Range(0, 1000000);
        printf("%d ", a[i]);
    }
    printf("\n");
    int left, right, mid, kind;
    for (int i = 0; i < sl; i++)
    {
        kind = r.Range(0, 5);
        if (kind < 2)
        {
            left = r.Range(0, sl);
            right = r.Range(left, sl + 1);
            mid = r.Range(left, right + 1);
            printf("2 %d %d %d\n", left, right, a[mid]);
        }
        else
        {
            left = r.Range(0, sl);
            right = r.Range(left, sl + 1);
            printf("1 %d %d %d\n", left, right, r.Range(1, 100000));
        }
    }
    //system("pause");
    fclose(stdout);
    return 0;
}