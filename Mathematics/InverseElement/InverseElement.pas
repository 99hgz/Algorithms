{
 * @key word:逆元，扩展欧几里得
 * @已测试：HDU - 1211
 * @Author: hgz 
 * @Date: 2017-04-24 21:14:17 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-24 21:14:17 
}
var
p,q,e,l,d,n,a:int64;
i:longint;
function  pn(b,p:int64):int64;
var
ans,t:int64;
begin
	ans:=1; t:=b;
	while p>0 do
		begin
		if odd(p) then ans:=(ans*t) mod n;
		p:=p div 2;
		t:=t*t mod n;
	end;
exit(ans);
end;
function  inverse(a,n:int64):int64;
	var
		d,x,y,tmp,ans:int64;
	procedure extgcd(a,b:int64;var d,x,y:int64);
		begin
		if b=0 then begin
			d:=a;x:=1;y:=0;
			end
		else
			begin
			extgcd(b,a mod b,d,x,y);
			tmp:=x;
			x:=y;
			y:=tmp-(y*(a div b));
			end;
		end;
	begin
		extgcd(a,n,d,x,y);
		if (1 mod d <>0) then exit(-1);
		x:=x*(1 div d);
		n:=abs(n);
		ans:=x mod n;
		if (ans<=0) then ans:=ans+n;
		exit(ans);
	end;
begin
while not(seekeof) do
begin
	readln(p,q,e,l);
	n:=(p-1)*(q-1);
	d:=inverse(e,n);
	n:=p*q;
	i:=1;
	while i<=l do
	begin
	read(a);
	write(chr(pn(a,d)));
	i:=i+1;
	end;
	writeln;
end;
	end.