{
 * @key word:欧拉函数
 * @已测试:HDU - 1787,HDU - 1286
 * @Author: hgz 
 * @Date: 2017-04-25 09:36:56 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-25 09:36:56 
}
var
	i,n,tmp:longint;
	phi,prime:array[0..32768]of int64;
	flag:array[0..32768]of boolean;
	
procedure work;
var 
maxn,i,tot,j:longint;   
begin
maxn:=32768;
tot:=0;
phi[1]:=1;
for i:=2 to maxn do 
	begin
	if not(flag[i]) then begin
		phi[i]:=i-1;
		tot:=tot+1;
		prime[tot]:=i;
		end;
	for j:=1 to tot do 
		begin
		if (i*prime[j]>maxn) then break;
		flag[i*prime[j]]:=true;
		if (i mod prime[j]=0) then 
			begin
			phi[i*prime[j]]:=phi[i]*prime[j];
			break;
			end
			else 
			phi[i*prime[j]]:=phi[i]*(prime[j]-1);
		end;
	end;
end;
function euler(n:int64):int64;
var 
	i:int64;
begin
	euler:=n;
	i:=2;
	while (i*i)<=n do
		begin
		if (n mod i=0) then 
			euler:=(euler div (i))*(i-1);
		while ((n mod i=0)) do n:=n div i;
		i:=i+1;
		end;
	if n>1 then euler:=(euler div n) * (n-1);
end;
begin
work;
readln(n);
for i:=1 to n do 
	begin
	readln(tmp);
	writeln(phi[tmp]);
	end;
end.