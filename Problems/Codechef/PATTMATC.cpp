#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

char s1[100010],s2[100010];
int fail[100010],s1len;
int len2,cnt;

struct KMP{
    int L,R,len,cur;
    void init(int l,int r){
        //printf("init:%d %d\n", l,r);
        len=r-l+1;
        L=l,R=r,cur=l-1;
        fail[l]=l-1;
        for(int i=l+1;i<=r;i++){
            int j=fail[i-1];
            while(j>=l&&s1[j+1]!=s1[i])j=fail[j];
            if(j+1>=l&&s1[j+1]==s1[i])fail[i]=j+1;
            else fail[i]=l-1;
        }
    }
    int lastmatchpos,it;
    int match(int l){
        if(lastmatchpos>=l) return lastmatchpos;
        if(it>len2) return -1;
        it++;
        for(;it<=len2;it++){
            while(cur>=L&&s1[cur+1]!=s2[it])cur=fail[cur];
            if(cur+1>=L&&s1[cur+1]==s2[it])cur++;
            if(cur==R){
                cur=fail[cur];
                lastmatchpos=it-len+1;
                if(lastmatchpos>=l)
                    return lastmatchpos;
            }
        }
        return -1;
    }
}block[510];



int main() {
    freopen("data.in","r",stdin);
    int T;
    scanf("%d", &T);
    while(T--){
        for(int i=1;i<=cnt;i++)
            block[i]=(KMP){0,0,0,0,0,0};
        for(int i=1;i<=s1len;i++)
            fail[i]=0;
        len2=s1len=cnt=0;
        scanf("%s", s1+1);
        scanf("%s", s2+1);
        len2=strlen(s2+1);
        int l=0x3f3f3f3f;
        s1len=strlen(s1+1);
        for(int r=1;r<=s1len;r++){
            if(s1[r]!='*')
                l=min(l,r);
            if(r==s1len||s1[r+1]=='*')
                if(l!=0x3f3f3f3f){
                    block[++cnt].init(l,r);
                    l=0x3f3f3f3f;
                }
        }
        //printf("debug:%d\n", block[2].match(8));
        for(int i=1;i<=len2;i++){
            int cur=i;
            for(int j=1;j<=cnt;j++){
                int tmp=block[j].match(cur);
                //printf("%d %d %d\n", j,cur,tmp);
                if(tmp==-1){
                    cur=-1;
                    break;
                }
                cur=tmp+block[j].len;
            }
            printf("%d%c", (cur==-1)?-1:(max(cur-1,i)),i==len2?'\n':' ');
        }
    }
    system("pause");
    return 0;
}