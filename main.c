#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() 
{
   /* Write you code here. */
   FILE *fp1,*fp2;
   unsigned char a;
   int b;
   int n=0,i;
   int count=0;
   fp1=fopen("a.dat","rb");
   fp2=fopen("b.txt","w");
   scanf("%x",&b);
   while(fread(&a,sizeof(unsigned char),1,fp1)!=0){
   	if(b==a){
   		count++;
	   }
   }
	fprintf(fp2,"%d\n",count);
	fclose(fp1);
	fclose(fp2);
}
