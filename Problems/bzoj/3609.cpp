#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll n,m;
int main()
{
	int T;
	scanf("%d",&T);
	while (T--) 
	{
		scanf("%lld%lld",&n,&m);
        ll ans=n/m*(m-1);
        if (n%m) ans+=n%m-1;
		puts((ans&1)?"0":"1");
	}
    system("pause");
	return 0;
}