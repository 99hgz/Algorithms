{
 * @key word:RMQ，区间最值，ST算法
 * @已测试:POJ - 3264
 * @Author: hgz 
 * @Date: 2017-04-23 13:02:10 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-23 13:02:10 
}
var
f2,f:array[0..100000,0..20]of longint;
n,i,tmp1,tmp2,m:longint;
function min(a,b:longint):longint;
begin
	if a>b then exit(b) else exit(a);
end;
function max(a,b:longint):longint;
begin
	if a<b then exit(b) else exit(a);
end;
procedure max_init();
	var 
	i,j,cd:longint;
	begin
	cd:=trunc(ln(n)/ln(2));
	for i:=1 to cd do 
		for j:=1 to n do
		f[j,i]:=max(f[j,i-1],f[j+1<<i>>1,i-1]);
	end;
function max_query(s,t:longint):longint;
	var
	cd:longint;
	begin
	cd:=trunc(ln(t-s+1)/ln(2));
	exit(max(f[s,cd],f[t-(1<<cd)+1,cd]));
	end;
procedure min_init();
	var 
	i,j,cd:longint;
	begin
	cd:=trunc(ln(n)/ln(2));
	for i:=1 to cd do 
		for j:=1 to n do
		f2[j,i]:=min(f2[j,i-1],f2[j+1<<i>>1,i-1]);
	end;
function min_query(s,t:longint):longint;
	var
	cd:longint;
	begin
	cd:=trunc(ln(t-s+1)/ln(2));
	exit(min(f2[s,cd],f2[t-(1<<cd)+1,cd]));
	end;
begin
	readln(n,m);
	for i:=1 to n do 
		read(f[i,0]);
	f2:=f;
	max_init;
	min_init;
	for i:=1 to m do 
		begin
		readln(tmp1,tmp2);
		writeln(max_query(tmp1,tmp2)-min_query(tmp1,tmp2));
		end;
end.