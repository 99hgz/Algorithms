{
 * @key word:树状数组，二维树状数组
 * @已测试:POJ - 2155
 * @Author: hgz 
 * @Date: 2017-04-23 12:44:10 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-23 12:44:10 
}
var
a:array[0..1100,0..1100]of longint;
ch:char;
n,t,_x,_y,_x2,_y2,i,j,n2:longint;
function lowbit(x:longint):longint;
begin
	exit(x and (-x));
end;

procedure update(x,y,v:longint);
var
yy:longint;
begin
	yy:=y;
	while x<=1100 do
	begin
		y:=yy;
		while y<=1100 do 
			begin
			a[x,y]:=a[x,y]+v;
			y:=y+lowbit(y);
			end;
		x:=x+lowbit(x);
	end;
end;

function get(x,y:longint):longint;
var
yy:longint;
begin
	yy:=y;
	get:=0;
	while x>0 do 
	begin
		y:=yy;
		while y>0 do 
			begin
			get:=get+a[x,y];
			y:=y-lowbit(y);
			end;
		x:=x-lowbit(x);
	end;
end;
begin
readln(n2);
for j:=1 to n2 do
    begin
    fillchar(a,sizeof(a),0);
    readln(n,t);
    for i:=1 to t do 
        begin
	    read(ch);
	    if ch='C' then begin
	    	readln(_x,_y,_x2,_y2);
	    	update(_x,_y,1);
	    	update(_x,_y2+1,1);
	    	update(_x2+1,_y,1);
    		update(_x2+1,_y2+1,1);
    		end else 
    		begin
	    	readln(_x,_y);
	    	writeln(get(_x,_y) mod 2);
	    	end;
        end;
    writeln;
    end;
end.