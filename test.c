#include<stdio.h> 
#include<stdlib.h> 

long double f(long double n){
	 long double al=1,a2=1,t; 
	 for (int i=3;i<=n;i++){ 
		t=a2; a2=al+a2; al=t; 
	}
	return a2; 
}
int main(){
	printf("g=%.8Lf",f(100)/f(101)); 
	system("pause");
}
