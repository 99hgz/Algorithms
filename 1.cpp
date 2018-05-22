#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int vis[10000];
int main() {
	int cnt=2009;
	while(cnt>3){
		int fl=0;
		for (int i = 1; i <= 2009; i++) {
			if(!vis[i])
				fl++;
			if(fl==3)
				vis[i]=1,cnt--,fl=0;
		}
	}
	for (int i = 1; i <= 2009; i++) 
		if(!vis[i])
			printf("%d\n", i);
	system("pause");
	return 0;
}