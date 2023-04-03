#define La 1<<8
#define Lb 1<<9
#define Lc 1<<10
#define Ld 1<<11
#define Le 1<<12
#define Lf 1<<13
#define Lg 1<<14

#define LightOn(x, ...) L##x || LightOn(__VA_ARGS__)
int num2light[10]={
	LightOn(a,b,c,d,e,f,g)	
}

int main(){
	
}