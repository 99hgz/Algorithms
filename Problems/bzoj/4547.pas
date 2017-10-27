type
	matrix=array[1..4,1..4] of int64;
var
	matrix1:matrix;
	k,i,j,cd:longint;
    n,s,max1,max2:int64;
    a:array[1..100005]of int64;
	ans:int64;
function matrix_mod_mul(x,y:matrix;p:longint):matrix;
var
	ans:matrix;
begin
	fillchar(ans,sizeof(ans),0);
	for k:=1 to cd do
		for i:=1 to cd do
			for j:=1 to cd do
			begin
				ans[i,j]:=ans[i,j] mod p;
				x[i,k]:=x[i,k] mod p;
				y[k,j]:=y[k,j] mod p;
				ans[i,j]:=(ans[i,j]+((x[i,k]*y[k,j]) mod p))mod p;
			end;
	exit(ans);
end;

function matrix_power(_origin:matrix;b,p:longint):matrix;
var
    ans:matrix;
begin
	if b=1 then exit(_origin);
	ans:=matrix_power(_origin,b shr 1,p);
	ans:=matrix_mod_mul(ans,ans,p);
	if (b and 1=1)then
		exit(matrix_mod_mul(ans,_origin,p))
	else
		exit(ans);
end;

procedure solve(times:longint);
begin
    matrix1:=matrix_power(matrix1,times+1,10000007);
	//writeln(matrix1[1,1]+matrix1[1,2]-2,' ',matrix1[2,1]+matrix1[2,2]-1);
	ans:=(((ans+(matrix1[1,1]+matrix1[1,2]-2)*max1) mod 10000007)+(matrix1[2,1]+matrix1[2,2]-1)*max2)mod 10000007;
end;

begin
	read(n,k);
    max1:=-maxlongint;
    max2:=-maxlongint;
    for i:=1 to n do 
        begin
            read(a[i]);
            if (a[i]>=max1) then begin
                max2:=max1;
                max1:=a[i];
            end
            else if (a[i]>max2) then max2:=a[i];
            ans:=ans+a[i];
			ans:=ans mod 10000007;
        end;
    //ans:=ans-max1-max2;
    cd:=2;
    matrix1[1,1]:=1;
    matrix1[1,2]:=1;
    matrix1[2,1]:=1;
    for i:=1 to k do 
        if (max2>=0) then begin
            solve(k-i+1);
            break;
        end
        else begin
            max2:=max1+max2;
            ans:=ans+max2;
			ans:=ans mod 10000007;
        end;
    writeln(ans);
    
	
    
end.
