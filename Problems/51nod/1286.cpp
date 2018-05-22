#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int last,cnt,root,a[2000010][26],len[2000010],fa[2000010],fail[2000010],stlen;
vector<int> ans;
char s1[2000010];

void init(){
    int len=strlen(s1+1);
    fail[1]=0;
    for(int i=2;i<=len;i++){
        int j=fail[i-1];
        while(j&&s1[j+1]!=s1[i])j=fail[j];
        if(s1[j+1]==s1[i])fail[i]=j+1;
        else fail[i]=0;
    }
}

void extend(int ch)
{
    int p = last, np = last = ++cnt;
    len[np] = len[p] + 1;
    fa[np]=0;
    while (p && !a[p][ch])
        a[p][ch] = np, p = fa[p];
    if (!p)
        fa[np] = root;
    else
    {
        int q = a[p][ch];
        if (len[q] == len[p] + 1)
            fa[np] = q;
        else
        {
            int nq = ++cnt;
            fa[nq]=0;
            len[nq] = len[p] + 1;
            memcpy(a[nq], a[q], sizeof a[q]);
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while (p && a[p][ch] == q)
                a[p][ch] = nq, p = fa[p];
        }
    }
}

bool check(int mid){
    last=cnt=root=1;
    memset(a,0,sizeof a);
    for(int i=ans[mid]+1;i<=stlen-ans[mid];i++)
        extend(s1[i]-'a');
    int cur=root;
    for(int i=1;i<=ans[mid];i++){
        cur=a[cur][s1[i]-'a'];
        if(cur==0) return false;
    }
    return true;
}

int main() {
    scanf("%s", s1+1);
    init();
    stlen=strlen(s1+1);
    int cur=stlen;
    while(cur){
        ans.push_back(cur);
        cur=fail[cur];
    }
    sort(ans.begin(),ans.end());
    int l=0,r=ans.size()-1,ans1=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        //printf("len=%d\n", ans[mid]);
        if(check(mid))
            l=mid+1,ans1=mid;
        else
            r=mid-1;
    }
    printf("%d\n", (ans1==-1)?0:ans[ans1]);
    system("pause");
    return 0;
}