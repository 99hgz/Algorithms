#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int n,q,lg[100010],a[100010],x,y;

namespace rmqmx{
    int block,bnum;
    int mx[100010][17],bmx[100010][17],bpre[100010][17],bsuc[100010][17];
    void init(int *a){
        block=lg[n];
        bnum=1;
        int bbid=0;
        for(int i=1;i<=n;i++){
            mx[i][0]=a[i];
            bbid++;
            if(bbid>block)bbid=1,bnum++;
            bmx[bnum][0]=max(bmx[bnum][0],a[i]);
            bpre[bnum][bbid]=max(bpre[bnum][bbid-1],a[i]);
        }
        for(int j=1;j<=lg[bnum];j++)
            for(int i=1;i<=bnum;i++)
                if (i + (1 << j) - 1 <= bnum)
                    bmx[i][j] = max(bmx[i][j - 1], bmx[i + (1 << (j - 1))][j - 1]);
        for(int i=1;i<=bnum;i++){
            int ed=i*block;
            for(int j=ed,pos=1;j>ed-block;j--,pos++)
                bsuc[i][pos]=max(bsuc[i][pos-1],a[j]);
        }
        for(int j=1;j<=lg[block];j++)
            for(int i=1;i<=n;i++)
                if(i+(1<<j)-1<=n)
                    mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
    }
    int query(int x,int y){
        int xb=(x-1)/block+1,yb=(y-1)/block+1;
        if(yb>xb){
            int res=max(bsuc[xb][xb*block-x+1],bpre[yb][y-(yb-1)*block]);
            xb++,yb--;
            if(yb>=xb){
                int k=lg[yb-xb+1];
                res=max(res,max(bmx[xb][k],bmx[yb-(1<<k)+1][k]));
            }
            return res;
        }else{
            int k=lg[y-x+1];
            return max(mx[x][k],mx[y-(1<<k)+1][k]);
        }
    }
}

namespace rmqmn{
    int block,bnum;
    int mx[100010][17],bmx[100010][17],bpre[100010][17],bsuc[100010][17];
    void init(int *a){
        block=lg[n];
        bnum=1;
        bmx[bnum][0]=0x3f3f3f3f;
        int bbid=0;
        for(int i=1;i<=n;i++){
            mx[i][0]=a[i];
            bbid++;
            if(bbid>block){bbid=1,bnum++;bmx[bnum][0]=0x3f3f3f3f;bpre[bnum][0]=0x3f3f3f3f;}
            bmx[bnum][0]=min(bmx[bnum][0],a[i]);
            bpre[bnum][bbid]=min(bpre[bnum][bbid-1],a[i]);
        }
        for(int j=1;j<=lg[bnum];j++)
            for(int i=1;i<=bnum;i++)
                if (i + (1 << j) - 1 <= bnum)
                    bmx[i][j] = min(bmx[i][j - 1], bmx[i + (1 << (j - 1))][j - 1]);
        for(int i=1;i<=bnum;i++){
            int ed=i*block;
            bsuc[i][0]=0x3f3f3f3f;
            for(int j=ed,pos=1;j>ed-block;j--,pos++)
                bsuc[i][pos]=min(bsuc[i][pos-1],a[j]);
        }
        for(int j=1;j<=lg[block];j++)
            for(int i=1;i<=n;i++)
                if(i+(1<<j)-1<=n)
                    mx[i][j]=min(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
    }
    int query(int x,int y){
        int xb=(x-1)/block+1,yb=(y-1)/block+1;
        if(yb>xb){
            int res=min(bsuc[xb][xb*block-x+1],bpre[yb][y-(yb-1)*block]);
            xb++,yb--;
            if(yb>=xb){
                int k=lg[yb-xb+1];
                res=min(res,min(bmx[xb][k],bmx[yb-(1<<k)+1][k]));
            }
            return res;
        }else{
            int k=lg[y-x+1];
            return min(mx[x][k],mx[y-(1<<k)+1][k]);
        }
    }
}

const int ch_top=4e6+3;
char ch[ch_top],*now_r=ch-1,*now_w=ch-1;
inline int read(){
    while(*++now_r<'0');
    int x=*now_r-'0';
    while(*++now_r>='0')x=x*10+*now_r-'0';
    return x;
}
inline void write(int x){
    static char st[20];static int top;
    while(st[++top]='0'+x%10,x/=10);
    while(*++now_w=st[top],--top);
    *++now_w='\n';
}

int main() {
    
    fread(ch,1,ch_top,stdin);
    //scanf("%d%d", &n,&q);
    n=read(),q=read();
    for(int i=2;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)
        //scanf("%d", &a[i]);
        a[i]=read();
    rmqmx::init(a);
    rmqmn::init(a);
    for(int i=1;i<=q;i++){
        x=read(),y=read();//scanf("%d%d", &x,&y);
        //int res1=rmqmx::query(x,y);//res2=rmqmn::query(x,y);
        //res1=1;
        //printf("%d\n", res1);
        //printf("%d\n", rmqmx::query(x,y)-rmqmn::query(x,y));
        write(rmqmx::query(x,y)-rmqmn::query(x,y));
    }
    fwrite(ch,1,now_w-ch,stdout);
    //system("pause");
    return 0;
}