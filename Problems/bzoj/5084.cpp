#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;


struct kv{
    int key,val;
};
struct OPER{
    int op,ch,id,ans,last;
    vector<kv>vec;
};
stack<OPER> S;
const int MAXN=200010;
char st[MAXN];


    int p,q,np,nq,ans;
    int cnt=1,last=1;
    int a[MAXN][26],len[MAXN],fa[MAXN];
    void extend(int ch,int id){
        S.push((OPER){3,ch,id,ans,last});
        OPER cg1=(OPER){2,ch,id,-1,-1};
        p=last,np=last=++cnt;len[np]=len[p]+1;
        while(!a[p][ch]&&p){cg1.vec.push_back((kv){p,a[p][ch]});a[p][ch]=np,p=fa[p];}
        S.push(cg1);
        if (!p)fa[np]=1;
        else {
            q=a[p][ch];
            if (len[q]==len[p]+1) fa[np]=q;
            else{
                nq=++cnt,len[nq]=len[p]+1;
                memcpy(a[nq],a[q],sizeof a[q]);
                OPER cg2=(OPER){1,ch,id,-1,-1};
                cg2.vec.push_back((kv){np,fa[np]});
                cg2.vec.push_back((kv){q,fa[q]});
                S.push(cg2);
                fa[nq]=fa[q];
                fa[np]=fa[q]=nq;
                OPER cg3=(OPER){2,ch,id,-1,-1};
                while(p&&a[p][ch]==q) {cg3.vec.push_back((kv){p,a[p][ch]});a[p][ch]=nq,p=fa[p];}
                S.push(cg3);
            }
        }
        ans=ans+len[np]-len[fa[np]];
    }

int main() {
    scanf("%s", st+1);
    int stlen=strlen(st+1);
    for (int i = 1; i <= stlen; i++) {
        if (st[i]=='-'){
            int k=S.top().id;
            while(!S.empty()&&S.top().id==k){
                OPER tmp=S.top();
                S.pop();
                if (tmp.op==1)
                    for(int j=0;j<tmp.vec.size();j++)
                        fa[tmp.vec[j].key]=tmp.vec[j].val;
                else if (tmp.op==2)
                    for(int j=0;j<tmp.vec.size();j++)
                        a[tmp.vec[j].key][tmp.ch]=tmp.vec[j].val;
                else if (tmp.op==3)
                    ans=tmp.ans,last=tmp.last;
            }
        }else{
            extend(st[i]-'a',i);
        }
        printf("%d\n", ans);
    }
    system("pause");
    return 0;
}