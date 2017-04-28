{
 * @key word: 矩阵乘法,快速幕
 * @已测试:http://www.yyhs.net.cn:801/JudgeOnline/problem.php?cid=1187&pid=2
 * @Author: hgz 
 * @Date: 2017-04-22 13:39:10 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-22 13:39:10 
}
type
	matrix=array[1..50,1..50] of int64;
var
	matrix1:matrix;
	i,j,k,n,cd,s,ans:longint;
	
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

begin
	read(cd,n);
	for i:=1 to cd do
		for j:=1 to cd do
			read(matrix1[i,j]);
	read(s,ans);
	matrix1:=matrix_power(matrix1,n,10007);
	writeln(matrix1[s,ans] mod 10007);
end.
