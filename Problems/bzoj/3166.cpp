#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

set<int> st;
int n,a[100010],Hash[100010],Root[100010],Last[100010],Last2[100010],Next[100010],Next2[100010];
vector<int>vec[100010];

int check(set<int>::iterator it,int op){
    if (it!=st.end()) return *it;
    return (op==1)?n+1:-1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        Hash[i]=a[i];
        Root[i]=Root[i-1];
        //insert(Root[i],30,a[i]);
    }
    sort(Hash+1,Hash+1+n);
    int tn=unique(Hash+1,Hash+1+n)-Hash-1;
    for (int i = 1; i <= n; i++){
        a[i]=lower_bound(Hash+1,Hash+1+tn,a[i])-Hash;
        vec[a[i]].push_back(i);
    }
    for (int i = tn; i >= 1; i--){
        if (i!=tn){
            for(int it=0;it<vec[i].size();it++){
                int pos=vec[i][it];
                set<int>::iterator it1=st.lower_bound(pos),it2=it1;
                Next[pos]=check(it1,1)-1;
                if (it1!=st.end()){
                    it1++;
                    Next2[pos]=check(it1,2);
                }else Next2[pos]=-1;
                it1=it2;
                if (it1!=st.begin()){
                    it1--;
                    Last[pos]=(*it1)+1;
                    if (it1!=st.begin()){
                        it1--;
                        Last2[pos]=*it1;
                    }else Last2[pos]=-1;
                }else Last[pos]=1,Last2[pos]=-1;
            }
        }
        for(int it=0;it<vec[i].size();it++){
            int pos=vec[i][it];
            st.insert(pos);
        }
    }

    for (int i = 1; i <= n; i++)
        printf("%d %d %d %d\n", Last2[i],Last[i],Next[i],Next2[i]);
    system("pause");
    return 0;
}