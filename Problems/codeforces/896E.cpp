#pragma GCC optimize("Ofast,no-stack-protector")
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
struct ano{
	char a[1<<25],*s;
	char b[1<<25],*t;
	ano():s(a),t(b){
		a[fread(a,1,sizeof a,stdin)]=0;
	}
	~ano(){fwrite(b,1,t-b,stdout);}
	operator int(){
		int x=0;
		while(*s<48)++s;
		while(*s>32)
			x=x*10+*s++-48;
		return x;
	}
	void out(int x){
		static char c[12];
		char*i=c;
		if(!x)*t++=48;
		else{
			while(x){
				int y=x/10;
				*i++=x-y*10+48,x=y;
			}
			while(i!=c)*t++=*--i;
		}
		*t++=10;
	}
}buf;
typedef long long ll;
int n,q,a[100004],op,l,r,ans;
float x;
int main() {
    n=buf,q=buf;
    for (register int i = 1; i <= n; i++) 
        a[i]=buf;
    for (register int i = 1; i <= q; i++){
        op=buf,l=buf,r=buf,x=buf;
        if(op==1){
            register int j=l;
            for(;j+7<=r;j+=8){
                a[j]-=(a[j]>x)*x;
                a[j+1]-=(a[j+1]>x)*x;
                a[j+2]-=(a[j+2]>x)*x;
                a[j+3]-=(a[j+3]>x)*x;
                a[j+4]-=(a[j+4]>x)*x;
                a[j+5]-=(a[j+5]>x)*x;
                a[j+6]-=(a[j+6]>x)*x;
                a[j+7]-=(a[j+7]>x)*x;
            }
            for(;j<=r;j++)
                a[j]-=(a[j]>x)*x;
        }else{
            ans=0;
            register int j=0;
            for(j=l;j+7<=r;j+=8)
                ans+=(a[j]==x)+(a[j+1]==x)+(a[j+2]==x)+(a[j+3]==x)+(a[j+4]==x)+(a[j+5]==x)+(a[j+6]==x)+(a[j+7]==x);
            for(;j<=r;j++)
                ans+=(a[j]==x);
            printf("%d\n", ans);
        }
    } 
    //system("pause");
    return 0;
}