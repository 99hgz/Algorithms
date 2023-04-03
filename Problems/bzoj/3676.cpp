#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

char st[300010],a[700010];
int n,maxR,p,f[700010],stp2samp[300010],ans;

namespace SAM{
    int len[600010],fa[600010],_root,last,cnt,a[600010][27];
    int c[600010],pos[600010],_st[600010][20],sz[600010];
    void init(){
        last=_root=++cnt;
    }
    int extend(int ch){
        int p=last;
        int np=last=++cnt;
        sz[np]=1;
        len[np]=len[p]+1;
        for(;!a[p][ch];p=fa[p])a[p][ch]=np;
        if(!p)
            fa[np]=_root;
        else{
            int q=a[p][ch];
            if(len[q]==len[p]+1)
                fa[np]=q;
            else{
                int nq=++cnt;
                len[nq]=len[p]+1;
                fa[nq]=fa[q];
                fa[q]=fa[np]=nq;
                memcpy(a[nq],a[q],sizeof a[nq]);
                for(;a[p][ch]==q;p=fa[p])a[p][ch]=nq;
            }
        }
        return np;
    }
    void build(){
        for ( int i = 1; i <= cnt; i++ )
            c[len[i]]++;
        for ( int i = 1; i <= cnt; i++ )
            c[i] += c[i - 1];
        for ( int i = 1; i <= cnt; i++ )
            pos[c[len[i]]--] = i;
        for ( int i = cnt; i >= 1; i-- ){
            int p=pos[i];
            sz[fa[p]]+=sz[p];
        }
    }
    void init_st(){
        for(int i=1;i<=cnt;i++)
            _st[i][0]=fa[i];
        for(int i=1;i<=19;i++)
            for(int j=1;j<=cnt;j++)
                _st[j][i]=_st[_st[j][i-1]][i-1];
    }
    int query(int p,int stlen){
        for(int i=19;i>=0;i--){
            if(_st[p][i]==0) continue;
            if(len[_st[p][i]]>=stlen)
                p=_st[p][i];
        }
        return p;
    }
    int work(int l,int r){
        int cur=_root;
        for(int i=l;i<=r;i++)
            cur=a[cur][st[i]-'a'];
        return cur;
    }
}

int main() {

    scanf("%s",st+1);
    int stlen=strlen(st+1);
    
    a[0]='@';
    for(int i=1;st[i];i++)
        a[++n]='#',a[++n]=st[i];
    a[++n]='#';
    a[n+1]='*';
    for(int i=1;i<=n;i++){
        f[i]=(i<maxR)?min(f[2*p-i],maxR-i+1):1;
        while(i-f[i]>0&&i+f[i]<=n&&a[i-f[i]]==a[i+f[i]])f[i]++;
        if(i+f[i]-1>maxR) maxR=i+f[i]-1,p=i;
    }

    SAM::init();
    for(int i=1;i<=stlen;i++)
        SAM::extend(st[i]-'a');

    SAM::build();
    SAM::init_st();
    
    int cur=SAM::_root;
    for(int i=1;i<=stlen;i++){
        cur=SAM::a[cur][st[i]-'a'];
        stp2samp[i]=cur;
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
        if(i&1){
            int len=f[i]-1;
            if(!len) continue;
            int L=(i/2)-(len/2)+1,R=(i/2)+(len/2);
            ll ts=SAM::sz[SAM::query(stp2samp[R],R-L+1)];
            if(ts*len>ans) ans=ts*len;
            //printf("st[%d..%d]=%d\n", L,R,ts);
        }else{
            int len=f[i]-1;
            if(!len) continue;
            int L=(i/2)-(len/2),R=(i/2)+(len/2);
            ll ts=SAM::sz[SAM::query(stp2samp[R],R-L+1)];
            if(ts*len>ans) ans=ts*len;
            //printf("st[%d..%d]=%d\n", L,R,ts);
        }
    printf("%lld\n", ans);
 //   system("pause");
    return 0;
}
