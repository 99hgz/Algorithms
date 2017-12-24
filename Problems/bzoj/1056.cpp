#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;

typedef pair<ll, ll> Rootpair;
#define mp make_pair
ll tot, opt, x, Root, n;

struct VAL
{
    ll score, inserttime;
};

bool operator==(VAL a, VAL b)
{
    return (a.score == b.score) && (a.inserttime == b.inserttime);
}

bool operator>(VAL a, VAL b)
{
    if (a.score > b.score)
        return false;
    if (a.score == b.score && a.inserttime < b.inserttime)
        return false;
    return true;
}

struct TREENODE
{
    VAL val;
    ll fix, Hash, size, ch[2];
} Tree[300010];

ll newnode(VAL v, ll Hash)
{
    tot++;
    Tree[tot] = (TREENODE){v, rand(), Hash, 1};
    Tree[tot].ch[0] = Tree[tot].ch[1] = 0;
    return tot;
}

void up(ll rt)
{
    Tree[rt].size = Tree[Tree[rt].ch[0]].size + Tree[Tree[rt].ch[1]].size + 1;
}

void merge(ll &rt, ll L, ll R)
{
    if (!L || !R)
    {
        rt = L + R;
        return;
    }
    if (Tree[L].fix < Tree[R].fix)
        rt = L, merge(Tree[rt].ch[1], Tree[rt].ch[1], R);
    else
        rt = R, merge(Tree[rt].ch[0], L, Tree[rt].ch[0]);
    up(rt);
}

Rootpair split(ll rt, ll kth)
{
    if (!kth)
        return mp(0, rt);
    ll ls = Tree[rt].ch[0], rs = Tree[rt].ch[1];
    if (kth == Tree[ls].size)
    {
        Tree[rt].ch[0] = 0;
        up(rt);
        return mp(ls, rt);
    }
    if (kth == Tree[ls].size + 1)
    {
        Tree[rt].ch[1] = 0;
        up(rt);
        return mp(rt, rs);
    }
    if (kth < Tree[ls].size)
    {
        Rootpair tmp = split(ls, kth);
        Tree[rt].ch[0] = tmp.second;
        up(rt);
        return mp(tmp.first, rt);
    }
    Rootpair tmp = split(rs, kth - Tree[ls].size - 1);
    Tree[rt].ch[1] = tmp.first;
    up(rt);
    return mp(rt, tmp.second);
}

ll getrank(VAL val)
{
    ll res = 0, tmp = 0x7f7f7f7f, rt = Root;
    while (rt)
    {
        if (val == Tree[rt].val)
            tmp = min(tmp, res + Tree[Tree[rt].ch[0]].size + 1);
        if (val > Tree[rt].val)
            res += Tree[Tree[rt].ch[0]].size + 1, rt = Tree[rt].ch[1];
        else
            rt = Tree[rt].ch[0];
    }
    return tmp == 0x7f7f7f7f ? res : tmp;
}

ll findkth(ll val)
{
    ll rt = Root;
    while (1)
    {
        if (Tree[Tree[rt].ch[0]].size + 1 == val)
            return rt;
        if (Tree[Tree[rt].ch[0]].size > val - 1)
            rt = Tree[rt].ch[0];
        else
            val -= Tree[Tree[rt].ch[0]].size + 1, rt = Tree[rt].ch[1];
    }
}

void insert(VAL val, ll Hash)
{
    ll rt = newnode(val, Hash);
    ll Rank = getrank(val);
    Rootpair tmp = split(Root, Rank);
    merge(Root, tmp.first, rt);
    merge(Root, Root, tmp.second);
}

void del(VAL val)
{
    ll Rank = getrank(val);
    Rootpair tmp1 = split(Root, Rank);
    Rootpair tmp2 = split(tmp1.first, Rank - 1);
    merge(Root, tmp2.first, tmp1.second);
}
char op[1000];
ll getHash()
{
    ll len = strlen(op);
    ll res = 0;
    for (ll i = 1; i < len; i++)
        res = (res * 29 + op[i] - 'A' + 1);
    return (ll)res;
}
typedef vector<char> vcc;
map<ll, VAL> exist;
map<ll, vcc> hash2name;
ll timestamp;
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%s", op);
        if (op[0] == '?')
        {
            if ('0' <= op[1] && op[1] <= '9')
            {
                ll len = strlen(op);
                ll cd = 0;
                for (ll j = 1; j <= len - 1; j++)
                    cd = cd * 10 + op[j] - '0';
                ll oldrt = 0;
                for (ll j = cd; j <= cd + 9; j++)
                {
                    ll rt = findkth(j);
                    if (rt == 0)
                        break;
                    if (oldrt)
                    {
                        ll len2 = hash2name[Tree[oldrt].Hash].size();
                        for (ll i = 0; i < len2; i++)
                            printf("%c", hash2name[Tree[oldrt].Hash][i]);
                        printf(" ");
                    }
                    oldrt = rt;
                }
                if (oldrt)
                {
                    ll len2 = hash2name[Tree[oldrt].Hash].size();
                    for (ll i = 0; i < len2; i++)
                        printf("%c", hash2name[Tree[oldrt].Hash][i]);
                }
                printf("\n");
            }
            else
            {
                ll Hash = getHash();
                printf("%lld\n", getrank(exist[Hash]));
            }
        }
        else
        {
            ll val;
            scanf("%lld", &val);
            ll Hash = getHash();
            if (exist[Hash].inserttime)
                del(exist[Hash]);
            ll len = strlen(op);
            if (!exist[Hash].inserttime)
                for (ll i = 1; i < len; i++)
                    hash2name[Hash].push_back(op[i]);
            //printf("insert:Hash=%d\n", Hash);
            ++timestamp;
            exist[Hash] = (VAL){val, timestamp};
            insert(exist[Hash], Hash);
        }
    }
    // system("pause");
    return 0;
}