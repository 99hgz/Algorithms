{
 * @key word:并查集
 * @已测试:POJ - 2236
 * @Author: hgz 
 * @Date: 2017-04-24 20:47:22 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-24 20:47:22 
}
var  
    n,m,i,j,k,x,y:longint; 
    ch,ch1:char;		
    father:array[0..1001] of longint;  
    d:array[0..1001]of record x,y:longint;end;
    red:array[0..1001]of boolean;
function getfather(x:longint):longint;  
begin  
    if father[x]=0 then exit(x);
    father[x]:=getfather(father[x]);  
    exit(father[x]);  
end;  
function ceil(a:real):longint;
begin
    if trunc(a)<a then exit(trunc(a)+1) else exit(trunc(a));
end;
function l(a,b:longint):longint;
begin
    exit(ceil(sqrt(sqr(d[a].x-d[b].x)+sqr(d[a].y-d[b].y))));
end;
procedure he(x,y:longint);  
var  
    fx,fy:longint;  
begin  
    fx:=getfather(x);  
    fy:=getfather(y);  
    father[fx]:=fy;  
end;  
begin  
    readln(n,m);  
    for i:=1 to n do 
        readln(d[i].x,d[i].y);
			
    while not(eof) do
        begin  
        read(ch,ch1);
        if ch='O' then begin
            readln(y);
            for j:=1 to n do 
                if (y<>j)and(red[j])and(l(y,j)<=m) then
                    if getfather(y)<>getfather(j) then he(y,j);
            red[y]:=true;
			end else
			begin
			readln(y,x);
			if getfather(y)<>getfather(x) then writeln('FAIL') else writeln('SUCCESS');
			end;
		end;  
end.