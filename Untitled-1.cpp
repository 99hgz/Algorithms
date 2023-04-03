#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

unsigned long long M=1e16;
int main(){
	int n;cin>>n;
	if (n<=2){
		if (n==0) cout<<0<<endl; else
		if (n==1) cout<<3<<endl;
		 else cout<<9<<endl;
		return 0;
	}
	unsigned long long x,y,z;
	x=3;y=9;n-=2;
	bool ifB=0;
	while (n--){
		if (y+y+x+x>=M) ifB=1;
		z=((y+y)%M+(x+x)%M)%M;
		x=y,y=z;
	}
	if (ifB){
		M=(long long)1e10;
		cout<<"......"<<z%M<<endl;
	} else cout<<z<<endl;
	system("pause");
	return 0;
}
