{
 * @key word:树状数组
 * @已测试:POJ - 2352
 * @Author: hgz 
 * @Date: 2017-04-23 12:35:51 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-23 12:35:51 
}
var
ans,a:array[0..32009]of longint;
n,i,j,_x,_y:longint;
function lowbit(x:longint):longint;
begin
	exit(x and (-x));
end;

procedure update(x,v:longint);
begin
	while x<=32009 do
	begin
		a[x]:=a[x]+v;
		x:=x+lowbit(x);
	end;
end;

function get(x:longint):longint;
begin
	get:=0;
	while x>0 do 
	begin
		get:=get+a[x];
		x:=x-lowbit(x);
	end;
end;

begin
readln(n);
for i:=1 to n do 
	begin
	read(_x,_y);
	inc(ans[get(_x+1)]);
	update(_x+1,1);
	end;
for i:=0 to n-1 do 
	writeln(ans[i]);
end.