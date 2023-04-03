#include<bits/stdc++.h>
using namespace std;
string s1[5101],s[10011];
int n,m,bb[10001],cc[10001],b[501][501],st=1,ts=1,s_x,s_y,e_x,e_y,times[100011],vis[501][501],q_x[10001],q_y[10011];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int bfs(){
	int head=0,tail=1;
	q_x[1]=s_x;
	q_y[1]=s_y;
	times[1]=0;
	vis[s_x][s_y]=1;
	while(head<tail){
		head++;
		int x=q_x[head],y=q_y[head];
		if(x==e_x&&y==e_y)return times[head];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				s[i][j]=s1[i][j];
			}
		}
		if(times[head]%2==1&&s[i][j]=='-'||times[head]%2==0&&s[i][j]='|'){
			for(int i=1;i<st;i++){
				if(s[bb[i]][cc[i]]=='-'){
					if(dx[i]==0){
						x=x,y=y;
						times[head]++;
					}
					else s[bb[i]][cc[i]]='|';
				}
				else {
					if(dy[i]==0)
					s[bb[i]][cc[i]]='-';
				}
			}
		}
		for(int i=0;i<4;i++){
			int n_x=x+dx[i],n_y=y+dy[i];
			if(s[n_x][n_y]=='|')n_y--;
			else if(s[n_x][n_y]=='-')n_x++;
			if(n_x<1||n_x>n||n_y<1||n_y>m)continue;
			if(vis[n_x][n_y]==1)continue;
			tail++;
			q_x[tail]=n_x;
			q_y[tail]=n_y;
			times[tail]=times[head]+1;
			vis[n_x][n_y]=1;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s1[i]);
		for(int j=1;j<=m;j++){	
			if(s[i][j]=='-'||s[i][j]=='|'){
				bb[st]=i;
				cc[st]=j;
				st++;
			}else if(s[i][j]=='S')s_x=i,s_y=j;
			else if(s[i][j]=='T')e_x=i,e_y=j;
		}
	}
	printf("%d",bfs());
	return 0;
} 